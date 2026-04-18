struct A { long long a; };
struct B: virtual A { long long b; };  // 24
struct C: virtual A { long long c; };  // 24
struct D: B, C {long long d; };        // 48 т.к. одно a убирается