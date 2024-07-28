#pragma once

#ifdef GP_PLATFORM_WINDOWS
#ifdef GP_BUILD_DLL
#define GRAPE_API __declspec(dllexport)
#else
#define GRAPE_API __declspec(dllimport)
#endif
#endif // GP_PLATFORM_WINDOWS

#ifdef GP_ENABLE_ASSERTS
#define GP_ASSERT(x, ...) { if(!(x)) { GP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define GP_CORE_ASSERT(x, ...) { if(!(x)) { GP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define GP_ASSERT(x, ...)
#define GP_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define GP_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)