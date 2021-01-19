//
// Created by Parti on 2020/12/30.
//

#include "Work_14.h"

Work_14::Work_14() {
    addExercise({[](const string &filePath) {
        auto createMaskByKMeans = [](const Mat &src, Mat &mask) {
            if ((mask.type() != CV_8UC1) || (src.size() != mask.size())) {
                return 0;
            }
            int width = src.cols, height = src.rows, pixNum = width * height, clusterCount = 2;
            Mat labels, centers, sampleData = src.reshape(3, pixNum), km_data;
            sampleData.convertTo(km_data, CV_32F);
            TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
            kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);
            uchar fg[2] = {0, 255};
            for (int row = 0; row < height; row++) {
                for (int col = 0; col < width; col++) {
                    mask.at<uchar>(row, col) = fg[labels.at<int>(row * width + col)];
                }
            }
            return 0;
        };

        Mat sourceImage = imread(filePath);
        Mat mask = Mat::zeros(sourceImage.size(), CV_8UC1);
        createMaskByKMeans(sourceImage, mask);
        imshow("sourceImage", sourceImage);
        imshow("mask", mask);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        auto createMaskByKMeans = [](const Mat &src, Mat &mask) {
            if ((mask.type() != CV_8UC1) || (src.size() != mask.size())) {
                return 0;
            }
            int width = src.cols, height = src.rows, pixNum = width * height, clusterCount = 2;
            Mat labels, centers, sampleData = src.reshape(3, pixNum), km_data;
            sampleData.convertTo(km_data, CV_32F);
            TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
            kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);
            uchar fg[2] = {0, 255};
            for (int row = 0; row < height; row++) {
                for (int col = 0; col < width; col++) {
                    mask.at<uchar>(row, col) = fg[labels.at<int>(row * width + col)];
                }
            }
            if (mask.at<uchar>(0, 0) == 255) {
                mask = 255 - mask;
            }
            return 0;
        };

        VideoCapture captureBackGround(filePath);//背景
        VideoCapture capture(0);  //前景

        int keyReturn;
        do {
            Mat frame;
            Mat frameFront;
            Mat result;
            Mat people;
            captureBackGround >> frame;
            capture >> frameFront;

            resize(frameFront, people, frame.size());

            if ((frame.data != nullptr) && (people.data != nullptr)) {
                people.copyTo(result);
                Mat mask = Mat::zeros(frame.size(), CV_8UC1);
                createMaskByKMeans(frame, mask);

                for (int i = 0; i < frame.rows; i++) {
                    for (int j = 0; j < frame.cols; j++) {
                        if (mask.at<uchar>(i, j) == 255) {
                            result.at<Vec3b>(i, j)[0] = frame.at<Vec3b>(i, j)[0];
                            result.at<Vec3b>(i, j)[1] = frame.at<Vec3b>(i, j)[1];
                            result.at<Vec3b>(i, j)[2] = frame.at<Vec3b>(i, j)[2];
                        }
                    }
                }
                imshow("result", result);
                keyReturn = waitKey(30);
            } else {
                cout << "the Video Ends!";
                break;
            }
        } while (keyReturn == -1);
    }, _defaultImageUrl});
}
