#include <iostream>
#include "dynamic.hpp"

DYNAMIC_PREFIX void do_sound_times(int n) {
  while (n--) {
    std::cout << "Beep ";
  }
  std::cout << std::endl;
}