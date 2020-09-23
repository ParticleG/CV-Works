#include "Work_1.h"

int main() {
    Work_1 work_1;
    int exerciseNumber;
    cout << "Choose an exercise number, could be 1 to 4" << endl;
    while (cin >> exerciseNumber) {
        work_1.runExercise(exerciseNumber);
    }
    return 0;
}