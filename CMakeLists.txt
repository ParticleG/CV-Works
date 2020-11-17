cmake_minimum_required(VERSION 3.17)
project(CV_Works)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV CONFIG REQUIRED)
if (OpenCV_FOUND)
    message("Found OpenCV. Version: " ${OpenCV_VERSION})
endif ()

add_executable(CV_Works main.cpp Work_1.cpp Work_1.h Work_2.cpp Work_2.h Work_3.cpp Work_3.h Work_4.cpp Work_4.h Work_5.cpp Work_5.h Work_6.cpp Work_6.h Work_7.cpp Work_7.h)

target_include_directories(CV_Works PRIVATE ${OpenCV_INCLUDE_DIR})
target_link_libraries(CV_Works ${OpenCV_LIBRARIES})