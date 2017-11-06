#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QColorDialog>
#include "mainwindow.h"
#include "shiftmaxwindow.h"
#include "objecthisrogramwindow.h"
#include "thresholdvideowindow.h"
#include "extractvideowindow.h"
#include "audioanalysiswindow.h"

class View{
    private:
        MainWindow* mainWindow ;
        ShiftMaxWindow* shiftMaxWindow ;
        ObjectHistogramWindow* objectHistogramWindow ;
        ThresholdVideoWindow* thresholdVideoWindow ;
        QColorDialog* qColorDialog ;
        ExtractVideoWindow* extractVideoWindow ;
        AudioAnalysisWindow* audioAnalysisWindow ;

        std::vector<QWidget*> views ;

    public:
        View();
        ~View() ;
        QWidget* getMainWindow() ;
        QWidget* getShiftMaxWindow() ;
        QWidget* getObjectHistogramWindow() ;
        QWidget* getThresholdVideoWindow() ;
        QWidget* getQColorDialog() ;
        QWidget* getExtractVideoWindow() ;
        QWidget* getAudioAnalysisWindow() ;
};

#endif // VIEW_H
