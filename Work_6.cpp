//
// Created by Parti on 2020/11/17.
//

#include "Work_6.h"
Work_6::Work_6() {
    _defaultImage = imread("C:/Users/Particle_G/Pictures/avatar.jpg");
}

void Work_6::runExercise(unsigned short select) {
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

void Work_6::exercise_1() {
}

void Work_6::exercise_2() {
}

void Work_6::exercise_3() {
}