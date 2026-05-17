#pragma once

// required libs


// other libs
#include "../Geom/Geometry.h"

// current libs
#include "Body.h"
#include "RigidBody.h"

//// functions
namespace Physics {
// Вектор выталкивания
    Geometry::Vector getShift(const Geometry::Shape* A, const Geometry::Shape* B) {
        switch(A->type()) {
            case Geometry::Shape::Circle:
                switch(B->type()) {
                    case Geometry::Shape::Circle: {
                            Geometry::Vector ret;
                            const Geometry::Circle* circleA = static_cast<const Geometry::Circle*>(A);
                            const Geometry::Circle* circleB = static_cast<const Geometry::Circle*>(B);

                            // Растояния между центрами
                            float dx = circleB->center.x - circleA->center.x;
                            float dy = circleB->center.y - circleA->center.y;

                            // Квадрат растаяния между центрами
                            float sqrDistance = dx * dx + dy * dy;

                            // Квадрат суммы радиусов
                            float sumRadii = circleA->radius + circleB->radius;
                            float sqrRadii = sumRadii * sumRadii;

                            // Проверка столкновения
                            if (sqrDistance < sqrRadii) {
                                float distance = std::sqrt(sqrDistance);
                        
                                if (distance != 0.0f) {
                                    float overlap = sumRadii - distance;
                                    // Выталкиваем вектор А в обратную сторону от Б
                                    ret.x = -(dx / distance) * overlap;
                                    ret.y = -(dy / distance) * overlap;
                                } else {
                                    // Если центры полностью совпали
                                    ret.y = sumRadii; 
                        }
                    }
                            
            return ret;
          }
        default: return Geometry::Vector();
      }
    default: return Geometry::Vector();
  }
}
} // namespace Physics