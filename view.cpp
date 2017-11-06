#include "view.h"
#include "QMainWindow"

View::View(){
    mainWindow = new MainWindow() ;
    shiftMaxWindow = new ShiftMaxWindow() ;
    objectHistogramWindow = new ObjectHistogramWindow() ;
    thresholdVideoWindow = new ThresholdVideoWindow() ;
    qColorDialog = new QColorDialog() ;
    extractVideoWindow = new ExtractVideoWindow() ;
    audioAnalysisWindow = new AudioAnalysisWindow() ;

    qColorDialog->setWindowFlags(Qt::Widget);
    qColorDialog->setModal(true);

    views.push_back(mainWindow);
    views.push_back(shiftMaxWindow) ;
    views.push_back((QWidget*)objectHistogramWindow);
    views.push_back(thresholdVideoWindow);
    views.push_back(qColorDialog);
    views.push_back(extractVideoWindow);
    views.push_back(audioAnalysisWindow);
}

QWidget* View::getMainWindow(){ return views[0] ; }
QWidget* View::getShiftMaxWindow(){ return views[1] ; }
QWidget* View::getObjectHistogramWindow(){ return views[2] ; }
QWidget* View::getThresholdVideoWindow(){return views[3] ;}
QWidget* View::getQColorDialog(){return views[4] ;}
QWidget* View::getExtractVideoWindow(){return views[5] ;}
QWidget* View::getAudioAnalysisWindow(){return views[6] ;}

View::~View(){
    delete audioAnalysisWindow ;
    delete extractVideoWindow ;
    delete qColorDialog ;
    delete thresholdVideoWindow ;
    delete objectHistogramWindow ;
    delete shiftMaxWindow ;
    delete mainWindow ;
    views.clear();
}
