//
// Created by Parti on 2021/1/18.
//

#include "Work_10.h"

Work_10::Work_10() {
    addExercise({[](const string &filePath) {
        struct Userdata {
            vector<Point> _mousePoints;
            Point _points;
            Mat _image;
        };
        vector<Point> mousePoints;
        Point points;

        auto onMouse = [](int EVENT, int x, int y, int flags, void *userdata) {
            Userdata tempUserdata = *reinterpret_cast<Userdata *>(userdata);
            Mat hh = tempUserdata._image;
            if (EVENT == EVENT_LBUTTONDOWN) {
                tempUserdata._points.x = x;
                tempUserdata._points.y = y;
                tempUserdata._mousePoints.push_back(tempUserdata._points);
                circle(hh, tempUserdata._points, 4, Scalar(255, 255, 255), -1);
                imshow("mouseCallback", hh);
            }
        };

        auto selectPolygon = [&mousePoints, &points, onMouse](const Mat &srcMat, Mat &dstMat) {
            vector<vector<Point>> contours;
            Mat selectMat, m = Mat::zeros(srcMat.size(), CV_32F);
            m = 1;
            if (!srcMat.empty()) {
                srcMat.copyTo(selectMat);
                srcMat.copyTo(dstMat);
            } else {
                std::cout << "failed to read image!:" << std::endl;
                return -1;
            }
            namedWindow("mouseCallback");
            imshow("mouseCallback", selectMat);
            Userdata tempUserdata = {mousePoints, points, selectMat};
            setMouseCallback("mouseCallback", static_cast<MouseCallback>(onMouse), &tempUserdata);
            waitKey(0);
            destroyAllWindows();
            contours.push_back(mousePoints);
            if (contours[0].size() < 3) {
                std::cout << "failed to read image!:" << std::endl;
                return -1;
            }
            drawContours(m, contours, 0, Scalar(0), -1);
            m.copyTo(dstMat);
            return 0;
        };

        auto mouseROI = [filePath, selectPolygon]() {
            Mat srcMat = imread(filePath), dstMat;
            selectPolygon(srcMat, dstMat);
            imshow("srcMat", srcMat);
            imshow("select Area", dstMat);
            waitKey(0);
            return 0;
        };

        auto DFTDemo = [filePath]() {
            cv::Mat srcMat = imread(filePath, 0);

            if (srcMat.empty()) {
                std::cout << "failed to read image!:" << std::endl;
                return -1;
            }

            Mat padMat;
            int m = getOptimalDFTSize(srcMat.rows);
            int n = getOptimalDFTSize(srcMat.cols);
            copyMakeBorder(srcMat, padMat, 0, m - srcMat.rows, 0, n - srcMat.cols, BORDER_CONSTANT, Scalar::all(0));

            Mat planes[] = {Mat_<float>(padMat), Mat::zeros(padMat.size(), CV_32F)};
            Mat complexMat;

            merge(planes, 2, complexMat);
            dft(complexMat, complexMat);
            split(complexMat, planes);
            magnitude(planes[0], planes[1], planes[0]);

            Mat magMat = planes[0];
            magMat += Scalar::all(1);
            log(magMat, magMat);

            magMat = magMat(Rect(0, 0, magMat.cols & -2, magMat.rows & -2));
            int cx = magMat.cols / 2, cy = magMat.rows / 2;

            Mat q0(magMat, Rect(0, 0, cx, cy)),
                    q1(magMat, Rect(cx, 0, cx, cy)),
                    q2(magMat, Rect(0, cy, cx, cy)),
                    q3(magMat, Rect(cx, cy, cx, cy)),
                    tmp;

            q0.copyTo(tmp);
            q3.copyTo(q0);
            tmp.copyTo(q3);
            q1.copyTo(tmp);
            q2.copyTo(q1);
            tmp.copyTo(q2);

            normalize(magMat, magMat, 0, 1, NORM_MINMAX);

            imshow("Input Image", srcMat);    // Show the result
            imshow("spectrum magnitude", magMat);
            waitKey(0);

            return 0;
        };

        auto invertedFFTDemo = [filePath, selectPolygon]() {
            cv::Mat dst;
            cv::Mat src = imread(filePath, 0);

            int m = getOptimalDFTSize(src.rows);
            int n = getOptimalDFTSize(src.cols);
            Mat padded;
            copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));
            Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
            Mat planes_true = Mat_<float>(padded);
            Mat ph = Mat_<float>(padded);
            Mat complexImg;
            merge(planes, 2, complexImg);
            dft(complexImg, complexImg);
            split(complexImg, planes);

            magnitude(planes[0], planes[1], planes_true);//幅度谱mag
            phase(planes[0], planes[1], ph);//相位谱ph
            Mat A = planes[0];
            Mat B = planes[1];
            Mat mag = planes_true;

            mag += Scalar::all(1);
            log(mag, mag);

            double maxVal;
            minMaxLoc(mag, nullptr, &maxVal, nullptr, nullptr);

            mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
            ph = ph(Rect(0, 0, mag.cols & -2, mag.rows & -2));
            Mat _magI = mag.clone();
            normalize(_magI, _magI, 0, 1);

            int cx = mag.cols / 2;
            int cy = mag.rows / 2;

            Mat tmp;
            Mat q0(mag, Rect(0, 0, cx, cy));
            Mat q1(mag, Rect(cx, 0, cx, cy));
            Mat q2(mag, Rect(0, cy, cx, cy));
            Mat q3(mag, Rect(cx, cy, cx, cy));
            q0.copyTo(tmp);
            q3.copyTo(q0);
            tmp.copyTo(q3);
            q1.copyTo(tmp);
            q2.copyTo(q1);
            tmp.copyTo(q2);

            normalize(mag, mag, 0, 1);
            mag = mag * 255;
            imwrite("mag", mag);

            mag = mag / 255;
            Mat mask, processedMag;

            selectPolygon(mag, mask);

            mag = mag.mul(mask);

            processedMag = mag * 255;
            imwrite("processedMag", processedMag);

            Mat q00(mag, Rect(0, 0, cx, cy));
            Mat q10(mag, Rect(cx, 0, cx, cy));
            Mat q20(mag, Rect(0, cy, cx, cy));
            Mat q30(mag, Rect(cx, cy, cx, cy));

            q00.copyTo(tmp);
            q30.copyTo(q00);
            tmp.copyTo(q30);
            q10.copyTo(tmp);
            q20.copyTo(q10);
            tmp.copyTo(q20);

            mag = mag * maxVal;
            exp(mag, mag);
            mag = mag - Scalar::all(1);
            polarToCart(mag, ph, planes[0], planes[1]);
            merge(planes, 2, complexImg);


            Mat invertedFFT(Size(src.cols, src.rows), CV_8UC1);
            idft(complexImg, invertedFFT, DFT_REAL_OUTPUT);
            normalize(invertedFFT, invertedFFT, 0, 1);

            Rect rect(0, 0, src.cols, src.rows);
            dst = invertedFFT(rect);
            dst = dst * 255;

            cv::Mat dspMat;
            dst.convertTo(dspMat, CV_8UC1);
            imshow("dst", dspMat);
            imshow("src", src);
            waitKey(0);

            return 0;
        };
        mouseROI();
        DFTDemo();
        invertedFFTDemo();
    }, _defaultImageUrl});
}
