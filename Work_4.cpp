//
// Created by Parti on 2020/11/17.
//

#include "Work_4.h"

Work_4::Work_4() {
    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), grayMat, binMat, erodeMat, kernel, dilateMat, openMat, closedMat;
        cvtColor(sourceImage, grayMat, COLOR_BGR2GRAY);
        threshold(grayMat, binMat, 82, 255, 0);
        Size mat_size = Size(5, 5);
        kernel = getStructuringElement(MORPH_RECT, mat_size);
        erode(binMat, erodeMat, kernel);
        dilate(binMat, dilateMat, kernel);

        Size matSize = Size(5, 5);
        Mat erode_mat, _kernel = getStructuringElement(MORPH_RECT, matSize);
        erode(binMat, erode_mat, _kernel);
        dilate(erode_mat, openMat, _kernel);

        Mat dilate_mat;
        erode(binMat, dilate_mat, kernel);
        dilate(dilate_mat, closedMat, kernel);

        imshow("binMat", binMat);
        imshow("erodeMat", erodeMat);
        imshow("dilateMat", dilateMat);
        imshow("openMat", openMat);
        imshow("closedMat", closedMat);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), grayMat, binMat, erodeMat, kernel, labels, stats, centroids;
        Size mat_size = Size(5, 5);

        cvtColor(sourceImage, grayMat, COLOR_BGR2GRAY);
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
    }, _defaultImageUrl});
}