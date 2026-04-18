struct A1 { long long a; };
struct A2 { long long a; };

struct B: virtual A1, virtual A2 { long long b; };
struct C: virtual A1, virtual A2 { long long c; };
struct D: B, C { long long d; };                   //56