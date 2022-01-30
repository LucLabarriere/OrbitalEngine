cmake_minimum_required(VERSION 3.0.0)
project(OrbitalEngine VERSION 0.1.0)

add_compile_definitions(ORBITAL_OPENGL)

file(GLOB_RECURSE SOURCES
	src/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		ORBITAL_COMPILING
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
		${CMAKE_SOURCE_DIR}/vendor/glm
		${CMAKE_SOURCE_DIR}/vendor/glad/include
		${CMAKE_SOURCE_DIR}/vendor/glfw/include
		${CMAKE_SOURCE_DIR}/vendor/spdlog/include
	PRIVATE
		src
)

target_precompile_headers(${PROJECT_NAME} PUBLIC include/OrbitalEngine/Context.h)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		glad
		glfw
		spdlog
)
