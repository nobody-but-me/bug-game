
cmake_minimum_required(VERSION 3.21)
project(BUG CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
	${CMAKE_SOURCE_DIR}/core/libs/
	${CMAKE_SOURCE_DIR}/core/
)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
	# ${CMAKE_SOURCE_DIR}/core/renderer/*.cpp
	# ${CMAKE_SOURCE_DIR}/core/physics/*.cpp
	${CMAKE_SOURCE_DIR}/core/backend/*.cpp
	# ${CMAKE_SOURCE_DIR}/core/editor/*.cpp
	# ${CMAKE_SOURCE_DIR}/core/utils/*.cpp
	# ${CMAKE_SOURCE_DIR}/core/audio/*.cpp
	# ${CMAKE_SOURCE_DIR}/core/files/*.cpp
	${CMAKE_SOURCE_DIR}/core/libs/*.cpp
	# ${CMAKE_SOURCE_DIR}/core/math/*.cpp
	
	# ${CMAKE_SOURCE_DIR}/game/player/*.cpp
	# ${CMAKE_SOURCE_DIR}/game/camera/*.cpp
	# ${CMAKE_SOURCE_DIR}/game/levels/*.cpp
	# ${CMAKE_SOURCE_DIR}/game/bugs/*.cpp
)

add_executable(bug ${CMAKE_SOURCE_DIR}/core/main.cpp ${SRC_FILES} ${CMAKE_SOURCE_DIR}/core/libs/glad.c)
target_compile_options(bug PRIVATE -Wall -Werror)
target_link_libraries(bug PRIVATE glfw)


