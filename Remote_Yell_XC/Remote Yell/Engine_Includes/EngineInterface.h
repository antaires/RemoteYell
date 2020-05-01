#pragma once


#include <Tools/CollisionPrimitives.h>

#include <Gameplay/Entity.h>

#include <Gameplay/Components/CameraComponent.h>
#include <Gameplay/Components/RenderComponent.h>
#include <Gameplay/Components/TileCollisionComponent.h>
#include <Gameplay/Components/CollisionGeometryComponent.h>
#include <Gameplay/Components/TransformComponent.h>

#include <System/Core.h>

//----------------------------------------------- 
// Engine
//
// The outward-facing interface for engine usage.
//
struct Engine
{
	//-------------------------------------------
	// ALIASES
	//
	using UpdateFn = Internal::System::Core::GameUpdateFn;

	// World.
	using CreationFn = Internal::System::World::CreateFunction;
	using WorldParseToken = Internal::System::World::Token;
	using BackgroundLayerData = Internal::System::World::LayerData;
	using BGCreateFn = Internal::System::World::BGCreateFunction;

	// Gameplay.
	using EntityId = Internal::Gameplay::EntityId;
	using Entity = Internal::Gameplay::Entity;
	using EntityID_List = Internal::Gameplay::EntityID_List;

	// Component.
	using Component = Internal::Gameplay::Component;
	using SystemCameraComponent = Internal::Gameplay::CameraComponent;
	using SystemRenderComponent = Internal::Gameplay::RenderComponent;
	using SystemTransformComponent = Internal::Gameplay::TransformComponent;
	using SystemTileCollisionComponent = Internal::Gameplay::TileCollisionComponent;
	using SystemCollisionGeometryComponent = Internal::Gameplay::CollisionGeometryComponent;

	// Math.
	using Vec2 = Internal::Math::Vec2;
	
	// Render.
	using RenderOrder = Internal::Render::RenderOrder;
	using RenderAnchor = Internal::Render::RenderAnchor;
	using SpriteSheet = Internal::Tools::SpriteSheet;

	// Collision.
	using Point = Internal::Tools::CollisionPrimitives::Point;
	using AABB = Internal::Tools::CollisionPrimitives::AABB;
	using Circle = Internal::Tools::CollisionPrimitives::Circle;
	using Ray = Internal::Tools::CollisionPrimitives::Ray;

	//-------------------------------------------
	// FUNCTIONS
	//
	// Window management.
	static void CreateWindow(const std::string& title, const int width, const int height);
	static void GetWindowDimensions(int& width, int& height);

	// Game flow.
	static void StartUpdate(UpdateFn update);
	static unsigned long long GetTick();
	static double GetGameTime();

	// Entity.
	static Entity& CreateEntity();
	static Entity* EditEntity(int id);
	static void UnloadAllEntities();

	// World.
	static void LoadWorldFile(const std::string& filePath, CreationFn creator);
	static void SetUpBackground(const std::vector<BackgroundLayerData>& layers, BGCreateFn creator);
	static const SpriteSheet& GetWorldSpritesheet();
	static const int GetTileSize();
	static const Entity* GetTileEntity(int x, int y);
	static void AddCollisionTile(const int col, const int row, const EntityId entityId);

	// Camera.
	static const Vec2& GetCameraPosition();

	// Drawing.
	static void DrawWorldLine(const Vec2& start, const Vec2& end, int r = 255, int g = 255, int b = 255);
	static void DrawScreenLine(const Vec2& start, const Vec2& end, int r = 255, int g = 255, int b = 255);

	static void DrawWorldText(const std::string& text, const Vec2& pos, int r = 255, int g = 255, int b = 255);
	static void DrawScreenText(const std::string& text, const Vec2& pos, int r = 255, int g = 255, int b = 255);

	// Input.
	static bool KeyDown(const char* key);
	static bool KeyUp(const char* key);
	static bool MouseLeftDown();
	static bool MouseRightDown();
	static void GetMousePosition(int& x, int& y);

	// Collision
	static const bool PointVsAABB(const Point& point, const AABB& aabb);
	static const bool PointVsCircle(const Point& point, const Circle& circle);
	static const bool AABBVsAABB(const AABB& one, const AABB& two);
	static const bool AABBVsCircle(const AABB& aabb, const Circle& circle);
	static const bool CircleVsCircle(const Circle& one, const Circle& two);
	static const bool AABBVsEntities(const AABB& aabb, const EntityID_List& entites, EntityID_List& hits);
	static const bool CircleVsEntities(const Circle& circle, const EntityID_List& entites, EntityID_List& hits);
	static const bool RayVsAABB(const Ray& ray, const float distance, const AABB& aabb, Point* outIntersectionPoint = nullptr);
	static const bool RayVsCirlce(const Ray& ray, const float distance, const Circle& circle, Point* outIntersectionPoint = nullptr);
	static const bool RayVsWorld(const Ray& ray, const float distance, Point* outIntersectionPoint = nullptr);
};

