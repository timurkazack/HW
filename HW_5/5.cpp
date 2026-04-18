struct A { long long a; };
struct B: A { long long b; };
struct C: A { long long c; };
struct D: virtual B, virtual C {long long d; };   // тут просто сумма всех, и виртуал решает только для наследников этого класса