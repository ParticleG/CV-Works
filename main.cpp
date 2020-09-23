#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    Mat tempImage = imread("C:/Users/Particle_G/Pictures/avatar.jpg");
    imshow("Before",tempImage);
    for (auto matIterator = tempImage.begin<Vec3b>(); matIterator != tempImage.end<Vec3b>(); matIterator++) {
        int averageRGB = ((*matIterator).val[0] + (*matIterator).val[1] + (*matIterator).val[2]) / 3;
        (*matIterator).val[0] = averageRGB;    //B
        (*matIterator).val[1] = averageRGB;    //G
        (*matIterator).val[2] = averageRGB;    //R
    }
    imshow("Test",tempImage);
    waitKey(0);
    return 0;
}