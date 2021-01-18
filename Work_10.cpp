//
// Created by Parti on 2021/1/18.
//

#include "Work_10.h"

Work_10::Work_10() {
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
