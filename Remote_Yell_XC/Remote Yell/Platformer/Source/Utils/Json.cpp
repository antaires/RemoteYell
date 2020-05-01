#include <Utils/Json.h>

#include <cassert>
#include <fstream>
#include <sstream>

namespace Platformer
{

namespace Utils
{

void Json::parseFile(const std::string& fileName, JsonParseFn parseFn)
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
