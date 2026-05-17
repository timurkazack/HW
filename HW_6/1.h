#pragma once
#include <list>
template<class T, class Func>
void clean(std::list<T>& in, const Func& func) {
   // func это условие по которому удаляется элемент
   // Так как это шаблон, он может быть функцией.
   for (auto it = in.begin(); it != in.end(); ++ it) {
      if (func(*it)) {
         /*
         Твой код.
         Нужно удалить элемент по итератору. 
         При этом ничего не должно сломаться :3
         */
         // окей
         it = in.erase(it);
         --it;
      }
      //else ++it;
   }
};