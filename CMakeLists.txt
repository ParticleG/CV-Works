cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

message(STATUS "C++ standard set to ${CMAKE_CXX_STANDARD}")

project(CV-Works)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(STATUS "Compiler is Clang")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "Compiler is GCC")
    add_compile_options(-Wno-volatile -fcoroutines)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message(STATUS "Compiler is Intel C++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(STATUS "Compiler is Visual Studio C++")
    add_compile_options(/MP /utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS NOMINMAX)
endif ()

find_package(OpenCV CONFIG REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ROOT_SRC)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${ROOT_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBRARIES})

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/default.png DESTINATION ${CMAKE_BINARY_DIR})