#include <Level.h>

#include <cassert>

namespace Platformer
{

// Mapping of which specific sprites represent each type of entity.
std::map<Gameplay::EntityType, std::vector<int>> Level::theWorldSpriteIndexes =
{
	{ Gameplay::EntityType_Tile_Ground_Mid,{ 2, 5, 6, 7 } },
	{ Gameplay::EntityType_Tile_Ground_Left,{ 1, 15 } },
	{ Gameplay::EntityType_Tile_Ground_Right,{ 3, 19 } },
	{ Gameplay::EntityType_Tile_Wall_Mid,{ 32, 46, 47, 48 } },
	{ Gameplay::EntityType_Tile_Wall_Left,{ 45 } },
	{ Gameplay::EntityType_Tile_Wall_Right,{ 49 } },
	{ Gameplay::EntityType_Tile_Shadow_Mid,{ 17, 31, 33 } },
	{ Gameplay::EntityType_Tile_Shadow_Left,{ 30 } },
	{ Gameplay::EntityType_Tile_Shadow_Right,{ 34 } },
	{ Gameplay::EntityType_Tile_Water,{ 200 } },
	{ Gameplay::EntityType_Tile_SmallBox,{ 154 } },
};

// The parallax background.
std::vector<Engine::BackgroundLayerData> Level::theBackgroundLayers = {
	{ Gameplay::EntityType_Background_City, 0.2f },
	{ Gameplay::EntityType_Background_Clouds, 0.4f }
};

Level::Level(const char* levelFile)
{
	using namespace Gameplay;

	// Pass the engine the world file to open and parse, providing a callback for the actions taken during parsing.
	Engine::LoadWorldFile(levelFile, [this](const Engine::WorldParseToken& token, const Engine::Vec2& pos)
	{
		return ParseWorld(token, pos);
	});


	// Create the parallax background, and pass the function to create new entities when needed.
	Engine::SetUpBackground(theBackgroundLayers, [](int typeIndex, int x, int y) -> int
	{
		return Gameplay::EntityFactory::CreateEntity((Gameplay::EntityType)typeIndex, x, y);
	});
}

Level::~Level()
{
	Engine::UnloadAllEntities();
}

const std::vector<int>& Level::GetSpritesForType(Gameplay::EntityType type)
{
	assert(theWorldSpriteIndexes.count(type) > 0);
	return theWorldSpriteIndexes.at(type);
}

Engine::EntityId Level::ParseWorld(const Engine::WorldParseToken& token, const Engine::Vec2& pos)
{
	using namespace Gameplay;

	Engine::EntityId createdEntity = -1;

	int x = static_cast<int>(pos.myX);
	int y = static_cast<int>(pos.myY);

	switch (token.Current)
	{
		case ' ':
		{
			break;
		}
		case '-':
		{
			auto type = PickLeftMidRight(token, { EntityType_Tile_Ground_Left, EntityType_Tile_Ground_Mid, EntityType_Tile_Ground_Right });
			createdEntity = EntityFactory::CreateTile(type, x, y, true);

			break;
		}
		case '|':
		{
			auto type = PickLeftMidRight(token, { EntityType_Tile_Wall_Left, EntityType_Tile_Wall_Mid, EntityType_Tile_Wall_Right });
			createdEntity = EntityFactory::CreateTile(type, x, y, false);

			break;
		}
		case 'x':
		{
			auto type = PickLeftMidRight(token, { EntityType_Tile_Shadow_Left, EntityType_Tile_Shadow_Mid, EntityType_Tile_Shadow_Right });
			createdEntity = EntityFactory::CreateTile(type, x, y, false);

			break;
		}
		case '~':
		{
			createdEntity = EntityFactory::CreateTile(EntityType_Tile_Water, x, y, false);

			break;
		}
		case 'b':
		{
			createdEntity = EntityFactory::CreateTile(EntityType_Tile_SmallBox, x, y, true);

			break;
		}
		case 'P':
		{
			EntityFactory::CreateEntity(EntityType_Player, x, y);

			break;
		}
		case 'E':
		{
			EntityFactory::CreateEntity(EntityType_Enemy, x, y);

			break;
		}
		default:
			break;
	}

	return createdEntity;
}

Gameplay::EntityType Level::PickLeftMidRight(const Engine::WorldParseToken& token, const LeftMidRight& lmr)
{
	if (token.Previous != token.Current)
		return lmr.Left;

	if (token.Next != token.Current)
		return lmr.Right;

	return lmr.Mid;
}


}
