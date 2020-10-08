cmake_minimum_required(VERSION 3.17)
project(CV_Works)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV CONFIG REQUIRED)
if (OpenCV_FOUND)
    message("Found OpenCV. Version: " ${OpenCV_VERSION})
endif ()

add_executable(CV_Works main.cpp Work_1.cpp Work_1.h Work_2.cpp Work_2.h)

target_include_directories(CV_Works PRIVATE ${OpenCV_INCLUDE_DIR})
target_link_libraries(CV_Works ${OpenCV_LIBRARIES})