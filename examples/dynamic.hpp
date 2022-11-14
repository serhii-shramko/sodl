#pragma once

// Prefix to tag dynamic load function
#ifdef _WIN32
#define DYNAMIC_PREFIX extern "C" __declspec(dllexport)
#else
#define DYNAMIC_PREFIX extern "C"
#endif