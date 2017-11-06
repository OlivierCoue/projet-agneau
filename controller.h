#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QWidget>
#include "model.h"
#include "view.h"

#include <QDir>

class Controller : QObject{

    Q_OBJECT

    private:
        QWidget* qWidgetMainWindow ;
        QWidget* qWidgetObjectHistogramWindow ;
        QWidget* qWidgetShiftMaxWindow ;
        QWidget* qWidgetVideoThresholdWindow ;
        QWidget* qWidgetColorSelection ;
        QWidget* qWidgetExtractVideoWindow ;
        QWidget* qWidgetAudioAnalysisWindow ;

        Model* model ;
        View* view ;
        QString folderName ;
        QString filename ;
        QString currentPathVideos ;
        QString currentPath ;

        int positionSlide;

        bool isMousePressed ;
    public:
        Controller(Model* model, View* view);
        ~Controller() ;
    public slots:
        void updateVideo(QImage img, int currentFrame, QString info) ;
        void updateThresholdVideo(QImage img) ;

        void applyColor() ;

        void algorithmSubstractionChecked(bool toogled) ;
        void algorithmColorsChecked(bool toogled) ;

        void displayShiftMaxDialog() ;
        void displayObjectHistogram() ;
        void displayVideoThreshold() ;
        void displayColorSelection() ;
        void displayExtractVideo() ;
        void displayLaunchAudioAnalysis() ;
        void openVideoFile() ;


        void loadTrajectory() ;
        void saveTrajectory() ;
        void clearList() ;

        void sliderVideoMoved(int position) ;
        void sliderVideoPressed() ;
        void sliderVideoReleased();
        void playStopVideo() ;
        void beginningVideo() ;
        void backward() ;
        void fastBackward() ;
        void endVideo() ;
        void forward() ;
        void fastForward() ;

        void trajectoryChecked(int checked) ;
        void visualizeChecked() ;
        void treatmentChecked() ;

        void mousePressed(int x, int y) ;
        void mouseMoving(int x, int y) ;
        void mouseReleased(int x, int y) ;
        void mouseMovingAndPressed(int x, int y) ;

        void shitMaxEdited() ;

        void sliderMinHueMoved(int position) ;
        void sliderMaxHueMoved(int position) ;

        void sliderMinSaturationMoved(int position) ;
        void sliderMaxSaturationMoved(int position) ;

        void sliderMinValueMoved(int position) ;
        void sliderMaxValueMoved(int position) ;

        void truncateSound();

        void extractVideo() ;
        void setStartVideoExtraction() ;
        void setEndVideoExtraction() ;

        void nbClassChosen(int nbClass) ;
        void browseFileForClass_0() ;
        void browseFileForClass_1() ;
        void browseFileForClass_2() ;
        void browseFileForClass_3() ;
        void browseFileForClass_4() ;
        void launchAnalysis() ;




};

#endif // CONTROLLER_H
