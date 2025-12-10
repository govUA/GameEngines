#ifndef MOVE_COLLISIONSYSTEM_H
#define MOVE_COLLISIONSYSTEM_H

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <algorithm>

struct Circle {
    float x, y;
    float radius;
};

struct AABB {
    float x, y;
    float w, h;
};

struct CollisionResult {
    bool isColliding;
    float penetrationDepth;
    float normalX;
    float normalY;
};

class CollisionSystem {
public:
    static bool BroadPhaseCheck(const AABB &box1, const AABB &box2);

    static CollisionResult NarrowPhaseCheck(const Circle &circle, const AABB &box);

    static void ResolveCollision(float &posX, float &posY, const CollisionResult &result);
};

#endif
