#include <opencv2/core/utils/logger.hpp>
#include "Work_1.h"
#include "Work_2.h"
#include "Work_3.h"
#include "Work_4.h"
#include "Work_5.h"
#include "Work_6.h"
#include "Work_7.h"
#include "Work_8.h"
#include "Work_9.h"
#include "Work_10.h"
#include "Work_11.h"
#include "Work_12.h"
#include "Work_13.h"
#include "Work_14.h"
#include "Work_15.h"

int main() {
    Work_1 work_1;
    Work_2 work_2;
    Work_3 work_3;
    Work_4 work_4;
    Work_5 work_5;
    Work_6 work_6;
    Work_7 work_7;
    Work_8 work_8;
    Work_9 work_9;
    Work_10 work_10;
    Work_11 work_11;
    Work_12 work_12;
    Work_13 work_13;
    Work_14 work_14;
    Work_15 work_15;

    unsigned int workNumber;
    cout << "Choose an work number, could be 1 to 15: ";
    cin >> workNumber;
    switch (workNumber) {
        case 1:
            work_1.runExercise();
            break;
        case 2:
            work_2.runExercise();
            break;
        case 3:
            work_3.runExercise();
            break;
        case 4:
            work_4.runExercise();
            break;
        case 5:
            work_5.runExercise();
            break;
        case 6:
            work_6.runExercise();
            break;
        case 7:
            work_7.runExercise();
            break;
        case 8:
            work_8.runExercise();
            break;
        case 9:
            work_9.runExercise();
            break;
        case 10:
            work_10.runExercise();
            break;
        case 11:
            work_11.runExercise();
            break;
        case 12:
            work_12.runExercise();
            break;
        case 13:
            work_13.runExercise();
            break;
        case 14:
            work_14.runExercise();
            break;
        case 15:
            work_15.runExercise();
            break;
        default:
            cout << "Work not found." << endl;
            break;
    }
    return 0;
}