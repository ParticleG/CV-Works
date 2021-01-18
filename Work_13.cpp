//
// Created by Parti on 2021/1/18.
//

#include "Work_13.h"

Work_13::Work_13() {
    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);
    }, _defaultImageUrl});
}
