struct A { long long a; };            //   8
struct B: virtual A { long long b; }; // + 24 (16 + 8(ссылка на A))
struct C: A { long long c; };         // + 16
struct D: B, C {long long d; };       // = 48