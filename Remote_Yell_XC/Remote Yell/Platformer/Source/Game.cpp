#include <Game.h>

#include <EngineInterface.h>

#include <Level.h>

#include <iostream>

namespace Platformer
{

// The Game instance.
Game theGame;

// Set up all necessary data, then commence the Engine.
void Game::Run()
{
	Engine::CreateWindow("Remote Yell", Constants::k_windowWidth, Constants::k_windowHeight);

	// Start the Engine and pass our update function, to be run every update loop.
	Engine::StartUpdate([&](const double dt)
	{
		Update(dt);
	});
}

void Game::Update(const double deltaTime)
{
	if (myLevel == nullptr)
	{
		myLevel = new Level(Constants::k_defaultLevel);
	}
	
	// TODO: Game logic.

}

} // Platformer
