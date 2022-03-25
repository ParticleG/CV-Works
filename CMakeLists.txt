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

add_executable(${PROJECT_NAME} main.cpp Work_baseClass.cpp Work_baseClass.h Work_1.cpp Work_1.h Work_2.cpp Work_2.h Work_3.cpp Work_3.h Work_4.cpp Work_4.h Work_5.cpp Work_5.h Work_6.cpp Work_6.h Work_7.cpp Work_7.h Work_8.cpp Work_8.h Work_9.cpp Work_9.h Work_10.cpp Work_10.h Work_11.cpp Work_11.h Work_12.cpp Work_12.h Work_13.cpp Work_13.h Work_14.cpp Work_14.h Work_15.cpp Work_15.h)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ROOT_SRC)

target_sources(${PROJECT_NAME} PRIVATE ROOT_SRC)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
        ${OpenCV_INCLUDE_DIR}
)