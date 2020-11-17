//
// Created by Parti on 2020/11/17.
//

#include "Work_4.h"

Work_4::Work_4() {
    _defaultImage = imread("./Coin.jpg");
}

void Work_4::runExercise(unsigned short select) {
    switch (select) {
        case 1:
            exercise_1();
            break;
        case 2:
            exercise_2();
            break;
        default:
            cout << "Unknown exercise number, could be 1 to 2" << endl;
            break;
    }
}

void Work_4::exercise_1() {
    Mat grayMat, binMat, erodeMat, kernel, dilateMat, openMat, closedMat;
    cvtColor(_defaultImage, grayMat, COLOR_BGR2GRAY);
    threshold(grayMat, binMat, 82, 255, 0);
    Size mat_size = Size(5, 5);
    kernel = getStructuringElement(MORPH_RECT, mat_size);
    erode(binMat, erodeMat, kernel);
    dilate(binMat, dilateMat, kernel);
    _open(binMat, openMat);
    _close(binMat, closedMat);
    imshow("binMat", binMat);
    imshow("erodeMat", erodeMat);
    imshow("dilateMat", dilateMat);
    imshow("openMat", openMat);
    imshow("closedMat", closedMat);
    waitKey(0);
}

void Work_4::exercise_2() {
    Mat grayMat, binMat, erodeMat, kernel, labels, stats, centroids;
    Size mat_size = Size(5, 5);

    cvtColor(_defaultImage, grayMat, COLOR_BGR2GRAY);
    threshold(grayMat, binMat, 82, 255, 0);
    kernel = getStructuringElement(MORPH_RECT, mat_size);
    erode(binMat, erodeMat, kernel);
    connectedComponentsWithStats(erodeMat, labels, stats, centroids);
    int height = stats.rows;
    for (int i = 0; i < height; ++i) {
        int *data = stats.ptr<int>(i);
        rectangle(erodeMat, Point(data[0], data[1]),
                  Point(data[0] + data[2], data[1] + data[3]),
                  Scalar(255, 0, 0));
    }
    std::cout << height << std::endl;
    imshow("binMat", binMat);
    imshow("erodeMat", erodeMat);
    waitKey(0);
}

void Work_4::_open(Mat &src, Mat &dst) {
    Size matSize = Size(5, 5);
    Mat erode_mat, kernel = getStructuringElement(MORPH_RECT, matSize);
    erode(src, erode_mat, kernel);
    dilate(erode_mat, dst, kernel);
}

void Work_4::_close(Mat &src, Mat &dst) {
    Size matSize = Size(5, 5);
    Mat dilate_mat, kernel = getStructuringElement(MORPH_RECT, matSize);
    erode(src, dilate_mat, kernel);
    dilate(dilate_mat, dst, kernel);
}