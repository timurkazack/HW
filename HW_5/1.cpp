struct A { long long a; };      //8
struct B: A { long long b; };   //   16
struct C: A { long long c; };   // + 16
struct D: B, C {long long d; }; // = 40