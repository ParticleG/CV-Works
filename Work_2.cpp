//
// Created by Particle_G on 2020/10/8.
//

#include "Work_2.h"

Work_2::Work_2() {
    _defaultImage = imread("C:/Users/Parti/Pictures/avatar.jpg");
}

void Work_2::runExercise(unsigned short select) {
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
        case 4:
            exercise_4();
            break;
        case 5:
            exercise_5();
            break;
        default:
            cout << "Unknown exercise number, could be 1 to 5" << endl;
            break;
    }
}

void Work_2::exercise_1() {
    vector<Mat> channels;
    split(_defaultImage, channels);
    imshow("red", channels.at(2));
    imshow("blue", channels.at(1));
    imshow("green", channels.at(0));
    imshow("original Mat", _defaultImage);
    waitKey(0);
}

void Work_2::exercise_2() {
    VideoCapture videoCapture;
    videoCapture.open(R"(C:\Users\Particle_G\Videos\Ending_1080p60.mov)");
    if (!videoCapture.isOpened()) {
        cout << "不能打开视频文件" << endl;
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
}

void Work_2::exercise_3() {
    circle(_defaultImage, Point(10, 10), 5, CV_RGB(255, 0, 0), 1, 8, 0);
    line(_defaultImage, Point(10, 10), Point(30, 30), CV_RGB(255, 0, 0), 1, 8, 0);
    rectangle(_defaultImage, Rect(10, 10, 20, 10), CV_RGB(255, 0, 0), 1, 8, 0);
    imshow("Draw", _defaultImage);
    waitKey(0);
}

void Work_2::exercise_4() {
    Mat gray;
    cvtColor(_defaultImage, gray, COLOR_RGB2GRAY);

    int grades = 256;
    int hist_size[] = {grades};

    float range[] = {0, 256};
    const float *ranges[] = {range};
    MatND hist;

    int channels[] = {0};

    calcHist(&gray, 1, channels, Mat(), // do not use mask
             hist, //输出直方图
             1, hist_size,
             ranges,
             true, // the histogram is uniform
             false);
}

void Work_2::exercise_5() {
    Mat gray;
    cvtColor(_defaultImage, gray, COLOR_RGB2GRAY);

    int grades = 256;
    int hist_size[] = {grades};

    float range[] = {0, 256};
    const float *ranges[] = {range};
    MatND hist;

    int channels[] = {0};

    calcHist(&gray, 1, channels, Mat(), // do not use mask
             hist, //输出直方图
             1, hist_size,
             ranges,
             true, // the histogram is uniform
             false);

    double max_val;
    minMaxLoc(hist, nullptr, &max_val, nullptr, nullptr);//找出最大的bins值
    int scale = 2;//bins之间的距离为2
    int hist_height = 300;//输出直方图的高度

    Mat hist_img = Mat::zeros(hist_height, grades * scale, CV_8UC3);//定义hist_img的矩阵，高度为hist_height,宽度为bins*scale

    for (int i = 0; i < grades; i++) {
        float bin_val = hist.at<float>(i);

        int intensity = cvRound(bin_val * static_cast<float>(hist_height) / max_val);  //归一化，要绘制的高度，从上往下数

        rectangle(hist_img, Point(i * scale, hist_height/* - 1*/),
                  Point((i + 1) * scale - 1, hist_height - intensity),
                  CV_RGB(255, 255, 255));
    }
    imshow("Gray Histogram", hist_img);
    waitKey(0);
}
