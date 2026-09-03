cmake_minimum_required(VERSION 3.28)

project(SideScrollerPrototype)

# TODO: Try 20 soon
set(CMAKE_CXX_STANDARD 17)

# Tried this, does not work
#find_package(raylib 6.0 REQUIRED)

set(RAYLIB_DIR "raylib-6.0_win64_msvc16")
set(RAYLIB_LIB_DIR "raylib-6.0_win64_msvc16/lib")
include_directories(${RAYLIB_DIR}/include)
link_directories(${RAYLIB_LIB_DIR})

file(GLOB_RECURSE SOURCES src/*.cpp)

# Note main.cpp not in src folder
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src)

# These are for Windows only
target_link_libraries(${PROJECT_NAME} raylib opengl32 gdi32 winmm)

# Additional CMAKE conf (for IDE)
set(CMAKE_BUILD_TYPE DEBUG)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/Debug)