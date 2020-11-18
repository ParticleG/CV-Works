//
// Created by Parti on 2021/1/6.
//

#ifndef CV_WORKS_WORK_15_H
#define CV_WORKS_WORK_15_H

#define YOLOV3_VIDEO        "./vtest.avi"
#define OPENPOSE_VIDEO        "./default.mp4"

//#define INPUT_METHOD
// 0: image 1:video 2:camera

#include <opencv2/dnn.hpp>
#include <fstream>

#include "Work_baseClass.h"

class Work_15 : public Work_baseClass {
public:
    void runExercise(unsigned short select) override;

private:
    void exercise_1(bool isOpenPose);

    void postprocess(cv::Mat &frame, std::vector<cv::Mat> &outs);

    static std::vector<cv::String> getOutputsNames(const cv::dnn::Net &net);

    void drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat &frame);

    int yoloV3();

    int openpose();

    std::vector<std::string> classes;
    float confThreshold = 0.5; // Confidence threshold
    float nmsThreshold = 0.4;  // Non-maximum suppression threshold
    int inpWidth = 416;        // Width of network's input image
    int inpHeight = 416;       // Height of network's input image

    // https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md

    int POSE_PAIRS[3][20][2] = {
            {   // COCO body
                    {1, 2}, {1, 5}, {2, 3},
                                            {3, 4}, {5, 6}, {6, 7},
                                                                    {1, 8}, {8, 9},  {9,  10},
                                                                                              {1, 11}, {11, 12}, {12, 13},
                                                                                                                           {1,  0},  {0,  14},
                                                                                                                                               {14, 16}, {0,  15}, {15, 17}
            },
            {   // MPI body
                    {0, 1}, {1, 2}, {2, 3},
                                            {3, 4}, {1, 5}, {5, 6},
                                                                    {6, 7}, {1, 14}, {14, 8}, {8, 9},
                                                                                                       {9,  10}, {14, 11}, {11, 12}, {12, 13}
            },
            {   // hand
                    {0, 1}, {1, 2}, {2, 3}, {3, 4},         // thumb
                                                    {0, 5}, {5, 6}, {6, 7}, {7, 8},         // pinkie
                                                                                     {0,  9}, {9, 10}, {10, 11}, {11, 12},    // middle
                                                                                                                           {0,  13}, {13, 14}, {14, 15}, {15, 16},  // ring
                                                                                                                                                                   {0,  17}, {17, 18}, {18, 19}, {19, 20}   // small
            }
    };
};


#endif //CV_WORKS_WORK_15_H
