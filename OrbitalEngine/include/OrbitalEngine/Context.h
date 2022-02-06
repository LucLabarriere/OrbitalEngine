#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <chrono>
#include <filesystem>
#include <sstream>
#include <signal.h>
#include <glm/glm.hpp>
#include <format>
#include <functional>

#ifdef __INTELLISENSE__
#pragma diag_suppress 2500
#endif

// OpenGL
#if defined(ORBITAL_OPENGL)
	#define GLFW_INCLUDE_NONE
	#include <GLFW/glfw3.h>
	#include <glad/glad.h>
#endif

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

// Setting up macros
#define OE_ASSERT(x, ...) { if(!(x)) { Logger::Critical(__VA_ARGS__); __debugbreak(); }}
#define OE_RAISE_SIGSEGV(...) { Logger::Critical(__VA_ARGS__); raise(SIGSEGV); }
#define OE_BIT(x) 1 << x

#include "Constants.h"