//
// Created by Parti on 2021/1/18.
//

#include "Work_12.h"

Work_12::Work_12() {
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
