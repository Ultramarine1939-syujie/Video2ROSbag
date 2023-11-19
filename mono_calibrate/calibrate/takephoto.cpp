#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <stdio.h>

using namespace std;
using namespace cv;


int main() {
    VideoCapture capture(4);
    capture.set(CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CAP_PROP_FRAME_HEIGHT, 480);
    

    Mat img;
    char filename[200];

    int i =0;

    while (capture.isOpened()) {
        
        capture >> img;

        
        imshow("test",img);

        waitKey(1500);

        sprintf(filename, "%s%d%s", "../pic/", i++, ".jpg");
        cout << filename << endl;

        imwrite(filename, img);
    }
    return 0;
}
