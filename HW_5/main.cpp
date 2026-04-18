#include <iostream>
using namespace std;


struct Interface {
  void virtual metod1() = 0;
  /*
    другие методы.
  */
  virtual ~Interface() {}
};

int main() {
   cout << sizeof(Interface) << '\n'; // 8
   return 0;
};