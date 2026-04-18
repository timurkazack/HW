#include <iostream>
#include <string>
using namespace std;
// прогал на CodeChef`е т.к. не было доступа к компу
// п.с. на код шефе работало но потом в вскод нет, незнаю почему

struct Point {
   int x, y;

   string get() {
      return '[' + to_string(x) + ", " + to_string(y) + ']';
   };

};


struct Triangle {

   union {
   struct { Point A, B, C; };
   Point array[3];
   };

   Triangle() : array{{0, 0}, {0, 0}, {0, 0}} {};

   void print() {
      cout << "A:" << A.get() << "\tB:" << B.get() << "\tC:" << C.get() << '\n';
   };

};

int main() {
   Triangle tr;
   tr.print();

   tr.A.x = 10;
   tr.print();

   tr.B.y = 0;
   tr.print();

   tr.C;
   tr.print();

   tr.array[1] = Point(1, 2);
   tr.print();

   return 0;

}