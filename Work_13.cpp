//
// Created by Parti on 2021/1/18.
//

#include "Work_13.h"

Work_13::Work_13() {
    addExercise({[](const string &filePath) {
        system("color 02");
        VideoCapture capture(filePath);
        int cnt = 0, keyReturn;
        Mat frame, tempMat, refMat, resultMat, displayMat;
        do {
            capture >> frame;
            if (cnt == 0) {
                Rect2d r;
                r = selectROI(frame, true);
                tempMat = frame(r);
                tempMat.copyTo(refMat);
                destroyAllWindows();
            }
            int match_method = 0;
            matchTemplate(frame, refMat, resultMat, match_method);
            normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());
            double minVal, maxVal;
            Point minLoc, maxLoc, matchLoc;
            minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
            matchLoc = minLoc;
            frame.copyTo(displayMat);
            rectangle(displayMat,
                      matchLoc,
                      Point(matchLoc.x + refMat.cols, matchLoc.y + refMat.rows),
                      Scalar::all(0),
                      2,
                      8,
                      0);
            cnt++;
            imshow("template", refMat);
            imshow("displayMat", displayMat);
            keyReturn = waitKey(30);
        } while (keyReturn == -1);
    }, _defaultVideoUrl});

    addExercise({[](const string &filePath) {
        auto calCellHist = [](const Mat &src) {
            Mat gx, gy, mag, angle;
            Sobel(src, gx, CV_32F, 1, 0, 1);
            Sobel(src, gy, CV_32F, 0, 1, 1);
            cartToPolar(gx, gy, mag, angle, true);

            auto *hist = (float *) malloc(sizeof(float) * 8);
            for (int j = 0; j < 16; j++) {
                for (int i = 0; i < 16; i++) {
                    int angle_average = angle.at<float>(j, i);
                    hist[angle_average / 45] += mag.at<float>(j, i);
                }
            }
            return hist;
        };

        Mat sourceImage = imread(filePath),
                alterAImage = imread(filePath.substr(0, filePath.size() - 4) + "_a.png");

        int cellSize = 16;
        int nX = sourceImage.cols / cellSize;
        int nY = sourceImage.rows / cellSize;
        Mat img2 = Mat::zeros(sourceImage.rows, sourceImage.cols, CV_8UC1);
        int num = nX * nY * 8;

        auto *srcHist = new float[num];
        memset(srcHist, 0, sizeof(float) * num);

        auto *img1Hist = new float[num];
        memset(img1Hist, 0, sizeof(float) * num);

        auto *img2Hist = new float[num];
        memset(img2Hist, 0, sizeof(float) * num);

        int cnt1, cnt2;
        float distance;
        double distance_min = 10e100;
        int x = 0;
        int y = 0;
        for (int q = 85; q < 105; q++) {
            for (int p = 85; p < 105; p++) {
                for (int m = 0; m < sourceImage.rows; m++) {
                    for (int n = 0; n < sourceImage.cols; n++) {
                        img2.at<uchar>(m, n) = alterAImage.at<uchar>(q + m, p + n);
                    }
                }
                cnt1 = 0;
                for (int j = 0; j < nY; j++) {
                    for (int i = 0; i < nX; i++) {
                        Rect rectL(i * cellSize, j * cellSize, cellSize, cellSize);
                        Mat nowMat = sourceImage(rectL);
                        for (int k = 0; k < 8; k++) {
                            img1Hist[k + cnt1 * 8] = calCellHist(nowMat)[k];
                        }
                        cnt1++;
                    }
                }
                cnt2 = 0;
                for (int j = 0; j < nY; j++) {
                    for (int i = 0; i < nX; i++) {
                        Rect rectL(i * cellSize, j * cellSize, cellSize, cellSize);
                        Mat nowMat = img2(rectL);
                        for (int k = 0; k < 8; k++) {
                            img2Hist[k + cnt2 * 8] = calCellHist(nowMat)[k];
                        }
                        cnt2++;
                    }
                }
                distance = 0;
                for (int i = 0; i < num; i++) {
                    distance += (img1Hist[i] - img2Hist[i]) * (img1Hist[i] - img2Hist[i]);
                    if (distance < distance_min) {
                        distance_min = distance;
                        x = q;
                        y = p;
                    }
                }
            }
        }
        cout << "Min " << distance_min << endl;
        cout << "x " << x << endl;
        cout << "y " << y << endl;
        Rect rect(y, x, sourceImage.cols, sourceImage.rows);
        cv::rectangle(alterAImage, rect, Scalar(255, 0, 0), 1, LINE_8, 0);
        imshow("dstMat", alterAImage);
        waitKey(0);
        delete[] img1Hist;
        delete[] img2Hist;
        return 0;
    }, _defaultImageUrl});
}
