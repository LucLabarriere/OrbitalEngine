#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <filesystem>
#include <sstream>
#include <signal.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

// OpenGL
#if defined(ORBITAL_OPENGL)

	#define GLFW_INCLUDE_NONE
	#include <GLFW/glfw3.h>
	#include <glad/glad.h>
#endif


// Setting up library import/export
#if defined(_MSC_VER)
//  Microsoft 
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)

#elif defined(__GNUC__)
//  GCC
#define EXPORT __attribute__((visibility("default")))
#define IMPORT

#else
#define EXPORT
#define IMPORT
#pragma warning Unknown dynamic link import/export semantics.
#endif

#if ORBITAL_COMPILING
#define ORBITAL_API EXPORT
#else
#define ORBITAL_API IMPORT
#endif

// Setting up macros
#define OE_INFO(msg, ...) spdlog::info(msg, __VA_ARGS__)
#define OE_ERROR(msg, ...) spdlog::error(msg, __VA_ARGS__)
#define OE_WARNING(msg, ...) spdlog::warn(msg, __VA_ARGS__)
#define OE_DEBUG(msg, ...) spdlog::debug(msg, __VA_ARGS__)
#define OE_ASSERT(x, ...) { if(!(x)) { OE_ERROR(__VA_ARGS__); __debugbreak(); }}
#define OE_RAISE_SIGSEGV(...) { OE_ERROR(__VA_ARGS__); raise(SIGSEGV); }

#include "Constants.h"