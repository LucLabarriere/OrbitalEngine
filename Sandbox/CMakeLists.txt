cmake_minimum_required(VERSION 3.0.0)
project(Sandbox VERSION 0.1.0)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${CMAKE_SOURCE_DIR}/OrbitalEngine/include
	PRIVATE
		include
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} PRIVATE OrbitalEngine)