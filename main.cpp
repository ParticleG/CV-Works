#include "Work_1.h"
#include "Work_2.h"

template<typename Work>
void executor(Work &temp, unsigned int exerciseNumber) {
    temp.runExercise(exerciseNumber);
}

int main() {
    Work_1 work_1;
    Work_2 work_2;
    unsigned int workNumber, exerciseNumber;
    cout << "Choose an work number, could be 1 to 2" << endl;
    cin >> workNumber;
    cout << "Choose an exercise number, could be 1 to 4" << endl;
    cin >> exerciseNumber;
    switch (workNumber) {
        case 1:
            executor(work_1, exerciseNumber);
            break;
        case 2:
            executor(work_2, exerciseNumber);
            break;
        default:
            cout << "Work not found." << endl;
            break;
    }
    return 0;
}