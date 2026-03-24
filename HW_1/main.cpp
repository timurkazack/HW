#include <cmath>
using namespace std;



class Vector {
public:
    float x;
    float y;

    Vector() : x(0.0), y(0.0) {}
    Vector(float X, float Y) : x(X), y(Y) {}
    Vector(Vector& other) : x(other.x), y(other.y) {}

    void add(Vector& other) { x+=other.x; y+=other.y; }
    void sub(Vector& other) { x-=other.x; y-=other.y; }
    void mul(Vector& other) { x*=other.x; y*=other.y; }
    float length() { return sqrt(x*x + y*y); }
};



Vector sum(Vector& a, Vector& b) {
    return Vector((a.x + b.x), (a.y + b.y));
}

Vector dif(Vector& a, Vector& b) {
    return Vector((a.x - b.x), (a.y - b.y));
}

Vector mul(Vector& a, float s) {
    return Vector((a.x * s) , (a.y * s));
}

Vector mul(float s, Vector& a) {
    return Vector((a.x * s) , (a.y * s));
}

float dotProduct(Vector& a, Vector& b) {
    return a.x * b.x + a.y * b.y;
}

float crossProduct(Vector& a, Vector& b) {
    return a.x * b.y - a.y * b.x;
}



class Segment {
public:
    Vector a;
    Vector b;


    Segment() : a(0.0, 0.0), b(0.0, 0.0) {}
    Segment(Vector& A, Vector& B) : a(A), b(B) {}
    Segment(Segment& other) : a(other.a), b(other.b) {}

    float lenght() {
        return dif(a, b).length();
    }

    void move(Vector& shift) {
        a.add(shift);
        b.add(shift);
    }
};



class Circle {
public:
    Vector pos;
    float r;


    Circle() : pos(0.0, 0.0), r(0.0) {}
    Circle(Vector& Pos, float Radius) : pos(Pos), r(Radius) {}
    Circle(Circle& other) : pos(other.pos), r(other.r) {}

    float square() {
        return 3.14 * r *r;
    }

    void move(Vector& shift) {
        pos.add(shift);
    }
};



class Triangle {
public:
    Vector A;
    Vector B;
    Vector C;

    Triangle() : A(0.0, 0.0), B(0.0, 0.0), C(0.0, 0.0) {}
    Triangle(Vector& a,Vector& b, Vector& c) : A(a), B(b), C(c) {}

    float square() {
        Vector AB = dif(B, A);
        Vector AC = dif(C, A);
        
        return abs(crossProduct(AB, AC)) * 0.5;
    }

    void move(Vector& shift) {
        A.add(shift);
        B.add(shift);
        C.add(shift);
    }
};


int main() {
    return 0;
}
