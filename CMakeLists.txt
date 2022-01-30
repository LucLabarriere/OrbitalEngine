cmake_minimum_required(VERSION 3.0.0)
project(Orbital VERSION 0.1.0)

set(CMAKE_SUPPRESS_REGENERATION true)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

file(GLOB_RECURSE VENDOR_H "vendor/*.h")
set_source_files_properties(${VENDOR_H}
	PROPERTIES
	COMPILE_FLAGS "-w"
)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/spdlog)

# ExternalProject_Add(spdlog
#     PREFIX spdlog
#     SOURCE_DIR ${PROJECT_SOURCE_DIR}/vendor/spdlog
#     CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#     -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
#     -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
#     -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
#     -DCMAKE_INSTALL_PREFIX=${STAGING_DIR}
#     -DSPDLOG_BUILD_SHARED=OFF
# )

add_subdirectory(OrbitalEngine)
add_subdirectory(Sandbox)
