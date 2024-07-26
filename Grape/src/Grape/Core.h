#pragma once

#ifdef GP_PLATFORM_WINDOWS
#ifdef GP_BUILD_DLL
#define GRAPE_API __declspec(dllexport)
#else
#define GRAPE_API __declspec(dllimport)
#endif
#endif // GP_PLATFORM_WINDOWS
