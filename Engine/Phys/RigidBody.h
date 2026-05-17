#pragma once
#include "Physics.h"

namespace Physics {
   // Твердое тело с формой
   struct RigidBody : Body {
      Geometry::Shape* shape;
      bool isStatic;

      // Конструктор по умолчанию
      RigidBody() : shape(nullptr), isStatic(false) {}

      // Конструктор с параметрами
      RigidBody(Geometry::Shape* sh, const Geometry::Vector& pos, const Geometry::Vector& vel, bool stat = false, float m = 1.0f)
          : Body(m), shape(sh), isStatic(stat) {
          position = pos;
          velocity = vel;
      }

      // Деструктор
      ~RigidBody() {
          delete shape;
      }

      // Запрещаем копирование (чтобы указатель на Shape не сломал тут все =) )
      RigidBody(const RigidBody&) = delete;
      RigidBody& operator=(const RigidBody&) = delete;

      // Перемещение
      RigidBody(RigidBody&& other) noexcept // говрят с noexcept оптимизация лучше
          : Body(other.mass), shape(other.shape), isStatic(other.isStatic) {
          position = other.position;
          velocity = other.velocity;
          other.shape = nullptr;
      }

      RigidBody& operator=(RigidBody&& other) noexcept {
          if (this != &other) {
              delete shape;
              mass = other.mass;
              position = other.position;
              velocity = other.velocity;
              shape = other.shape;
              isStatic = other.isStatic;
              other.shape = nullptr;
          }
          return *this;
      }
   };
} // namespace Physics