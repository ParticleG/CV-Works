//
// Created by Parti on 2021/1/18.
//

#include "Work_8.h"

Work_8::Work_8() {
    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), outputImage = imread(filePath), binaryImage;
        threshold(sourceImage, binaryImage, 125, 175, THRESH_BINARY_INV);
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(binaryImage, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

        for (int i = 0; i < contours.size(); i++) {
            RotatedRect rBox = minAreaRect(contours[i]);
            float width = (float) rBox.size.width,
                    height = (float) rBox.size.height,
                    ratio = width / height,
                    pixel = width * height;
            if (pixel > 1000 && fabs(ratio - 1) < 0.1) {
                cv::Point2f vtx[4];
                rBox.points(vtx);
                for (int j = 0; j < 4; ++j) {
                    line(outputImage, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0, 0, 255), 2);
                }
                drawContours(outputImage, contours, i, Scalar(0, 255, 255), -1, 8);
            }
        }
        imshow("sourceImage", sourceImage);
        imshow("binaryImage", binaryImage);
        imshow("outputImage", outputImage);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), openImage, binaryImage, grayImage, outputImage;
        vector<vector<Point>> contours;

        sourceImage.copyTo(outputImage);
        cvtColor(sourceImage, grayImage, COLOR_BGR2GRAY);
        threshold(grayImage, binaryImage, 0, 255, THRESH_OTSU);
        morphologyEx(binaryImage, openImage, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(5, 5)));
        findContours(openImage, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

        for (int i = 0; i < contours.size(); i++) {
            RotatedRect rBox = minAreaRect(contours[i]);
            cv::Point2f vertex[4];
            rBox.points(vertex);
            float width = rBox.size.width;
            float height = rBox.size.height;
            float pixel = width * height;

            if (pixel > 50 * 50) {
                drawContours(outputImage, contours, i, Scalar(0, 0, 255), 1, 8);
                for (int j = 0; j < 4; j++) {
                    cv::line(outputImage, vertex[j], vertex[(j + 1) % 4], Scalar(255, 255, 0), 1, LINE_AA);
                }
            }
        }
        imshow("outputImage", outputImage);
        imshow("sourceImage", sourceImage);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat srcMat = imread(filePath), hsv, gray, bin1, bin2, bin, Result;
        vector<vector<Point>> contours;
        int minH = 0, maxH = 20, minS = 43, maxS = 255, minV = 55, maxV = 255;
        Point2f vtx[4];

        resize(srcMat, srcMat, Size(400, 400));
        cvtColor(srcMat, hsv, COLOR_BGR2HSV);
        srcMat.copyTo(Result);
        inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), bin1);
        minH = 160;
        maxH = 180;
        inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), bin2);
        bitwise_or(bin1, bin2, bin);
        findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

        for (auto &contour : contours) {
            RotatedRect rBox = minAreaRect(contour);
            rBox.points(vtx);
            float width = rBox.size.width;
            float height = rBox.size.height;
            float area = width * height;
            if (area > 1000) {
                for (int j = 0; j < 4; j++) {
                    line(Result, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 255, 255), 2);
                }
            }
        }
        imshow("srcMat", srcMat);
        imshow("result", Result);
        waitKey(0);
    }, _defaultImageUrl});
}
