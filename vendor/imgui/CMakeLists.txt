cmake_minimum_required(VERSION 3.0.0)
project(imgui VERSION 1.86)

add_library(${PROJECT_NAME} STATIC
	imgui.cpp
	imgui_draw.cpp
	imgui_tables.cpp
	imgui_widgets.cpp
	imgui_demo.cpp
	backends/imgui_impl_glfw.cpp
	backends/imgui_impl_glfw.h
	backends/imgui_impl_opengl3.cpp
	backends/imgui_impl_opengl3.h
	backends/imgui_impl_opengl3_loader.h
	imgui.h
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		./
		${CMAKE_SOURCE_DIR}/vendor/glfw/include
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
