//
// Created by Parti on 2021/1/18.
//

#include "Work_9.h"

Work_9::Work_9() {
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
