//
// Created by Parti on 2020/11/17.
//

#include "Work_5.h"

Work_5::Work_5() {
    _defaultImage = imread("C:/Users/Parti/Pictures/avatar.jpg");
}

void Work_5::runExercise(unsigned short select) {
    switch (select) {
        case 1:
            exercise_1();
            break;
        case 2:
            exercise_2();
            break;
        case 3:
            exercise_3();
            break;
        default:
            cout << "Unknown exercise number, could be 1 to 3" << endl;
            break;
    }
}

void Work_5::exercise_1() {
    VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened()) {
        std::cout << "Open Failed !" << std::endl;
        return;
    }
    double fps = cap.get(CAP_PROP_FPS);
    std::cout << "fps = " << fps << std::endl;
    do {
        cv::Mat frame;
        if (!(cap.read(frame))) {
            std::cout << "Read Failed !" << std::endl;
            return;
        } else {
            cv::Mat dst;
            medianBlur(frame, dst, 3);
            imshow("frame", dst);
        }
    } while (waitKey(30) == -1);
}

void Work_5::exercise_2() {
    VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened()) {
        std::cout << "Open Failed !" << std::endl;
        return;
    }
    double fps = cap.get(CAP_PROP_FPS);
    std::cout << "fps = " << fps << std::endl;
    do {
        cv::Mat frame;
        if (!(cap.read(frame))) {
            std::cout << "Read Failed !" << std::endl;
            return;
        } else {
            cv::Mat dst;
            Size mat_size = Size(5, 5);
            blur(frame, dst, mat_size);
            imshow("frame", dst);
        }
    } while (waitKey(30) == -1);
}

void Work_5::exercise_3() {
    VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened()) {
        std::cout << "Open Failed !" << std::endl;
        return;
    }
    double fps = cap.get(CAP_PROP_FPS);
    std::cout << "fps = " << fps << std::endl;
    do {
        cv::Mat frame;
        if (!(cap.read(frame))) {
            std::cout << "Read Failed !" << std::endl;
            return;
        } else {
            cv::Mat dst, gaussi_mat, gry_mat;
            Size mat_size = Size(5, 5);
            GaussianBlur(frame, gaussi_mat, mat_size, 0);
            cvtColor(gaussi_mat, gry_mat, COLOR_BGR2GRAY);
            Sobel(gry_mat, dst, CV_16SC1, 1, 0, 5);
            imshow("frame", dst);
        }
    } while (waitKey(30) == -1);
}