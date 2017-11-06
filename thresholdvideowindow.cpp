#include "thresholdvideowindow.h"

ThresholdVideoWindow::ThresholdVideoWindow(){
    qLabelThreshold = new QLabel ;
    qVBoxlayout = new QVBoxLayout ;

    qHBoxLayoutHue = new QHBoxLayout ;
    qHBoxLayoutSaturation = new QHBoxLayout ;
    qHBoxLayoutValue = new QHBoxLayout ;

    qPushButton = new QPushButton("Appliquer couleur") ;

    qSliderMinHue = new QSlider(Qt::Horizontal) ;
    qSliderMinHue->setMinimum(0);
    qSliderMinHue->setMaximum(350);
    qSliderMinHue->setValue(36);

    qSliderMaxHue = new QSlider(Qt::Horizontal) ;
    qSliderMaxHue->setMinimum(0);
    qSliderMaxHue->setMaximum(350);
    qSliderMaxHue->setValue(88);

    qSliderMinSaturation = new QSlider(Qt::Horizontal) ;
    qSliderMinSaturation->setMinimum(0);
    qSliderMinSaturation->setMaximum(255);
    qSliderMinSaturation->setValue(20);

    qSliderMaxSaturation = new QSlider(Qt::Horizontal) ;
    qSliderMaxSaturation->setMinimum(0);
    qSliderMaxSaturation->setMaximum(255);
    qSliderMaxSaturation->setValue(255);

    qSliderMinValue = new QSlider(Qt::Horizontal) ;
    qSliderMinValue->setMinimum(0);
    qSliderMinValue->setMaximum(255);
    qSliderMinValue->setValue(83);

    qSliderMaxValue = new QSlider(Qt::Horizontal) ;
    qSliderMaxValue->setMinimum(0);
    qSliderMaxValue->setMaximum(255);
    qSliderMaxValue->setValue(255);

    qLabelMinHue = new QLabel("36") ;
    qLabelMinSaturation = new QLabel("20") ;
    qLabelMinValue = new QLabel("83") ;

    qLabelMaxHue = new QLabel("88") ;
    qLabelMaxSaturation = new QLabel("255") ;
    qLabelMaxValue = new QLabel("255") ;

    init();
}

void ThresholdVideoWindow::init(){

    setFixedSize(600,400);
    qLabelThreshold->setStyleSheet("background-color :black;");
    qVBoxlayout->addWidget(qLabelThreshold);

    qHBoxLayoutHue->addWidget(qLabelMinHue);
    qHBoxLayoutHue->addWidget(qSliderMinHue);
    qHBoxLayoutHue->addWidget(qLabelMaxHue);
    qHBoxLayoutHue->addWidget(qSliderMaxHue);
    qVBoxlayout->addLayout(qHBoxLayoutHue);


    qHBoxLayoutSaturation->addWidget(qLabelMinSaturation);
    qHBoxLayoutSaturation->addWidget(qSliderMinSaturation);
    qHBoxLayoutSaturation->addWidget(qLabelMaxSaturation);
    qHBoxLayoutSaturation->addWidget(qSliderMaxSaturation);
    qVBoxlayout->addLayout(qHBoxLayoutSaturation);


    qHBoxLayoutValue->addWidget(qLabelMinValue);
    qHBoxLayoutValue->addWidget(qSliderMinValue);
    qHBoxLayoutValue->addWidget(qLabelMaxValue);
    qHBoxLayoutValue->addWidget(qSliderMaxValue);
    qVBoxlayout->addLayout(qHBoxLayoutValue);

    qVBoxlayout->addWidget(qPushButton);
    setLayout(qVBoxlayout);
}

void ThresholdVideoWindow::displayImage(QImage img){
    qLabelThreshold->setPixmap(QPixmap::fromImage(img).scaled(qLabelThreshold->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    qLabelThreshold->adjustSize();
}

QPushButton* ThresholdVideoWindow::getQPushButton(){return qPushButton;}
QSlider* ThresholdVideoWindow::getQSliderMinHue(){return qSliderMinHue ;}
QSlider* ThresholdVideoWindow::getQSliderMaxHue(){return qSliderMaxHue ;}
QSlider* ThresholdVideoWindow::getQSliderMinSaturation(){return qSliderMinSaturation ;}
QSlider* ThresholdVideoWindow::getQSliderMaxSaturation(){return qSliderMaxSaturation ;}
QSlider* ThresholdVideoWindow::getQSliderMinValue(){return qSliderMinValue ;}
QSlider* ThresholdVideoWindow::getQSliderMaxValue(){return qSliderMaxValue ;}

void ThresholdVideoWindow::setQLabelMinHue(QString minHue){ qLabelMinHue->setText(minHue);}
void ThresholdVideoWindow::setQLabelMinSaturation(QString minSaturation){qLabelMinSaturation->setText(minSaturation); ;}
void ThresholdVideoWindow::setQLabelMinValue(QString minValue){qLabelMinValue->setText(minValue);}

void ThresholdVideoWindow::setQLabelMaxHue(QString maxHue){ qLabelMaxHue->setText(maxHue);}
void ThresholdVideoWindow::setQLabelMaxSaturation(QString maxSaturation){ qLabelMaxSaturation->setText(maxSaturation);}
void ThresholdVideoWindow::setQLabelMaxValue(QString maxValue){ qLabelMaxValue->setText(maxValue);}

ThresholdVideoWindow::~ThresholdVideoWindow(){
    delete qLabelMaxValue;
    delete qLabelMaxSaturation;
    delete qLabelMaxHue;

    delete qLabelMinValue;
    delete qLabelMinSaturation;
    delete qLabelMinHue;

    delete qSliderMaxValue;
    delete qSliderMinValue;
    delete qSliderMaxSaturation;
    delete qSliderMinSaturation;
    delete qSliderMaxHue;
    delete qSliderMinHue;
    delete qPushButton;

    delete qHBoxLayoutValue;
    delete qHBoxLayoutSaturation;
    delete qHBoxLayoutHue;

    delete qVBoxlayout;
    delete qLabelThreshold;
}

