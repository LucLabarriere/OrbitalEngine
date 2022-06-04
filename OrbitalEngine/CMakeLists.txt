cmake_minimum_required(VERSION 3.16.0)
project(OrbitalEngine VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 23)


file(GLOB_RECURSE SOURCES
	*.cpp
	*.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

if (MSVC)
target_compile_options(${PROJECT_NAME} PRIVATE "/wd6011")
target_compile_options(${PROJECT_NAME} PRIVATE "/FIOrbitalEngine/Utils/Context.h")
endif()
target_compile_definitions(${PROJECT_NAME} PUBLIC ORBITAL_OPENGL)
target_compile_definitions(${PROJECT_NAME} PUBLIC ORBITAL_DEBUG)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
		${CMAKE_SOURCE_DIR}/vendor/glm
		${CMAKE_SOURCE_DIR}/vendor/glad/include
		${CMAKE_SOURCE_DIR}/vendor/glfw/include
		${CMAKE_SOURCE_DIR}/vendor/imgui/
		${CMAKE_SOURCE_DIR}/vendor/entt/single_include
		${CMAKE_SOURCE_DIR}/vendor/fmt/include
		${CMAKE_SOURCE_DIR}/vendor/assimp/include
		${CMAKE_SOURCE_DIR}/vendor/uuid_v4/
	PRIVATE
		src
)

target_precompile_headers(${PROJECT_NAME} PUBLIC include/OrbitalEngine/Utils/Context.h)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		glad2
		glfw
		imgui
		fmt::fmt
		assimp::assimp
)
