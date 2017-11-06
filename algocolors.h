#ifndef ALGOCOLORS_H
#define ALGOCOLORS_H

#include <opencv\highgui.h>
#include <opencv\cv.h>

class AlgoColors{
    public:
        AlgoColors();
        void morphObs(cv::Mat &thresh);
        bool trackFilteredObject(int &x, int &y, cv::Mat threshold, cv::Mat &cameraFeed);
};

#endif // ALGOCOLORS_H
