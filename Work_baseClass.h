//
// Created by Parti on 2020/12/30.
//

#ifndef CV_WORKS_WORK_BASECLASS_H
#define CV_WORKS_WORK_BASECLASS_H

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

using ExerciseFunction = function<void(const string &filePath)>;

struct Exercise {
    ExerciseFunction _function;
    string filePath;
};

class Work_baseClass {
public:
    explicit Work_baseClass(const string &workingDirectory = "./");

    void addExercise(const Exercise &exercise);

    void runExercise();

    string _defaultImageUrl, _defaultVideoUrl;
private:
    vector<Exercise> _exercises;
};


#endif //CV_WORKS_WORK_BASECLASS_H
