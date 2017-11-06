#ifndef THRESHOLDVIDEOWINDOW_H
#define THRESHOLDVIDEOWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QColorDialog>
#include <QPushButton>
#include <QSlider>
#include <QString>
class ThresholdVideoWindow : public QDialog{
    private:
        QLabel* qLabelThreshold ;
        QVBoxLayout* qVBoxlayout ;

        QHBoxLayout* qHBoxLayoutHue ;
        QHBoxLayout* qHBoxLayoutSaturation ;
        QHBoxLayout* qHBoxLayoutValue ;

        QPushButton* qPushButton ;

        QLabel* qLabelMinHue ;
        QLabel* qLabelMinSaturation ;
        QLabel* qLabelMinValue ;

        QLabel* qLabelMaxHue ;
        QLabel* qLabelMaxSaturation ;
        QLabel* qLabelMaxValue ;

        QSlider* qSliderMinHue ;
        QSlider* qSliderMaxHue ;
        QSlider* qSliderMinSaturation ;
        QSlider* qSliderMaxSaturation ;
        QSlider* qSliderMinValue ;
        QSlider* qSliderMaxValue ;

        void init() ;
    public:
        ThresholdVideoWindow();
        void displayImage(QImage img) ;
        QPushButton* getQPushButton() ;
        QSlider* getQSliderMinHue() ;
        QSlider* getQSliderMaxHue() ;
        QSlider* getQSliderMinSaturation() ;
        QSlider* getQSliderMaxSaturation() ;
        QSlider* getQSliderMinValue() ;
        QSlider* getQSliderMaxValue() ;

        void setQLabelMinHue(QString minHue) ;
        void setQLabelMinSaturation(QString minSaturation) ;
        void setQLabelMinValue(QString minValue) ;

        void setQLabelMaxHue(QString maxHue) ;
        void setQLabelMaxSaturation(QString maxSaturation) ;
        void setQLabelMaxValue(QString maxValue) ;

        ~ThresholdVideoWindow() ;
};

#endif // THRESHOLDVIDEOWINDOW_H
