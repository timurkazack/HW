#include <iostream>
using namespace std;

class Massive {
private:
   int len;
   int* massive;
   
   void create_massive(int length) {
      massive = new int[length]();
   }
   
   void create_massive(int length, int value) {
      massive = new int[length];
      for (int i = 0; i < length; i++) {
         massive[i] = value;
      }
   }
   
   void del_massive() {
      delete[] massive;
   }

public:
   Massive() : len(0), massive(nullptr) {}
   
   Massive(int count_elements) : len(count_elements) {
      create_massive(len);}
   
   Massive(int count_elements, int elements) : len(count_elements) {
      create_massive(len, elements);}
   
   Massive(const Massive& other) : len(other.len) {
      massive = new int[len];
      for (int i = 0; i < len; i++) {
         massive[i] = other.massive[i];
      }
   }
   
   ~Massive() {
      if (massive != nullptr) {
         del_massive();
      }
   }
   
   Massive& operator=(const Massive& other) {
      if (this != &other) {
         if (massive != nullptr) {
            del_massive();
         }
         len = other.len;
         massive = new int[len];
         for (int i = 0; i < len; i++) {
            massive[i] = other.massive[i];
         }
      }
      return *this;
   }
   
   int operator[](int index) const {
      return massive[index];
   }
   
   int& operator[](int index) {
      return massive[index];
   }
   
   void clear() {
      if (massive != nullptr) {
         del_massive();
      }
      massive = nullptr;
      len = 0;
   }
   
   void resize(int new_len) {
      if (massive != nullptr) {
         del_massive();
      }
      len = new_len;
      massive = new int[len]();
   }
   
   void resize(int new_len, int value) {
      if (massive != nullptr) {
         del_massive();
      }
      len = new_len;
      massive = new int[len];
      for (int i = 0; i < len; i++) {
         massive[i] = value;
      }
   }
   
   int size() const {
      return len;
   }
   
   bool empty() const {
      return len == 0;
   }
};

int main() {
  Massive a; // память не должна выделяться
  Massive b(10); // память выделяется на 10 элементов, каждый равен 0
  Massive c(11, 5); // память выделяется на 11 элементов, каждый равен 0  // тут наверное имеллось ввиду заполнить все 5 
  const Massive d(b); // копирует массив.
  
  // функции
  b.clear(); // возвращает память в кучу. Размер 0;
  c.resize(10); // делает новый размер, удаляет старый массив, выделяет новый. Заполняет его 0
  c.resize(99, 77); // делает новый размер, удаляет старый массив, выделяет новый. Заполняет его 77
  d.size(); // возращает длину массива
  d.empty(); // если массив пуст возращает true, иначе false

  std::cout << d[4]; // есть обращение по номеру
  c[4] = 100; // можно менять по номеру.

  a = b; // есть оператор присваивания.

  return 0;
}