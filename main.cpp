#include "Work_1.h"
#include "Work_2.h"
#include "Work_3.h"
#include "Work_4.h"
#include "Work_5.h"
#include "Work_6.h"
#include "Work_7.h"

template<typename Work>
void executor(Work &temp, unsigned int exerciseNumber) {
    temp.runExercise(exerciseNumber);
}

int main() {
    Work_1 work_1;
    Work_2 work_2;
    Work_3 work_3;
    Work_4 work_4;
    Work_5 work_5;
    Work_6 work_6;
    Work_7 work_7;
    unsigned int workNumber, exerciseNumber;
    cout << "Choose an work number, could be 1 to 7." << endl;
    cin >> workNumber;
    cout << "Choose an exercise number." << endl;
    cin >> exerciseNumber;
    switch (workNumber) {
        case 1:
            executor(work_1, exerciseNumber);
            break;
        case 2:
            executor(work_2, exerciseNumber);
            break;
        case 3:
            executor(work_3, exerciseNumber);
            break;
        case 4:
            executor(work_4, exerciseNumber);
            break;
        case 5:
            executor(work_5, exerciseNumber);
            break;
        case 6:
            executor(work_6, exerciseNumber);
            break;
        case 7:
            executor(work_7, exerciseNumber);
            break;
        default:
            cout << "Work not found." << endl;
            break;
    }
    return 0;
}