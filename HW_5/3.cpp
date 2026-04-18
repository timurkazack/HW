//как 2.cpp
struct A { long long a; };            // 8
struct B: A { long long b; };         // 16
struct C: virtual A { long long c; }; // 24
struct D: B, C {long long d; };       // 48