#pragma once

#include <Tools/SpriteSheet.h>

#include <Math/Vec2.h>

#include <functional>
#include <map>
#include <string>
#include <vector>

#include <Gameplay/Entity.h>

namespace Internal
{


namespace System
{

struct World
{
public:

	struct Token
	{
		char Previous;
		char Current;
		char Next;
	};

	using CreateFunction = std::function<Gameplay::EntityId(const Token&, const Math::Vec2&)>;

	World() = default;
	~World() = default;

	void LoadWorldFromFile(const std::string& mapFile, CreateFunction parser);
	void Unload();

	struct LayerData
	{
		int TypeIndex;
		float Parallax;
	};

	using BGCreateFunction = std::function<int(int, int, int)>;
	void SetUpBackground(const std::vector<LayerData>& layers, BGCreateFunction createFn);

	void Update(const double deltaTime);

	void AddCollisionTile(const int col, const int row, const Gameplay::EntityId entityId);

	static int GetWidth() { return theWorldWidth; }
	static int GetHeight() { return theWorldHeight; }
	static int GetTileSize() { return Constants::k_tileSize; }

	const int ViewTileEntity(const int x, const int y) const { return (myTileMap.count({ x, y }) > 0) ? myTileMap.at({ x, y }) : -1; }

	static Tools::SpriteSheet& GetWorldSpriteSheet() { return theWorldSpriteSheet; }

	void SetBackgroundRefPos(const Math::Vec2& ref) { myBackgroundRefPos = ref; }
	void SetBackgroundOffset(const int offset) { myBackgroundOffset = offset; }

private:

	struct BackgroundLayer
	{
		LayerData Data;
		std::map<int, int> myLayerTiles;
	};

	void ManageBackgroundLayerTiles(bool leftSide, BackgroundLayer& layer);

	static Tools::SpriteSheet theWorldSpriteSheet;

	static int theWorldWidth;
	static int theWorldHeight;

	std::map<std::pair<int, int>, int> myTileMap = {};

	std::vector<BackgroundLayer> myBackgroundLayers;
	Math::Vec2 myBackgroundRefPos = { 0.0f, 0.0f };
	int myBackgroundOffset = 0;
	BGCreateFunction myBGCreateFunction = [](int, int, int) -> int { return -1; };

	struct Constants
	{
		static constexpr int k_tileSize = 64;
		static constexpr const char* k_spriteSheetFile = "Resources/Images/city.png";

		static constexpr int k_spriteSheetCols = 15;
		static constexpr int k_spriteSheetRows = 25;

		static constexpr int k_backgroundWidth = 1920;
		static constexpr int k_backgroundBuffer = 250;
	};
};

} // System

} // Internal
