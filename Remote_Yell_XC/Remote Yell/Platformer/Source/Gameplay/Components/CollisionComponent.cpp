#include <Gameplay/Components/CollisionComponent.h>

#include <Game.h>

#include <algorithm>
#include <float.h>

namespace Platformer
{

namespace Gameplay
{

CollisionComponent::CollisionComponent(const int width, const int height, const int xOffset/* = 0*/, const int yOffset/* = 0*/)
    : myOffset(xOffset, yOffset)
{
    myBounds.Width = width;
    myBounds.Height = height;
}

void CollisionComponent::Update(const double dt)
{
    auto* transformC = myParent->GetComponent<Engine::SystemTransformComponent>();
    auto& position = transformC->GetPosition();

    UpdateAABB(position + myOffset, myBounds);
}

void CollisionComponent::UpdateAABB(const Engine::Vec2& position, AABB& out) const
{
    out.Position = position;

    out.Left = out.Position.myX;
    out.Right = out.Left + out.Width;

    out.Top = out.Position.myY;
    out.Bottom = out.Top + out.Height;

    out.Center = out.Position + Engine::Vec2(out.Width * 0.5f, out.Height * 0.5f);
}

void CollisionComponent::CheckCollision(const Engine::Vec2& proposal, Engine::Vec2& minima) const
{
    auto& currentPos = myBounds.Position;
    Engine::Vec2 newPosition = currentPos + proposal;

    AABB newBounds(myBounds);
    UpdateAABB(newPosition, newBounds);

    const bool movingRight = (proposal.myX > 0.0f);
    const bool movingDown = (proposal.myY > 0.0f);

    Engine::Vec2 movingEdges;
    movingEdges.myX = movingRight ? myBounds.Right : myBounds.Left;
    movingEdges.myY = movingDown ? myBounds.Bottom : myBounds.Top;

    Engine::Vec2 testPosition;
    testPosition.myX = movingRight ? newBounds.Right : newBounds.Left;
    testPosition.myY = movingDown ? newBounds.Bottom : newBounds.Top;

    Engine::Vec2 tile(testPosition);
    tile.myX /= Engine::GetTileSize();
    tile.myY /= Engine::GetTileSize();

    const int x = (int)tile.myX;
    const int y = (int)tile.myY;

    // x axis
    float minX = FLT_MAX;
    for (int i = (y - 3); i <= (y + 3); ++i)
    {
        auto* ent = Engine::GetTileEntity(x, i);
        if (ent == nullptr)
            continue;

        auto* collisionC = ent->GetComponent<CollisionComponent>();
        auto& targetBounds = collisionC->myBounds;

        if (myBounds.Top >= targetBounds.Bottom || myBounds.Bottom <= targetBounds.Top)
            continue;

        float target = movingRight ? collisionC->myBounds.Left : collisionC->myBounds.Right;

        const float distance = std::abs(target - movingEdges.myX);
        minX = std::min(distance, minX);
    }

    // y axis
    float minY = FLT_MAX;
    for (int i = (x - 3); i <= (x + 3); ++i)
    {
        auto* ent = Engine::GetTileEntity(i, y);
        if (ent == nullptr)
            continue;

        auto* collisionC = ent->GetComponent<CollisionComponent>();
        auto& targetBounds = collisionC->myBounds;

        if (myBounds.Left >= targetBounds.Right || myBounds.Right <= targetBounds.Left)
            continue;

        float target = movingDown ? collisionC->myBounds.Top : collisionC->myBounds.Bottom;

        const float distance = std::abs(target - movingEdges.myY);
        minY = std::min(distance, minY);
    }

    minima.myX = minX;
    minima.myY = minY;
}

} // Gameplay

} // Platformer

