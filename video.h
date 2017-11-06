#ifndef VIDEO_H
#define VIDEO_H

#include <QImage>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <stdio.h>
#include <QDateTime>
#include "gestionvideo.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "algosubstraction.h"
#include "algocolors.h"

using namespace cv ;

class Video : public QThread{
    Q_OBJECT
    private:
        QMutex mutex ;
        QWaitCondition condition ;
        bool stopBool, boolFirstFrame, trajectoryChecked, visualize, treatment, keepRunning ;
        Mat frame, firstFrame,RGBframe ;
        double framerate ;
        std::string fullpath;
        VideoCapture videoCapture ;

        int nbFrames, nbCurrentFrame ;

        Mat imageTmp, imageOriginal, choosenObject ;
        Point previousPoint, currentPoint ;

        int shiftMax ;

        QImage mat2QImage(const Mat& src) ;

        QImage qImageHistRed ;
        QImage qImageHistGreen ;
        QImage qImageHistBlue ;

        int redMin, redMax ;
        int greenMin, greenMax ;
        int blueMin, blueMax ;

        AlgoSubstraction* algoSoustraction ;
        AlgoColors* algoColors ;

        Mat HSV ;
        Mat threshold;
        std::stringstream info ;
        QDateTime qDateTime ;
        int x,y ;

        int algoIDtoRun ;

        int minHue, minSaturation, minValue ;
        int maxHue, maxSaturation, maxValue ;

        int frameStartExtraction ;
        int frameEndExtraction ;

    protected :
        void run() ;
    public:
        Video(QObject *parent = 0);
        ~Video() ;
        void play() ;
        void stop() ;
        bool isStopped() ;
        bool loadVideo(std::string filename) ;

        double getSecFromNbFrame(double nbFrames) ;
        void setCurrentFrame(int frameNumber) ;

        double getFramerate() ;
        int getCurrentFrameID() ;
        int getNumberOfFrames() ;

        void setTrajectoryChecked(bool checked) ;
        void setVisualize(bool visualize) ;
        void setTreatment(bool treatment) ;
        void isFirstFrame(bool boolFirstFrame) ;
        void toKeepRunning(bool keepRunning) ;

        void setShiftMax(int shiftMax) ;

        QImage getFirstFrame() ;
        QImage getPreviousFrame() ;
        QImage getPreviousFrameExtended(int extension) ;
        QImage getNextFrame() ;
        QImage getNextFrameExtended(int extension) ;
        QImage getLastFrame() ;

        QImage getImageMousePressed(int x, int y, int qVideoLabelHeight, int qVideoLabelWidth) ;
        QImage getImageMousePressedAndMoving(int x, int y, int qVideoLabelHeight, int qVideoLabelWidth) ;
        QImage getImageMouseReleased(int x, int y, int qVideoLabelHeight, int qVideoLabelWidth) ;

        void computeHistogramChosenObject() ;
        int getRedMin() ;
        int getRedMax() ;
        int getGreenMin() ;
        int getGreenMax() ;
        int getBlueMin() ;
        int getBlueMax() ;
        QImage getHistRed() ;
        QImage getHistGreen() ;
        QImage getHistBlue() ;

        void drawObject(int x, int y, cv::Mat &frame) ;
        void setAlgoIDtoRun(int ID) ;

        void setMinHue(int minHue) ;
        void setMinSaturation(int minSaturation) ;
        void setMinValue(int minValue) ;

        void setMaxHue(int maxHue) ;
        void setMaxSaturation(int maxSaturation) ;
        void setMaxValue(int maxValue) ;

        void setFrameStartExtraction(int start) ;
        void setFrameEndExtraction(int end) ;

        void extractVideo(QString filename) ;
        int timeVideo();

    signals:
        void processedImage(const QImage& image, int nbFrame, QString info) ;
        void processedThresholdImage(const QImage& image) ;
};

#endif // VIDEO_H
