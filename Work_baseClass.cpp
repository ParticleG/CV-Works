//
// Created by Parti on 2020/12/30.
//

#include "Work_baseClass.h"

Work_baseClass::Work_baseClass(const string &workingDirectory) {
    _defaultImageUrl = workingDirectory + "default.png";
    _defaultVideoUrl = workingDirectory + "default.mp4";
}

void Work_baseClass::addExercise(const Exercise &exercise) {
    _exercises.push_back(exercise);
}

void Work_baseClass::runExercise() {
    unsigned short selection;
    cout << "Choose an exercise number out of total " << _exercises.size() << " exercises:";
    cin >> selection;
    try {
        _exercises.at(selection)._function(_exercises.at(selection).filePath);
    } catch (out_of_range &e) {
        cout << "Invalid input: Out of range." << endl;
    }
}
