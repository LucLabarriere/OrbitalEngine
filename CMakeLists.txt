cmake_minimum_required(VERSION 3.16.0)
project(Orbital VERSION 0.1.0)

if(MSVC)
message("Using MSVC " ${MSVC_VERSION})
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/fmt)

add_subdirectory(OrbitalEngine)
add_subdirectory(Sandbox)
