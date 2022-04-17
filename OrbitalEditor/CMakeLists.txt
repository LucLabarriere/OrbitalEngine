cmake_minimum_required(VERSION 3.16.0)
project(OrbitalEditor VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 23)

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin)
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

file(GLOB_RECURSE SOURCES
        *.cpp
        *.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

if (MSVC)
target_compile_options(${PROJECT_NAME} PRIVATE "/FIOrbitalEngine/Utils/Context.h")
endif()

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${CMAKE_SOURCE_DIR}/OrbitalEngine/include
                ${CMAKE_SOURCE_DIR}/vendor/imgui/
                ${CMAKE_SOURCE_DIR}/vendor/entt/single_include
	PRIVATE
		include
)

target_link_libraries(${PROJECT_NAME} PRIVATE OrbitalEngine imgui)

add_executable(${PROJECT_NAME}NV ${SOURCES})

target_include_directories(${PROJECT_NAME}NV
	PUBLIC
		${CMAKE_SOURCE_DIR}/OrbitalEngine/include
		${CMAKE_SOURCE_DIR}/vendor/imgui/
		${CMAKE_SOURCE_DIR}/vendor/entt/single_include
	PRIVATE
		include
)

target_link_libraries(${PROJECT_NAME}NV PRIVATE OrbitalEngine)

add_custom_target(copy_assets
	COMMAND ${CMAKE_COMMAND}
	-DCMAKE_RUNTIME_OUTPUT_DIRECTORY="${CMAKE_SOURCE_DIR}/bin"
	-P ${CMAKE_CURRENT_LIST_DIR}/copy_assets.cmake
)

add_dependencies(${PROJECT_NAME} copy_assets)
add_dependencies(${PROJECT_NAME}NV copy_assets)

