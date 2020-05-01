#pragma once

#include <json.hpp>

namespace Platformer
{

namespace Utils
{

struct Json
{
	using json = nlohmann::json;
	using JsonParseFn = std::function<void(json&)>;

	static void parseFile(const std::string& fileName, JsonParseFn parseFn);
};

} // Utils

} // Platformer
