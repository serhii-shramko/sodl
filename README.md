# sodl
sodl is a C++ cross-platform dlopen/LoadLibrary wrapper 

# Example
```cpp
#include <iostream>

#include "sodl.hpp"

int main(int argc, char **argv) {
  sodl::library lib("./lib_name.so");
  if (!lib.is_open()) {
    std::cout << "Library is not open: " << lib.error() << std::endl;
    return EXIT_FAILURE;
  }
  auto func = lib.get_function<void>("myname");
  if (!func) {
    std::cout << "Function not valid: " << lib.error() << std::endl;
    return EXIT_FAILURE;
  }
  func();
  return EXIT_SUCCESS;
}
```
