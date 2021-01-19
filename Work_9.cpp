//
// Created by Parti on 2021/1/18.
//

#include "Work_9.h"

Work_9::Work_9() {
    addExercise({[](const string &filePath) {
        auto histogramFunction = [](const Mat &src, float *hist) {
            int cellSize = 16, nX = src.cols / cellSize, nY = src.rows / cellSize;
            Mat gx, gy, mag, angle;
            Sobel(src, gx, CV_32F, 1, 0, 1);
            Sobel(src, gy, CV_32F, 0, 1, 1);
            cartToPolar(gx, gy, mag, angle, true);
            for (int cellX = 0; cellX < nX; cellX++) {
                for (int cellY = 0; cellY < nY; cellY++) {
                    int pixelStartX = 16 * cellX,
                            pixelEndX = pixelStartX + 16,
                            pixelStartY = 16 * cellY,
                            pixelEndY = pixelStartY + 16,
                            cellN = cellX * nX + cellY;
                    for (int i = pixelStartX; i < pixelEndX; i++) {
                        for (int j = pixelStartY; j < pixelEndY; j++) {
                            int angle_average = angle.at<float>(j, i);
                            hist[(angle_average / 45 + cellN * 8)] += mag.at<float>(j, i);
                        }
                    }
                }
            }
        };

        auto distanceCalculateFunction = [](const float *src_hist, const float *dst_hist, int bin) {
            float sum = 0;
            for (int i = 0; i < bin; i++) {
                sum += (src_hist[i] - dst_hist[i]) * (src_hist[i] - dst_hist[i]);
            }
            sum = sqrt(sum);
            return sum;
        };

        Mat sourceImage = imread(filePath),
                alterAImage = imread(filePath.substr(0, filePath.size() - 4) + "_a.png"),
                alterBImage = imread(filePath.substr(0, filePath.size() - 4) + "_b.png");
        int cellSize = 16, nX = sourceImage.cols / cellSize, nY = sourceImage.rows / cellSize, bin = nX * nY * 8;
        auto *src_hist = new float[bin], *img1_hist = new float[bin], *img2_hist = new float[bin];
        memset(src_hist, 0, sizeof(float) * bin);
        memset(img1_hist, 0, sizeof(float) * bin);
        memset(img2_hist, 0, sizeof(float) * bin);


        histogramFunction(sourceImage, src_hist);
        histogramFunction(alterAImage, img1_hist);
        histogramFunction(alterBImage, img2_hist);

        float img1dist = distanceCalculateFunction(src_hist, img1_hist, bin);
        float img2dist = distanceCalculateFunction(src_hist, img2_hist, bin);


        cout << img1dist << endl;
        std::cout << img2dist << endl;

        if (img1dist > img2dist) {
            cout << "The second one is more likes the default one." << endl;
        } else {
            cout << "The first one is more likes the default one." << endl;
        }
        delete[] src_hist;
        delete[] img1_hist;
        delete[] img2_hist;

    }, _defaultImageUrl});
}
