#include <iostream>
#include "1.h"
#include <list>

// функция которая указывает какие элементы удалять
// тут удаляются отрицательные числа
bool checker(int num) { return num < 0; }

int main() {
  std::list<int> mylist = {-7, 1, -1, 2, 4, 6, -19, -8, -77, 7, 9, 0, -5};
  clean(mylist, checker);
  for (auto value: mylist) {
    std::cout << value << ' ';
  }
  std::cout << '\n';
}