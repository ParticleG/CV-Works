cmake_minimum_required(VERSION 3.17)
project(CVTest)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV CONFIG REQUIRED)
if (OpenCV_FOUND)
    message("Found OpenCV. Version: " ${OpenCV_VERSION})
endif ()

add_executable(CVTest main.cpp Work_1.cpp Work_1.h)

target_include_directories(CVTest PRIVATE ${OpenCV_INCLUDE_DIR})
target_link_libraries(CVTest ${OpenCV_LIBRARIES})