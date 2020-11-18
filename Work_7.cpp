//
// Created by Parti on 2020/11/17.
//

#include "Work_7.h"

Work_7::Work_7() {
    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), outputImage;
        float angle = -10.0, scale = 1;
        Point2f center(sourceImage.cols / 2.0, sourceImage.rows / 2.0);
        Mat rot = getRotationMatrix2D(center, angle, scale);
        Rect bbox = RotatedRect(center, sourceImage.size(), angle).boundingRect();
        rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
        rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

        warpAffine(sourceImage, outputImage, rot, bbox.size());

        imshow("src", sourceImage);
        imshow("dst", outputImage);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), cannyImage;
        Canny(sourceImage, cannyImage, 150, 200);
        vector<Vec2f> lines;
        HoughLines(cannyImage, lines, 1, CV_PI / 180, 100);

        for (auto tempLine : lines) {
            float rho = tempLine[0], theta = tempLine[1];
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta), x0 = a * rho, y0 = b * rho;
            pt1.x = saturate_cast<int>(x0 + 1000 * (-b));
            pt1.y = saturate_cast<int>(y0 + 1000 * (a));
            pt2.x = saturate_cast<int>(x0 - 1000 * (-b));
            pt2.y = saturate_cast<int>(y0 - 1000 * (a));
            line(sourceImage, pt1, pt2, Scalar(0, 0, 255), 1);
        }
        imshow("src", sourceImage);
        imshow("canny", cannyImage);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), cannyImage;
        Canny(sourceImage, cannyImage, 150, 200);
        vector<Vec4i> lines;

        HoughLinesP(cannyImage, lines, 1, CV_PI / 180, 30, 5, 10);

        for (auto tempLine : lines) {
            cv::Point pt1, pt2;
            pt1.x = tempLine[0];
            pt1.y = tempLine[1];
            pt2.x = tempLine[2];
            pt2.y = tempLine[3];
            cv::line(sourceImage, pt1, pt2, Scalar(255, 0, 0), 1);
        }

        imshow("srcMat", sourceImage);
        imshow("CannyMat", cannyImage);
        waitKey(0);
    }, _defaultImageUrl});
}