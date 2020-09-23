//
// Created by Particle_G on 2020/9/23.
//

#ifndef CVTEST_WORK_1_H
#define CVTEST_WORK_1_H

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class Work_1 {
public:
    Work_1();
    void runExercise(unsigned  short select);

private:
    Mat _defaultImage;
    void exercise_1();
    void exercise_2();
    void exercise_3();
    void exercise_4();
};


#endif //CVTEST_WORK_1_H
