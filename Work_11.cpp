//
// Created by Parti on 2021/1/18.
//

#include "Work_11.h"

Work_11::Work_11() {
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
