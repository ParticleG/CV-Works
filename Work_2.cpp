//
// Created by Particle_G on 2020/10/8.
//

#include "Work_2.h"

Work_2::Work_2() {
    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
        vector<Mat> channels;
        split(sourceImage, channels);
        imshow("red", channels.at(2));
        imshow("blue", channels.at(1));
        imshow("green", channels.at(0));
        imshow("original Mat", sourceImage);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        VideoCapture videoCapture;
        videoCapture.open(filePath);
        if (!videoCapture.isOpened()) {
            cout << "Cannot open video file." << endl;
            return;
        }
        double fps = videoCapture.get(CAP_PROP_FPS);
        cout << "Video FPS: " << fps << endl;
        while (true) {
            Mat frame;
            bool isReadSuccess = videoCapture.read(frame);
            if (!isReadSuccess) {
                cout << "Can't read frames from the video." << endl;
                break;
            } else {
                imshow("Frame", frame);
            }
            if (waitKey(static_cast<int>(1000 / fps)) != -1) {
                break;
            }
        }
    }, _defaultVideoUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
        circle(sourceImage, Point(10, 10), 5, CV_RGB(255, 0, 0), 1, 8, 0);
        line(sourceImage, Point(10, 10), Point(30, 30), CV_RGB(255, 0, 0), 1, 8, 0);
        rectangle(sourceImage, Rect(10, 10, 20, 10), CV_RGB(255, 0, 0), 1, 8, 0);
        imshow("Draw", sourceImage);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), gray;
        cvtColor(sourceImage, gray, COLOR_RGB2GRAY);

        int grades = 256, hist_size[] = {grades}, channels[] = {0};
        float range[] = {0, 256};
        const float *ranges[] = {range};
        MatND hist;
        calcHist(&gray, 1, channels, Mat(), // do not use mask
                 hist,
                 1,
                 hist_size,
                 ranges,
                 true, // the histogram is uniform
                 false);

    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), gray;
        cvtColor(sourceImage, gray, COLOR_RGB2GRAY);
        int grades = 256, hist_size[] = {grades}, channels[] = {0};
        float range[] = {0, 256};
        const float *ranges[] = {range};
        MatND hist;
        calcHist(&gray, 1, channels, Mat(), // do not use mask
                 hist,
                 1, hist_size,
                 ranges,
                 true, // the histogram is uniform
                 false);
        double max_val;
        minMaxLoc(hist, nullptr, &max_val, nullptr, nullptr);
        int scale = 2, hist_height = 300;
        Mat hist_img = Mat::zeros(hist_height, grades * scale, CV_8UC3);
        for (int i = 0; i < grades; i++) {
            float bin_val = hist.at<float>(i);
            int intensity = cvRound(bin_val * static_cast<float>(hist_height) / max_val);
            rectangle(hist_img, Point(i * scale, hist_height/* - 1*/),
                      Point((i + 1) * scale - 1, hist_height - intensity),
                      CV_RGB(255, 255, 255));
        }
        imshow("Gray Histogram", hist_img);
        waitKey(0);
    }, _defaultImageUrl});
}
