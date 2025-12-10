#include "CollisionSystem.h"

bool CollisionSystem::BroadPhaseCheck(const AABB &a, const AABB &b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

CollisionResult CollisionSystem::NarrowPhaseCheck(const Circle &circle, const AABB &box) {
    CollisionResult result = {false, 0.0f, 0.0f, 0.0f};

    float closestX = std::clamp(circle.x, box.x, box.x + box.w);
    float closestY = std::clamp(circle.y, box.y, box.y + box.h);

    float distanceX = circle.x - closestX;
    float distanceY = circle.y - closestY;

    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
    float radiusSquared = circle.radius * circle.radius;

    if (distanceSquared < radiusSquared) {
        result.isColliding = true;

        float distance = std::sqrt(distanceSquared);

        if (distance == 0.0f) {
            float overlapL = circle.x - box.x;
            float overlapR = (box.x + box.w) - circle.x;
            float overlapT = circle.y - box.y;
            float overlapB = (box.y + box.h) - circle.y;

            float minOverlap = std::min({overlapL, overlapR, overlapT, overlapB});

            if (minOverlap == overlapL) {
                result.normalX = 1;
                result.normalY = 0;
            } else if (minOverlap == overlapR) {
                result.normalX = -1;
                result.normalY = 0;
            } else if (minOverlap == overlapT) {
                result.normalX = 0;
                result.normalY = 1;
            } else {
                result.normalX = 0;
                result.normalY = -1;
            }

            result.penetrationDepth = circle.radius + minOverlap;
        } else {
            result.normalX = distanceX / distance;
            result.normalY = distanceY / distance;
            result.penetrationDepth = circle.radius - distance;
        }
    }

    return result;
}

void CollisionSystem::ResolveCollision(float &posX, float &posY, const CollisionResult &result) {
    posX += result.normalX * result.penetrationDepth;
    posY += result.normalY * result.penetrationDepth;
}
