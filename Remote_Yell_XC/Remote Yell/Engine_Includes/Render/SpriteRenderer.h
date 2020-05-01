#pragma once

#include <map>
#include <string>

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Rect;

namespace Internal
{

namespace Render
{

class SpriteRenderer
{
public:

	SpriteRenderer() = default;
	~SpriteRenderer();

	void DrawSprite(const std::string& spritePath, const int x, const int y, bool center = false, bool flipHori = false, SDL_Rect* clip = nullptr);

private:

	struct Sprite
	{
		SDL_Surface* Surface;
		SDL_Texture* Texture;
	};

	void createSprite(const std::string& spritePath);

	std::map<std::string, Sprite> mySprites;
};

} // Render

} // Internal
