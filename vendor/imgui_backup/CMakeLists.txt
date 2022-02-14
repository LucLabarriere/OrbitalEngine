cmake_minimum_required(VERSION 3.0.0)
project(imgui VERSION 1.86)

add_library(${PROJECT_NAME} STATIC
	src/imgui.cpp
	src/imgui_draw.cpp
	src/imgui_tables.cpp
	src/imgui_widgets.cpp
	src/imgui_demo.cpp
	include/backends/imgui_impl_glfw.cpp
	include/backends/imgui_impl_glfw.h
	include/backends/imgui_impl_opengl3.cpp
	include/backends/imgui_impl_opengl3.h
	include/backends/imgui_impl_opengl3_loader.h
	include/imgui.h
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
		${CMAKE_SOURCE_DIR}/vendor/glfw/include
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
