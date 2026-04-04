#include <iostream>
#include <cmath>

using namespace std;


class Wrap {
private:
    float (*first_func)(float);
    float (*second_func)(float);
public:
    Wrap(float (*f1)(float), float (*f2)(float)) : first_func(f1), second_func(f2) {}

    float operator()(float x) const {
        return second_func(first_func(x));
    }
};


float Radian2Degree(float in) {
    return in * (180.f / M_PI);
}

float Degree2Radian(float in) {
    return in * (M_PI / 180.f);
}

int main() {
    const Wrap wcos(Degree2Radian, cos);
    const Wrap wsin(Degree2Radian, sin);
    const Wrap watan(atan, Radian2Degree);
    cout << wsin(90);


    return 0;
}