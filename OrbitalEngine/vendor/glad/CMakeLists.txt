cmake_minimum_required(VERSION 3.0.0)
project(glad VERSION 2.0.0)

add_library(${PROJECT_NAME}
	STATIC
		src/glad.c
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
)

message("Project set to ${CMAKE_BUILD_TYPE} mode")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
