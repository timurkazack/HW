struct A1 { long long a; };
struct A2 { long long a; };

struct B: virtual A1, A2 { long long b; }; //32
struct C: virtual A1, A2 { long long c; }; //32
struct D: B, C {long long d; };            //64