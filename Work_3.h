//
// Created by Parti on 2020/11/17.
//

#ifndef CV_WORKS_WORK_3_H
#define CV_WORKS_WORK_3_H

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class Work_3 {
public:
    Work_3();

    void runExercise(unsigned short select);

private:
    Mat _defaultImage;

    static void exercise_1();

    void exercise_2();

    void exercise_3();
};


#endif //CV_WORKS_WORK_3_H
