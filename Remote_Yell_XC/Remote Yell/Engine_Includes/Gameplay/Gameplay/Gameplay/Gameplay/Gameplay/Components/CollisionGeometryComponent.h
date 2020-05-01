#pragma once

#include <Gameplay/Component.h>
#include <Render/IRenderable.h>

#include <Tools/CollisionPrimitives.h>

namespace Internal
{

	namespace Gameplay
	{
		//TODO: extend for circles as well as AABBs
		// better yet arbitrary lists of AABBs and circless
		class CollisionGeometryComponent : public Component, public Render::IRenderable
		{
		private:

			using AABB = Tools::CollisionPrimitives::AABB;

		public:

			CollisionGeometryComponent(AABB bounds, Math::Vec2 offset = Math::Vec2{0.0f,0.0f});
			~CollisionGeometryComponent() override = default;

			void Update(const double dt) override;
			void Render() override;

			AABB GetBounds() const { return myBounds; }
		private:

			AABB myBounds = {};
			Math::Vec2 myOffset = {};
		};

	} // Gameplay

} // Internal
