//
// Created by Parti on 2021/1/18.
//

#include "Work_12.h"

Work_12::Work_12() {
    addExercise({[](const string &filePath) {
        Mat bgMat;
        Mat subMat;
        Mat bny_subMat;
        int cnt = 0, keyReturn = -1;
        VideoCapture capVideo(filePath);
        do {
            Mat frame;
            Mat grayMat;
            capVideo >> frame;
            cvtColor(frame, frame, COLOR_BGR2GRAY);
            if (cnt == 0) {
                frame.copyTo(bgMat);
            } else {
                absdiff(frame, bgMat, subMat);

                threshold(subMat, bny_subMat, 50, 255, THRESH_BINARY);
                imshow("b_subMat", bny_subMat);
                imshow("subMat", subMat);
                keyReturn = waitKey(30);
            }
            cnt++;
        } while (keyReturn == -1);
    }, _defaultVideoUrl});

    addExercise({[](const string &filePath) {
        auto calcGaussianBackground = [](vector<Mat> srcMats, Mat &meanMat, Mat &varMat) {
            for (int h = 0; h < srcMats[0].rows; h++) {
                for (int w = 0; w < srcMats[0].cols; w++) {
                    int sum = 0;
                    float var = 0;
                    for (auto &srcMat : srcMats) {
                        sum += srcMat.at<uchar>(h, w);
                    }
                    meanMat.at<uchar>(h, w) = sum / srcMats.size();
                    for (auto &srcMat : srcMats) {
                        var += pow((srcMat.at<uchar>(h, w) - meanMat.at<uchar>(h, w)), 2);
                    }
                    varMat.at<float>(h, w) = var / srcMats.size();
                }
            }
            return 0;
        };

        auto gaussianThreshold = [](Mat srcMat, Mat meanMat, Mat varMat, float weight, Mat &dstMat) {
            int srcI, meanI;
            for (int h = 0; h < srcMat.rows; h++) {
                for (int w = 0; w < srcMat.cols; w++) {
                    srcI = srcMat.at<uchar>(h, w);
                    meanI = meanMat.at<uchar>(h, w);
                    int dif = abs(srcI - meanI), th = static_cast<int>(weight * varMat.at<float>(h, w));
                    if (dif > th) {
                        dstMat.at<uchar>(h, w) = 255;
                    } else {
                        dstMat.at<uchar>(h, w) = 0;
                    }
                }
            }
            return 0;
        };

        VideoCapture capVideo(filePath);
        vector<Mat> srcMats;
        int nBg = 200, cnt = 0, keyReturn = -1;
        float wVar = 1.2;
        Mat frame, meanMat, varMat, dstMat;
        do {
            capVideo >> frame;
            cvtColor(frame, frame, COLOR_BGR2GRAY);
            if (cnt < nBg) {
                srcMats.push_back(frame);
                if (cnt == 0) {
                    cout << "reading frame " << endl;
                }
            } else if (cnt == nBg) {
                meanMat.create(frame.size(), CV_8UC1);
                varMat.create(frame.size(), CV_32FC1);
                cout << "calculating background models" << endl;
                calcGaussianBackground(srcMats, meanMat, varMat);
            } else {
                dstMat.create(frame.size(), CV_8UC1);
                gaussianThreshold(frame, meanMat, varMat, wVar, dstMat);
                imshow("result", dstMat);
                imshow("frame", frame);
                keyReturn = waitKey(30);
            }
            cnt++;
        } while (keyReturn == -1);
    }, _defaultVideoUrl});
}
