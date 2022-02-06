cmake_minimum_required(VERSION 3.0.0)
project(imgui VERSION 1.86)

file(GLOB_RECURSE SOURCES
	*.cpp
	*.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
		${CMAKE_SOURCE_DIR}/vendor/glfw/include
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
