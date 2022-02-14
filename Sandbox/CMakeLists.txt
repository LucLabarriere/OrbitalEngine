cmake_minimum_required(VERSION 3.16.0)
project(Sandbox VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/PROFILE")

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${CMAKE_SOURCE_DIR}/OrbitalEngine/include
	PRIVATE
		include
)

target_link_libraries(${PROJECT_NAME} PRIVATE OrbitalEngine)



add_executable(${PROJECT_NAME}NV ${SOURCES})
SET_TARGET_PROPERTIES(${PROJECT_NAME}NV PROPERTIES LINK_FLAGS "/PROFILE")

target_include_directories(${PROJECT_NAME}NV
	PUBLIC
		${CMAKE_SOURCE_DIR}/OrbitalEngine/include
	PRIVATE
		include
)

target_link_libraries(${PROJECT_NAME}NV PRIVATE OrbitalEngine)