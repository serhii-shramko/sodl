// sodl
// MIT License
//
// Copyright (c) 2022 serhii-shramko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef SODL_HPP
#define SODL_HPP

#include <cstring>
#include <functional>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#define SODL_OPEN_LIBRARY(lib_name) LoadLibraryA(lib_name)
#define SODL_CLOSE_LIBRARY FreeLibrary
#define SODL_LOAD_FUNCTION GetProcAddress
#define SODL_HANDLE_TYPE HMODULE
#else
#include <dlfcn.h>
#define SODL_OPEN_LIBRARY(lib_name) dlopen(lib_name, RTLD_NOW | RTLD_GLOBAL)
#define SODL_CLOSE_LIBRARY dlclose
#define SODL_LOAD_FUNCTION dlsym
#define SODL_HANDLE_TYPE void *
#endif

namespace sodl {
namespace util {
#ifdef _WIN32
static std::string last_error_as_string() {
  DWORD error_id = GetLastError();
  if (error_id == 0) {
    return std::string();
  }
  LPSTR buffer = nullptr;
  size_t size = FormatMessageA(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, error_id, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer,
      0, NULL);
  std::string error_string(buffer, size);
  LocalFree(buffer);
  return error_string;
}
#else
static std::string last_error_as_string() {
  const char *error_ptr = dlerror();
  if (error_ptr == nullptr)
    return std::string();
  size_t size = std::strlen(error_ptr) + 1;
  return std::string(error_ptr, size);
}
#endif
} // namespace util

class library {
public:
  inline library() = default;

  inline library(const std::string &file_name) { this->open(file_name); }

  inline ~library() { this->close(); }

  inline void open(const std::string &file_name) {
    if (m_handle != nullptr) {
      return;
    }
    m_handle = SODL_OPEN_LIBRARY(file_name.c_str());
  }

  inline void close() {
    if (m_handle == nullptr) {
      return;
    }
    SODL_CLOSE_LIBRARY(m_handle);
    m_handle = nullptr;
  }

  inline bool is_open() { return (m_handle != nullptr); }

  inline std::string error() { return util::last_error_as_string(); }

  template <typename Return, typename... Args>
  inline std::function<Return(Args...)>
  get_function(const std::string &function_name) {
    return (reinterpret_cast<Return (*)(Args...)>(
        SODL_LOAD_FUNCTION(m_handle, function_name.c_str())));
  }

private:
  SODL_HANDLE_TYPE m_handle = nullptr;
};
} // namespace sodl

#endif
