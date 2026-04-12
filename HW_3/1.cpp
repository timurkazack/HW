#include <iostream>

using namespace std;

struct Bad {                // sizeof 48(best); aligof 16

   // group #4 (aligof 16)
   long double b;           // sizeof 16x1

   // group #3 (aligof 8)
   double c;                // sizeof 8x1
   long long e;             // sizeof 8x1
   
   // group #2 (aligof 4)
   int a;                   // sizeof 4x1
   float d;                 // sizeof 4x1

   // group #1 (aligof 1)
   char local_massive_2[5]; // sizeof 1x5
   bool local_massive_1[3]; // sizeof 1x3
};




int main() {

   cout << "alignof " << alignof(Bad) << '\n';
   cout << "sizeof " << sizeof(Bad) << '\n';

   /*
   Из этого следует мое правило:
      1. Сгрупировать переменные по выравниванию типа
      2. Расположить группы по убыванию выравнивания
   */


   return 0;
}