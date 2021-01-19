//
// Created by Parti on 2021/1/18.
//

#include "Work_11.h"

Work_11::Work_11() {
    addExercise({[](const string &filePath) {
        double lut[256];
        auto lutBuild = [&lut](double gamma) {
            for (int i = 0; i < 256; i++) {
                lut[i] = pow((i * 1.0 / 255), gamma) * 255;
            }
        };

        auto gamma = [&lut](Mat srcMat) {
            int height = srcMat.rows;
            int width = srcMat.cols;
            for (int j = 0; j < height; j++) {
                for (int i = 0; i < width; i++) {
                    srcMat.at<uchar>(j, i) = lut[srcMat.at<uchar>(j, i)];
                }
            }
        };

        Mat sourceImage = imread(filePath);
        lutBuild(0.45);
        gamma(sourceImage);
        imshow("sourceImage", sourceImage);

        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), channels[3], dstChannels[3], outputImage;
        split(sourceImage, channels);
        for (int i = 0; i < 3; i++) {
            equalizeHist(channels[i], dstChannels[i]);
        }
        merge(dstChannels, 3, outputImage);
        imshow("outputImage", outputImage);
        waitKey(0);
        return 0;
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        double lut[256];
        auto lutBuild = [&lut](double gamma) {
            for (int i = 0; i < 256; i++) {
                lut[i] = pow((i * 1.0 / 255), gamma) * 255;
            }
        };

        auto gamma = [&lut](Mat srcMat) {
            int height = srcMat.rows;
            int width = srcMat.cols;
            for (int j = 0; j < height; j++) {
                for (int i = 0; i < width; i++) {
                    srcMat.at<uchar>(j, i) = lut[srcMat.at<uchar>(j, i)];
                }
            }
        };

        Mat sourceImage = imread(filePath);
        lutBuild(0.44);
        gamma(sourceImage);
        imshow("sourceImage", sourceImage);

        waitKey(0);
    }, _defaultImageUrl});
}
