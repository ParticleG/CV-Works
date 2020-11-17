//
// Created by Parti on 2020/11/17.
//

#include "Work_5.h"
Work_5::Work_5() {
    _defaultImage = imread("C:/Users/Parti/Pictures/avatar.jpg");
}

void Work_5::runExercise(unsigned short select) {
    switch (select) {
        case 1:
            exercise_1();
            break;
        case 2:
            exercise_2();
            break;
        case 3:
            exercise_3();
            break;
        default:
            cout << "Unknown exercise number, could be 1 to 3" << endl;
            break;
    }
}

void Work_5::exercise_1() {
}

void Work_5::exercise_2() {
}

void Work_5::exercise_3() {
}