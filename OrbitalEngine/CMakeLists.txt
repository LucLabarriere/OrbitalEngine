cmake_minimum_required(VERSION 3.0.0)
project(OrbitalEngine VERSION 0.1.0)

file(GLOB SOURCES src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
	PRIVATE
		src
)

target_precompile_headers(${PROJECT_NAME} PUBLIC include/OrbitalEngine/Context.h)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)