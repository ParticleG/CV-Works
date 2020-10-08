//
// Created by Particle_G on 2020/10/8.
//

#ifndef CV_WORKS_WORK_2_H
#define CV_WORKS_WORK_2_H

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class Work_2 {
public:
    Work_2();

    void runExercise(unsigned short select);

private:
    Mat _defaultImage;

    void exercise_1();

    void exercise_2();

    void exercise_3();

    void exercise_4();

    void exercise_5();
};


#endif //CV_WORKS_WORK_2_H
