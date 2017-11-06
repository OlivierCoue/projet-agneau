#ifndef ALGOSUBSTRACTION_H
#define ALGOSUBSTRACTION_H

#include "node.h"
#include "objectinformation.h"
#include "trajectory.h"

class AlgoSubstraction{
    public:
        AlgoSubstraction(int shiftMax, Mat& startFrame, Mat* choosenObject, int nbFrame);
        void run(Mat & currentFrame, int nbFrame, int&, int&);
        Mat generateBinaryImage(Mat &);
        void computeHistogram(Mat &);

        Trajectory getTrajectory() ;

    private:
        int shiftMax;     //Parameters of deplacementmax
        Mat startFrame;        //image of start frame
        Mat *choosenObject;        //object choose
        Mat binaryBackground;        //binary background image
        Mat element;
        Point2f centerBack;    //The last value of the array 'center'
        bool firstFrame;
        double biggestSurface; // the surface of the biggest contour
        int biggestSurfaceId;     // the number of the contour which has the biggest surface
        int count_refond;

        double thresholdRedMin;    //The lower limit of red channel
        double thresholdRedMax;    //The upper limit of red channel
        double thresholdGreenMin;  //The lower limit of green channel
        double thresholdGreenMax;  //The upper limit of green channel
        double thresholdBlueMin;   //The lower limit of blue channel
        double thresholdBlueMax;   //The upper limit of blue channel

        ObjectInformation myObject;
        Trajectory myTrajectoire;

};

#endif // ALGOSUBSTRACTION_H
