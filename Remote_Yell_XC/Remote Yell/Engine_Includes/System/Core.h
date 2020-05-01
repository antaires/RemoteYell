#pragma once

#include <chrono>
#include <functional>
#include <string>

#include <System/Camera.h>
#include <System/World.h>
#include <Render/RenderCore.h>

#include <Gameplay/EntityManager.h>

struct SDL_Window;
struct SDL_Renderer;

struct Engine;

namespace Internal
{

namespace System
{

class Core
{
public:

	Core() = default;
	~Core() = default;

	SDL_Window* GetWindow() const { return myWindow; }
	SDL_Renderer* GetSDLRenderer() const { return mySDLRenderer; }

	const Camera& ViewCamera() const { return myCamera; }
	Camera& EditCamera() { return myCamera; }

	const Render::RenderCore& ViewRenderCore() const { return myRenderCore; }
	Render::RenderCore& EditRenderCore() { return myRenderCore; }

	const World& ViewWorld() const { return myWorld; }
	World& EditWorld() { return myWorld; }

	const Gameplay::EntityManager& ViewEntityManager() const { return myEntityManager; }
	Gameplay::EntityManager& EditEntityManager() { return myEntityManager; }

	bool KeyPressed(const char* key) const;

private:

	friend Engine;
	using GameUpdateFn = std::function<void(const double)>;

	void CreateWindow(const std::string& title, const int width, const int height);
	void GetWindowDimensions(int& width, int& height);

	void StartGame(GameUpdateFn updateFn);

	const unsigned long long GetTick() const { return myTick; }
	const double GetGameTime() const { return myGameTime; }

	// SDL systems.
	SDL_Window* myWindow = nullptr;
	SDL_Renderer* mySDLRenderer = nullptr;

	// Main systems.
	Gameplay::EntityManager myEntityManager = {};
	Camera myCamera = {};
	Render::RenderCore myRenderCore = {};
	World myWorld = {};

	// Timing.
	unsigned long long myTick = 0ULL;
	double myGameTime = 0.0;
	unsigned int myTimerTicks = 0U;
	double myFrameTimer = 0.0;
	std::chrono::time_point<std::chrono::high_resolution_clock> myPreviousTime;

	// Input.
	const uint8_t* myKeyState = nullptr;
	unsigned int myMouseState = 0;
	int myMouseX = 0;
	int myMouseY = 0;

	struct Constants
	{
		static constexpr double k_framesPerSecond = 60.0;
		static constexpr double k_frameTimeS = (1.0 / k_framesPerSecond);
	};
};

} // System

extern System::Core theCore;

} // Internal
