#pragma once

#include <json.hpp>

#include <EngineInterface.h>

#include <Gameplay/Components/AnimRenderComponent.h>

namespace Platformer
{

namespace Utils
{

struct ContentPipeline
{
	using json = nlohmann::json;
	using JsonParseFn = std::function<void(json&)>;

	struct DataOutput
	{
		// Animation data.
		Gameplay::AnimRenderComponent::AnimFrameMap Animations = {};

		// Render data.
		int SpriteWidth = 0;
		int SpriteHeight = 0;
		int SpriteCols = 0;
		int SpriteRows = 0;

		// Collision data.
		Engine::Vec2 AABBDimensions = { 0.0f, 0.0f };
		Engine::Vec2 AABBOffset = { 0.0f, 0.0f };
	};

	static DataOutput getContent(const std::string& fileName);

private:

	static void parseFile(const std::string& fileName, JsonParseFn parseFn);

	struct Constants
	{
		static constexpr const char* k_jsonKeyDim = "dimensions";
		static constexpr const char* k_jsonKeyWidth = "width";
		static constexpr const char* k_jsonKeyHeight = "height";
		static constexpr const char* k_jsonKeyCols = "cols";
		static constexpr const char* k_jsonKeyRows = "rows";

		static constexpr const char* k_jsonKeyColl = "collision";
		static constexpr const char* k_jsonKeyXOffset = "xOffset";
		static constexpr const char* k_jsonKeyYOffset = "yOffset";

		static constexpr const char* k_jsonKeyAnim = "animations";
		static constexpr const char* k_jsonKeyIdx = "index";
		static constexpr const char* k_jsonKeyStart = "start";
		static constexpr const char* k_jsonKeyCount = "count";
	};
};

} // Utils

} // Platformer
