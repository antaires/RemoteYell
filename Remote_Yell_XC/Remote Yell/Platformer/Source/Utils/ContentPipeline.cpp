#include <Utils/ContentPipeline.h>

#include <cassert>
#include <fstream>
#include <sstream>

namespace Platformer
{

namespace Utils
{

ContentPipeline::DataOutput ContentPipeline::getContent(const std::string& fileName)
{
	ContentPipeline::DataOutput output;

	parseFile(fileName, [&output] (json& contents) {
	
		assert(contents.is_object());

		// RENDER DIMENSIONS

		assert(contents.count(Constants::k_jsonKeyDim) > 0);
		auto& dims = contents.at(Constants::k_jsonKeyDim);

		assert(dims.count(Constants::k_jsonKeyWidth) > 0);
		output.SpriteWidth = dims.at(Constants::k_jsonKeyWidth);

		assert(dims.count(Constants::k_jsonKeyHeight) > 0);
		output.SpriteHeight = dims.at(Constants::k_jsonKeyHeight);

		assert(dims.count(Constants::k_jsonKeyCols) > 0);
		output.SpriteCols = dims.at(Constants::k_jsonKeyCols);

		assert(dims.count(Constants::k_jsonKeyRows) > 0);
		output.SpriteRows = dims.at(Constants::k_jsonKeyRows);

		// COLLISION DIMENSIONS

		assert(contents.count(Constants::k_jsonKeyColl) > 0);
		auto& coll = contents.at(Constants::k_jsonKeyColl);

		assert(coll.count(Constants::k_jsonKeyWidth) > 0);
		output.AABBDimensions.myX = coll.at(Constants::k_jsonKeyWidth);

		assert(coll.count(Constants::k_jsonKeyHeight) > 0);
		output.AABBDimensions.myY = coll.at(Constants::k_jsonKeyHeight);

		assert(coll.count(Constants::k_jsonKeyXOffset) > 0);
		output.AABBOffset.myX = coll.at(Constants::k_jsonKeyXOffset);

		assert(coll.count(Constants::k_jsonKeyYOffset) > 0);
		output.AABBOffset.myY = coll.at(Constants::k_jsonKeyYOffset);

		// ANIMATIONS

		assert(contents.count(Constants::k_jsonKeyAnim) > 0);
		auto& anims = contents.at(Constants::k_jsonKeyAnim);

		for (auto& anim : anims)
		{
			assert(anim.count(Constants::k_jsonKeyIdx) > 0);
			auto& idx = anim.at(Constants::k_jsonKeyIdx);

			assert(anim.count(Constants::k_jsonKeyStart) > 0);
			auto& start = anim.at(Constants::k_jsonKeyStart);

			assert(anim.count(Constants::k_jsonKeyCount) > 0);
			auto& count = anim.at(Constants::k_jsonKeyCount);

			// Add the draw state.
			output.Animations[idx] = { start, count };
		}
	});

	return output;
}

void ContentPipeline::parseFile(const std::string& fileName, JsonParseFn parseFn)
{
	std::ifstream fileStream(fileName);
	assert(fileStream.is_open());

	json jsonContents;
	fileStream >> jsonContents;

	parseFn(jsonContents);

	fileStream.close();
}

} // Utils

} // Platformer
