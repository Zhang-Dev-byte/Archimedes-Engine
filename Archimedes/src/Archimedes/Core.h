#pragma once
#ifdef AC_BUILD_DLL
#define AC_API __declspec(dllexport)
#else
#define AC_API __declspec(dllimport)
#endif