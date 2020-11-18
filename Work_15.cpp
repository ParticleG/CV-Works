//
// Created by Parti on 2021/1/6.
//

#include "Work_15.h"

using namespace dnn;

void Work_15::runExercise(unsigned short select) {
    if (select == 1) {
        exercise_1(true);
    } else {
        cout << "Unknown exercise number, could be 1" << endl;
    }
}

void Work_15::exercise_1(bool isOpenPose = true) {
    auto start = static_cast<double>(getTickCount());

    if (isOpenPose) {
        openpose();
    } else {
        yoloV3();
    }

    double time = ((double) getTickCount() - start) / getTickFrequency();
    cout << "processing time:" << time / 1000 << "ms" << endl;
}

void Work_15::postprocess(Mat &frame, vector<cv::Mat> &outs) {
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    for (auto &out : outs) {
        // Scan through all the bounding boxes output from the network and keep only the
        // ones with high confidence scores. Assign the box's class label as the class
        // with the highest score for the box.
        //
        auto *data = (float *) out.data;
        for (int j = 0; j < out.rows; ++j, data += out.cols) {
            cv::Mat scores = out.row(j).colRange(5, out.cols);
            cv::Point classIdPoint;
            double confidence;

            cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);

            if (confidence > confThreshold) {
                int centerX = (int) (data[0] * static_cast<float>(frame.cols));
                int centerY = (int) (data[1] * static_cast<float>(frame.rows));
                int width = (int) (data[2] * static_cast<float>(frame.cols));
                int height = (int) (data[3] * static_cast<float>(frame.rows));
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float) confidence);
                boxes.emplace_back(left, top, width, height);
            }
        }
    }

    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
    for (int idx : indices) {
        cv::Rect box = boxes[idx];
        drawPred(classIds[idx], confidences[idx], box.x, box.y,
                 box.x + box.width, box.y + box.height, frame);
    }
}

std::vector<cv::String> Work_15::getOutputsNames(const dnn::Net &net) {
    static std::vector<cv::String> names;
    if (names.empty()) {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        std::vector<int> outLayers = net.getUnconnectedOutLayers();

        //get the names of all the layers in the network
        std::vector<cv::String> layersNames = net.getLayerNames();

        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
            names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}

void Work_15::drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat &frame) {
    cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(0, 0, 255));

    std::string label = cv::format("%.2f", conf);
    if (!classes.empty()) {
        CV_Assert(classId < (int) classes.size());
        label = classes[classId] + ":" + label;
    } else {
        std::cout << "classes is empty..." << std::endl;
    }

    int baseLine;
    cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 2, &baseLine);
    top = std::max(top, labelSize.height);
    cv::putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
}

int Work_15::yoloV3() {
    VideoCapture cap(YOLOV3_VIDEO);

    if (!cap.isOpened())return -1;

    string classesFile = "./coco.names";
    String yolov3_model = "./yolov3.cfg";
    String weights = "./yolov3.weights";

    std::ifstream classNamesFile(classesFile.c_str());
    if (classNamesFile.is_open()) {
        std::string className;
        while (std::getline(classNamesFile, className)) {
            classes.push_back(className);
        }
    } else {
        std::cout << "can not open classNamesFile" << std::endl;
    }

    cv::dnn::Net net = cv::dnn::readNetFromDarknet(yolov3_model, weights);

    net.setPreferableBackend(DNN_BACKEND_DEFAULT);
    net.setPreferableTarget(DNN_TARGET_CPU);

    cv::Mat frame;

    while (true) {
        cap >> frame;

        if (frame.empty()) {
            std::cout << "frame is empty!!!" << std::endl;
            return -1;
        }

        cv::Mat blob;
        cv::dnn::blobFromImage(frame, blob, 1 / 255.0, cv::Size(inpWidth, inpHeight), cv::Scalar(0, 0, 0), true, false);

        net.setInput(blob);

        std::vector<cv::Mat> outs;
        net.forward(outs, getOutputsNames(net));

        postprocess(frame, outs);

        cv::imshow("frame", frame);

        if (cv::waitKey(10) == 27) {
            break;
        }
    }

    return 0;
}

int Work_15::openpose() {
    String modelTxt = "./openpose_pose_coco.prototxt";
    String modelBin = "./pose_iter_440000.caffemodel";

    cv::dnn::Net net = cv::dnn::readNetFromCaffe(modelTxt, modelBin);

    int W_in = 368;
    int H_in = 368;
    float thresh = 0.1;

    VideoCapture cap;
    cap.open(OPENPOSE_VIDEO);

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

        int midx, npairs;
        int H = result.size[2];
        int W = result.size[3];

        int nparts = result.size[1];


        // find out, which model we have
        if (nparts == 19) {   // COCO body
            midx = 0;
            npairs = 17;
            nparts = 18; // skip background
        } else if (nparts == 16) {   // MPI body
            midx = 1;
            npairs = 14;
        } else if (nparts == 22) {   // hand
            midx = 2;
            npairs = 20;
        } else {
            cerr
                    << "there should be 19 parts for the COCO model, 16 for MPI, or 22 for the hand one, but this model has "
                    << nparts << " parts." << endl;
            return (0);
        }

        vector<Point> points(22);
        for (int n = 0; n < nparts; n++) {
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
        for (int n = 0; n < npairs; n++) {
            Point2f a = points[POSE_PAIRS[midx][n][0]];
            Point2f b = points[POSE_PAIRS[midx][n][1]];

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
}
