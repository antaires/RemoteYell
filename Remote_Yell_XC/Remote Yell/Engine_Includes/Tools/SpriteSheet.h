#pragma once

#include <string>

namespace Internal
{

namespace Tools
{

struct SpriteSheet
{
public:

	SpriteSheet(const std::string& file, const int w, const int h, const int cols, const int rows);
	~SpriteSheet() = default;

	std::string myFile;

	int mySpriteW;
	int mySpriteH;

	int myCols;
	int myRows;

	void IndexToXY(const int index, int& x, int& y);
};

} // Tools

} // Internal
