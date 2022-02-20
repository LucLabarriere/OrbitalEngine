cmake_minimum_required(VERSION 3.0.0)
project(glad2 VERSION 0.1.36)

add_library(${PROJECT_NAME}
	STATIC
		src/gl.c
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
)
