//
// Created by Parti on 2021/1/6.
//

#include "Work_15.h"

Work_15::Work_15() {
    using namespace dnn;
    addExercise({[](const string &filePath) {
        std::vector<std::string> classes;

        int POSE_PAIRS[3][20][2] = {
                {
                        {1, 2}, {1, 5}, {2, 3},
                                                {3, 4}, {5, 6}, {6, 7},
                                                                        {1, 8}, {8, 9},  {9,  10},
                                                                                                  {1, 11}, {11, 12}, {12, 13},
                                                                                                                               {1,  0},  {0,  14},
                                                                                                                                                   {14, 16}, {0,  15}, {15, 17}
                },
                {
                        {0, 1}, {1, 2}, {2, 3},
                                                {3, 4}, {1, 5}, {5, 6},
                                                                        {6, 7}, {1, 14}, {14, 8}, {8, 9},
                                                                                                           {9,  10}, {14, 11}, {11, 12}, {12, 13}
                },
                {
                        {0, 1}, {1, 2}, {2, 3}, {3, 4},
                                                        {0, 5}, {5, 6}, {6, 7}, {7, 8},
                                                                                         {0,  9}, {9, 10}, {10, 11}, {11, 12},
                                                                                                                               {0,  13}, {13, 14}, {14, 15}, {15, 16},
                                                                                                                                                                       {0,  17}, {17, 18}, {18, 19}, {19, 20}
                }
        };

        auto openpose = [filePath, POSE_PAIRS]() {
            String modelTxt = filePath.substr(0, filePath.size() - 11) + "openpose_pose_coco.prototxt";
            String modelBin = filePath.substr(0, filePath.size() - 11) + "pose_iter_440000.caffemodel";

            Net net = readNetFromCaffe(modelTxt, modelBin);

            int W_in = 368;
            int H_in = 368;
            float thresh = 0.1;

            VideoCapture cap;
            cap.open(filePath);

            if (!cap.isOpened())return -1;

            while (true) {
                cv::Mat frame;
                cap >> frame;
                if (frame.empty()) {
                    std::cout << "frame is empty!!!" << std::endl;
                    return -1;
                }
                Mat inputBlob = blobFromImage(frame, 1.0 / 255, Size(W_in, H_in), Scalar(0, 0, 0), false, false);
                net.setInput(inputBlob);
                Mat result = net.forward();

                int midX, nPairs;
                int H = result.size[2];
                int W = result.size[3];

                int nParts = result.size[1];

                // find out, which model we have
                if (nParts == 19) {   // COCO body
                    midX = 0;
                    nPairs = 17;
                    nParts = 18; // skip background
                } else if (nParts == 16) {   // MPI body
                    midX = 1;
                    nPairs = 14;
                } else if (nParts == 22) {   // hand
                    midX = 2;
                    nPairs = 20;
                } else {
                    cerr
                            << "there should be 19 parts for the COCO model, 16 for MPI, or 22 for the hand one, but this model has "
                            << nParts << " parts." << endl;
                    return (0);
                }

                vector<Point> points(22);
                for (int n = 0; n < nParts; n++) {
                    // Slice heatmap of corresponding body's part.
                    Mat heatMap(H, W, CV_32F, result.ptr(0, n));
                    Point p(-1, -1), pm;
                    double conf;
                    minMaxLoc(heatMap, nullptr, &conf, nullptr, &pm);
                    if (conf > thresh) {
                        p = pm;
                    }
                    points[n] = p;
                }

                float SX = float(frame.cols) / static_cast<float>(W);
                float SY = float(frame.rows) / static_cast<float>(H);
                for (int n = 0; n < nPairs; n++) {
                    Point2f a = points[POSE_PAIRS[midX][n][0]];
                    Point2f b = points[POSE_PAIRS[midX][n][1]];

                    if (a.x <= 0 || a.y <= 0 || b.x <= 0 || b.y <= 0)
                        continue;
                    a.x *= SX;
                    a.y *= SY;
                    b.x *= SX;
                    b.y *= SY;
                    line(frame, a, b, Scalar(0, 200, 0), 2);
                    circle(frame, a, 3, Scalar(0, 0, 200), -1);
                    circle(frame, b, 3, Scalar(0, 0, 200), -1);
                }
                imshow("frame", frame);
                waitKey(30);
            }
        };

        auto start = static_cast<double>(getTickCount());
        openpose();

        double time = ((double) getTickCount() - start) / getTickFrequency();
        cout << "processing time:" << time / 1000 << "ms" << endl;

    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);

    }, _defaultImageUrl});

    addExercise({[](const string &filePath) {
        Mat sourceImage = imread(filePath);

    }, _defaultImageUrl});
}
