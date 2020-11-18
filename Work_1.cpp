//
// Created by Particle_G on 2020/9/23.
//

#include "Work_1.h"

Work_1::Work_1() {
    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
        imshow("Before", sourceImage);
        for (auto matIterator = sourceImage.begin<Vec3b>();
             matIterator != sourceImage.end<Vec3b>(); matIterator++) {
            int averageRGB =
                    ((*matIterator).val[0] + (*matIterator).val[1] + (*matIterator).val[2]) / 3;
            (*matIterator).val[0] = averageRGB;    //B
            (*matIterator).val[1] = averageRGB;    //G
            (*matIterator).val[2] = averageRGB;    //R
        }
        imshow("After", sourceImage);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
        Mat grayedImage = imread(filePath);
        imshow("Default", sourceImage);
        imshow("Grayed", grayedImage);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
        const unsigned short threshold = 100;
        imshow("Before", sourceImage);
        for (auto matIterator = sourceImage.begin<Vec3b>();
             matIterator != sourceImage.end<Vec3b>(); matIterator++) {
            unsigned int averageRGB = ((*matIterator).val[0] + (*matIterator).val[1] + (*matIterator).val[2]) / 3;
            unsigned int binarizdPixel = averageRGB > threshold ? 255 : 0;
            (*matIterator).val[0] = binarizdPixel;    //B
            (*matIterator).val[1] = binarizdPixel;    //G
            (*matIterator).val[2] = binarizdPixel;    //R
        }
        imshow("After", sourceImage);
        waitKey(0);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath), deepMat = sourceImage.clone(), shallowMat = sourceImage;
        const unsigned short threshold = 100;
        for (auto matIterator = sourceImage.begin<Vec3b>();
             matIterator != sourceImage.end<Vec3b>(); matIterator++) {
            unsigned int averageRGB = ((*matIterator).val[0] + (*matIterator).val[1] + (*matIterator).val[2]) / 3;
            unsigned int binarizdPixel = averageRGB > threshold ? 255 : 0;
            (*matIterator).val[0] = binarizdPixel;    //B
            (*matIterator).val[1] = binarizdPixel;    //G
            (*matIterator).val[2] = binarizdPixel;    //R
        }
        imshow("Default", sourceImage);
        imshow("Shallow", shallowMat);
        imshow("Deep", deepMat);
        waitKey(0);
    }, _defaultImageUrl});
}