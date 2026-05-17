#pragma once
#include "Physics.h"

namespace Physics {
    // Базовое тело
    struct Body {
        float mass;
        Geometry::Vector position;
        Geometry::Vector velocity;
        
        Body(float m = 1.0f) : mass(m), position(0, 0), velocity(0, 0) {}
        
        void update(float dt) {
            position += velocity * dt;
        }
    };
} // namespace Physics