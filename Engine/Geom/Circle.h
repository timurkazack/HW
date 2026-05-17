#pragma once
#include "Geometry.h"

namespace Geometry {
// Класс круга
   class Circle : public Shape {
   public:
      Vector center;
      float radius;
       
      Circle(const Vector& c = Vector(0, 0), float r = 1.0f) : center(c), radius(r) {}
      Circle(const Circle& other) : center(other.center), radius(other.radius) {}
       
      Type type() const override { return Shape::Circle; }
       
      float square() const {
         return M_PI * radius * radius;
      }
       
      void move(const Vector& shift) {
         center += shift;
      }
   };
} // namespace Geometry