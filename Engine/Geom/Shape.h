#pragma once
#include "Geometry.h"

namespace Geometry {
   // Фигуры
   class Shape {
   public:
       enum Type {
           Circle
       };
       virtual Type type() const = 0;
       virtual ~Shape() {}
   };
} // namespace Geometry