#pragma once

#include <Math/Vec2.h>

#include <string>
#include <vector>

struct _TTF_Font;

namespace Internal
{

namespace Render
{

class DebugRenderer
{
public:

	DebugRenderer() = default;
	~DebugRenderer();

	void Render();

	void DrawWorldLine(const Math::Vec2& start, const Math::Vec2& end, int r = 255, int g = 255, int b = 255);
	void DrawScreenLine(const Math::Vec2& start, const Math::Vec2& end, int r = 255, int g = 255, int b = 255);

	void DrawWorldText(const std::string& text, const Math::Vec2& pos, int r = 255, int g = 255, int b = 255);
	void DrawScreenText(const std::string& text, const Math::Vec2& pos, int r = 255, int g = 255, int b = 255);

private:

	struct Text
	{
		std::string text;
		Math::Vec2 pos;
		bool screenSpace;

		int r;
		int g;
		int b;

		void Render(_TTF_Font* font);
	};

	struct Line
	{
		Math::Vec2 start;
		Math::Vec2 end;
		bool screenSpace;

		int r;
		int g;
		int b;

		void Render();
	};

	std::vector<Line> myDebugLines = {};
	std::vector<Text> myDebugText = {};

	_TTF_Font* myFont = nullptr;

	struct Constants
	{
		static constexpr const char* k_fontFilePath = "Resources/Fonts/FreeSansBold.ttf";
	};
};

} // Render

} // Internal
