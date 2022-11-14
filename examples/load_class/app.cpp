#include "class_template.hpp"
#include "sodl.hpp"
#include <iostream>

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
    auto create_object = lib.get_function<Entity *>("create_object");
    if (!create_object) {
      std::cout << "Function is not valid: " << lib.error() << std::endl;
      lib.close();
      continue;
    }
    auto delete_object = lib.get_function<void, Entity *>("delete_object");
    if (!delete_object) {
      std::cout << "Function is not valid: " << lib.error() << std::endl;
      lib.close();
      continue;
    }
    Entity *something = create_object();
    something->do_sound_times(count++);
    delete_object(something);
    lib.close();
  };
  return EXIT_SUCCESS;
}