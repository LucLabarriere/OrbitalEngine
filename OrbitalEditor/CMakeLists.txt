cmake_minimum_required(VERSION 3.16.0)
project(OrbitalEditor VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES
        *.cpp
        *.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

file(COPY ${CMAKE_SOURCE_DIR}/OrbitalEngine/assets DESTINATION ${CMAKE_BINARY_DIR}/OrbitalEditor)

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
