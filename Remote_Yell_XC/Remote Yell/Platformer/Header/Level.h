#pragma once

#include <EngineInterface.h>

#include <Gameplay/EntityFactory.h>

namespace Platformer
{

class Level
{
public:

	Level(const char* levelFile);
	~Level();

	static const std::vector<int>& GetSpritesForType(Gameplay::EntityType type);

private:

	Engine::EntityId ParseWorld(const Engine::WorldParseToken& token, const Engine::Vec2& pos);

	struct LeftMidRight
	{
		Gameplay::EntityType Left;
		Gameplay::EntityType Mid;
		Gameplay::EntityType Right;
	};
	Gameplay::EntityType PickLeftMidRight(const Engine::WorldParseToken& token, const LeftMidRight& lmr);

	static std::map<Gameplay::EntityType, std::vector<int>> theWorldSpriteIndexes;
	static std::vector<Engine::BackgroundLayerData> theBackgroundLayers;
};

}
