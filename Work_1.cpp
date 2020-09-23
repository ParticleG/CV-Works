//
// Created by Particle_G on 2020/9/23.
//

#include "Work_1.h"

Work_1::Work_1() {
    _defaultImage = imread("C:/Users/Particle_G/Pictures/avatar.jpg");
}

void Work_1::runExercise(unsigned short select) {
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
        default:
            cout << "Unknown exercise number, could be 1 to 4" << endl;
            break;
    }
}

void Work_1::exercise_1() {
    imshow("Before", _defaultImage);
    for (auto matIterator = _defaultImage.begin<Vec3b>(); matIterator != _defaultImage.end<Vec3b>(); matIterator++) {
        int averageRGB = ((*matIterator).val[0] + (*matIterator).val[1] + (*matIterator).val[2]) / 3;
        (*matIterator).val[0] = averageRGB;    //B
        (*matIterator).val[1] = averageRGB;    //G
        (*matIterator).val[2] = averageRGB;    //R
    }
    imshow("After", _defaultImage);
    waitKey(0);
}

void Work_1::exercise_2() {
    Mat grayedImage = imread("C:/Users/Particle_G/Pictures/avatar.jpg", 0);
    imshow("Default", _defaultImage);
    imshow("Grayed", grayedImage);
    waitKey(0);
}

void Work_1::exercise_3() {
    const unsigned short threshold = 100;
    imshow("Before", _defaultImage);
    for (auto matIterator = _defaultImage.begin<Vec3b>(); matIterator != _defaultImage.end<Vec3b>(); matIterator++) {
        unsigned int averageRGB = ((*matIterator).val[0] + (*matIterator).val[1] + (*matIterator).val[2]) / 3;
        unsigned int binarizdPixel = averageRGB > threshold ? 255 : 0;
        (*matIterator).val[0] = binarizdPixel;    //B
        (*matIterator).val[1] = binarizdPixel;    //G
        (*matIterator).val[2] = binarizdPixel;    //R
    }
    imshow("After", _defaultImage);
    waitKey(0);
}

void Work_1::exercise_4() {
    Mat deepMat = _defaultImage.clone(), shallowMat = _defaultImage;
    const unsigned short threshold = 100;
    for (auto matIterator = _defaultImage.begin<Vec3b>(); matIterator != _defaultImage.end<Vec3b>(); matIterator++) {
        unsigned int averageRGB = ((*matIterator).val[0] + (*matIterator).val[1] + (*matIterator).val[2]) / 3;
        unsigned int binarizdPixel = averageRGB > threshold ? 255 : 0;
        (*matIterator).val[0] = binarizdPixel;    //B
        (*matIterator).val[1] = binarizdPixel;    //G
        (*matIterator).val[2] = binarizdPixel;    //R
    }
    imshow("Default", _defaultImage);
    imshow("Shallow", shallowMat);
    imshow("Deep", deepMat);
    waitKey(0);
}