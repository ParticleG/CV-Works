//
// Created by Parti on 2020/11/17.
//

#include "Work_3.h"

Work_3::Work_3() {
    _defaultImage = imread("C:/Users/Parti/Pictures/avatar.jpg");
}

void Work_3::runExercise(unsigned short select) {
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

void Work_3::exercise_1() {
    VideoCapture videoCapture(0);
    double scale = 0.5,
            min_H = 0, max_H = 20,
            min_S = 43, max_S = 255,
            min_V = 55, max_V = 255;
    do {
        Mat frameMat, hsvMat, detectMat, resizeMat;
        videoCapture >> frameMat;
        Size matSize = Size(frameMat.cols * scale, frameMat.rows * scale);
        resizeMat = Mat(matSize, frameMat.type());
        resize(frameMat, resizeMat, matSize, INTER_LINEAR);
        cvtColor(resizeMat, hsvMat, COLOR_BGR2HSV);
        resizeMat.copyTo(detectMat);
        inRange(hsvMat, Scalar(min_H, min_S, min_V), Scalar(max_H, max_S, max_V), detectMat);
        imshow("in the range ", detectMat);
        imshow("frameMat", frameMat);
    } while (waitKey(30) == -1);
}

void Work_3::exercise_2() {
    Mat grayMat, binMat, adaptMat;
    cvtColor(_defaultImage, grayMat, COLOR_BGR2GRAY);
    threshold(grayMat, binMat, 100, 255, THRESH_OTSU);
    adaptiveThreshold(grayMat, adaptMat, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);
    imshow("srcMat", _defaultImage);
    imshow("binMat", binMat);
    imshow("adaptMat", adaptMat);
    waitKey(0);
}

void Work_3::exercise_3() {
    Mat grayMat;
    int lowTh = 30, maxTh = 255;
    cvtColor(_defaultImage, grayMat, COLOR_BGR2GRAY);
    imshow("binMat", grayMat);
    createTrackbar("threshold", "binMat", &lowTh, maxTh, [](int th, void * data) {
        Mat src_mat = *(Mat *) data;
        Mat dst_mat;
        threshold(src_mat, dst_mat, th, 255, 0);
        imshow("threshold", dst_mat);
    }, &grayMat);
    waitKey(0);
}
