//
// Created by Parti on 2020/11/17.
//

#ifndef CV_WORKS_WORK_5_H
#define CV_WORKS_WORK_5_H

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class Work_5 {
public:
    Work_5();

    void runExercise(unsigned short select);

private:
    Mat _defaultImage;

    void exercise_1();

    void exercise_2();

    void exercise_3();

    void exercise_4();

    void exercise_5();
};


#endif //CV_WORKS_WORK_5_H
