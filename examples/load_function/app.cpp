#include <iostream>

#include "sodl.hpp"

int main(int argc, char **argv) {
  sodl::library lib;
  std::string input;
  std::cout << "Type 'exit' to exit." << std::endl;
  int count = 1;
  while (true) {
    std::cout << "Enter dynamic library name: ";
    std::cin >> input;
    if (input == "exit")
      break;
    lib.open(input);
    if (!lib.is_open()) {
      std::cout << "Library is not opened: " << lib.error() << std::endl;
      continue;
    }
    auto do_sound_times = lib.get_function<void, int>("do_sound_times");
    if (!do_sound_times) {
      std::cout << "Function is not valid: " << lib.error() << std::endl;
      lib.close();
      continue;
    }
    do_sound_times(count++);
    lib.close();
  };
  return EXIT_SUCCESS;
}