#pragma once

#include <EngineInterface.h>

namespace Platformer
{

class Level;

//----------------------------------------------- 
// Game
//
// Main update logic and control for the overall game systems.
//
class Game
{
public:

	Game() = default;
	~Game() = default;

	void Run();
	
	static constexpr int GetWindowWidth() { return Constants::k_windowWidth; }
	static constexpr int GetWindowHeight() { return Constants::k_windowHeight; }

private:

	void Update(const double deltaTime);

	Level* myLevel = nullptr;

	struct Constants
	{
		static constexpr int k_windowWidth = 1280;
		static constexpr int k_windowHeight = 768;

		static constexpr const char* k_defaultLevel = "Resources/level_map.txt";
	};
};

// Single Game instance.
extern Game theGame;

} // Platformer
