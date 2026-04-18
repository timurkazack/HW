#include <cmath>
using namespace std;

class Vector {
public:
    float x;
    float y;

    Vector() : x(0.0), y(0.0) {}
    Vector(float X, float Y) : x(X), y(Y) {}
    Vector(const Vector& other) : x(other.x), y(other.y) {}

    void add(const Vector& other) { x += other.x; y += other.y; }
    void sub(const Vector& other) { x -= other.x; y -= other.y; }
    void mul(float scalar) { x *= scalar; y *= scalar; }
    float length() const { return sqrt(x*x + y*y); }
    
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

class Segment {
public:
    Vector a;
    Vector b;

    Segment() : a(0.0, 0.0), b(0.0, 0.0) {}
    Segment(const Vector& A, const Vector& B) : a(A), b(B) {}
    Segment(const Segment& other) : a(other.a), b(other.b) {}

    float length() const {
        Vector diff = a - b;
        return diff.length();
    }

    void move(const Vector& shift) {
        a += shift;
        b += shift;
    }
};

class Circle {
public:
    Vector pos;
    float r;

    Circle() : pos(0.0, 0.0), r(0.0) {}
    Circle(const Vector& Pos, float Radius) : pos(Pos), r(Radius) {}
    Circle(const Circle& other) : pos(other.pos), r(other.r) {}

    float square() const {
        return 3.14159f * r * r;
    }

    void move(const Vector& shift) {
        pos += shift;
    }
};

class Triangle {
public:
    Vector A;
    Vector B;
    Vector C;

    Triangle() : A(0.0, 0.0), B(0.0, 0.0), C(0.0, 0.0) {}
    Triangle(const Vector& a, const Vector& b, const Vector& c) : A(a), B(b), C(c) {}

    float square() const {
        Vector AB = B - A;
        Vector AC = C - A;
        return abs(crossProduct(AB, AC)) * 0.5f;
    }

    void move(const Vector& shift) {
        A += shift;
        B += shift;
        C += shift;
    }
};