#pragma once
#include "Geometry.h"

namespace Geometry {
    
    class Vector {
    public:
        float x;
        float y;
        
        Vector(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
        Vector(const Vector& other) : x(other.x), y(other.y) {}
        
        void add(const Vector& other) { x += other.x; y += other.y; }
        void sub(const Vector& other) { x -= other.x; y -= other.y; }
        void mul(float scalar) { x *= scalar; y *= scalar; }
        
        float length() const {
            return std::sqrt(x * x + y * y);
        }
        
        
        Vector& operator+=(const Vector& other) {
            x += other.x;
            y += other.y;
            return *this;
        }
        
        Vector& operator-=(const Vector& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        
        Vector& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
    };
    
    // Операторы для Vector
    Vector operator+(const Vector& a, const Vector& b) {
        return Vector(a.x + b.x, a.y + b.y);
    }
    
    Vector operator-(const Vector& a, const Vector& b) {
        return Vector(a.x - b.x, a.y - b.y);
    }
    
    Vector operator*(const Vector& a, float s) {
        return Vector(a.x * s, a.y * s);
    }
    
    Vector operator*(float s, const Vector& a) {
        return Vector(a.x * s, a.y * s);
    }
    
    float dotProduct(const Vector& a, const Vector& b) {
        return a.x * b.x + a.y * b.y;
    }
    
    float crossProduct(const Vector& a, const Vector& b) {
        return a.x * b.y - a.y * b.x;
    }
} // namespace Geometry