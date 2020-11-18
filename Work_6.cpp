//
// Created by Parti on 2020/11/17.
//

#include "Work_6.h"

Work_6::Work_6() {
    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
        float angle = -10.0, scale = 1.0;
        Point2f center(sourceImage.cols * 0.5, sourceImage.rows * 0.5);
        Mat affine_matrix = getRotationMatrix2D(center, angle, scale);
        Mat dst_mat;
        warpAffine(sourceImage, dst_mat, affine_matrix, sourceImage.size());
        imshow("src", sourceImage);
        imshow("dst", dst_mat);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
        Point2f src_pt[] = {
                Point2f(200, 200),
                Point2f(250, 200),
                Point2f(200, 100)
        };
        Point2f dst_pt[] = {
                Point2f(300, 100),
                Point2f(300, 50),
                Point2f(200, 100)
        };
        Mat affine_matrix = getAffineTransform(src_pt, dst_pt);
        Mat dst_mat;
        warpAffine(sourceImage, dst_mat, affine_matrix, sourceImage.size());
        imshow("src", sourceImage);
        imshow("dst", dst_mat);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
        Point2f src_pt[] = {
                Point2f(150, 150),
                Point2f(150, 300),
                Point2f(350, 300),
                Point2f(350, 150)
        };
        Point2f dst_pt[] = {
                Point2f(200, 150),
                Point2f(200, 300),
                Point2f(340, 270),
                Point2f(340, 180)
        };

        Mat perspectiveMatrix = getPerspectiveTransform(src_pt, dst_pt);
        Mat dst_mat;
        warpPerspective(sourceImage, dst_mat, perspectiveMatrix, sourceImage.size());
        imshow("src", sourceImage);
        imshow("dst", dst_mat);
        waitKey(0);
    }, _defaultImageUrl});
}