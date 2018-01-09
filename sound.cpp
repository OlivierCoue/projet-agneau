#include "sound.h"
#include <sstream>
#include <QProcess>
#include <QFile>
#include <QCoreApplication>
#include <global.h>
#include <source/WaveFile.h>
#include <transform/Mfcc.h>
#include <ml/Dtw.h>
#include <source/FramesCollection.h>
#include <QPainter>
#include <QTime>
#include <gestionvideo.h>
#include <model.h>
#include <QMessageBox.h>
#include <QTextCodec.h>
#include <iostream>

Sound::Sound(){
    qMediaPlayer = new QMediaPlayer ;
}

void Sound::extractSound(QString filename){
    std::string file = filename.toStdString() + ".mp4";
    std::string fileAudio = filename.toStdString() + ".wav";
    GestionVideo gestionExtractAudio(file);
    gestionExtractAudio.extractAudio(fileAudio);
}

void Sound::initPlotVectors(int frameCount, QCustomPlot & qCPsoundSignal, QString filename){

    int width = frameCount;
    int height = 120;

    QVector<double> x(frameCount), y(frameCount);


    QString fileIn = filename + ".wav";

    Aquila::WaveFile wav(fileIn.toStdString());
    int max = 0;
    int total = wav.getSamplesCount() / width;
    std::vector<double> result;
    double calcul = 0;
    for(unsigned int i = 0; i < wav.getSamplesCount(); i++){
        if(i%total == total - 1)
        {
            result.push_back(calcul/total);
            if(calcul/total > max)
                max = calcul/total;
            calcul = 0;
        }
        else
        {
            calcul += qAbs(wav.sample(i));
        }
    }

    double maxY = 0;

    for(unsigned int i = 0; i < result.size(); i++)
    {
        double value;
        if(max >= (height/2)){
            value = result.at(i)*(height/2) / max;
        }
        else{
            value = result.at(i);
        }
        if(value >= 0){
            x[i] = i;
            y[i] = value;

            if (value > maxY) {
                maxY = value;
            }
        }
    }

    qCPsoundSignal.graph(0)->setData(x, y);
    qCPsoundSignal.xAxis->setRange(0, width);
    qCPsoundSignal.yAxis->setRange(0, maxY);
    qCPsoundSignal.setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);
    qCPsoundSignal.replot();

}

void Sound::initCursor(QCustomPlot & qCPsoundSignal){
    this->item = new QCPItemLine(&qCPsoundSignal);
    item->setPen(QPen(Qt::red));
    item->start->setCoords(1,0);
    item->end->setCoords(1,120);
    qCPsoundSignal.replot();
}

void Sound::updateCursor(int value, QCustomPlot & qCPsoundSignal){
    this->item->start->setCoords(value,0);
    this->item->end->setCoords(value,120);
    qCPsoundSignal.replot();
}

void Sound::setMedia(QString filename){
    qMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
    qMediaPlayer->setVolume(100);
}

void Sound::play(){qMediaPlayer->play();}
void Sound::pause(){qMediaPlayer->pause();}
void Sound::stop(){qMediaPlayer->stop();}
void Sound::setPosition(qint64 position){qMediaPlayer->setPosition(position);}

void Sound::setSoundFileClass_0(QString filename){soundFileClass_0 = filename ;}
void Sound::setSoundFileClass_1(QString filename){soundFileClass_1 = filename ;}
void Sound::setSoundFileClass_2(QString filename){soundFileClass_2 = filename ;}
void Sound::setSoundFileClass_3(QString filename){soundFileClass_3 = filename ;}
void Sound::setSoundFileClass_4(QString filename){soundFileClass_4 = filename ;}
void Sound::setSoundFileToCompare(QString filename){soundFileToCompare = filename ;}

QString  Sound::getResultSoundFile_0(){return resultSoundFile_0 ;}
QString  Sound::getResultSoundFile_1(){return resultSoundFile_1 ;}
QString  Sound::getResultSoundFile_2(){return resultSoundFile_2 ;}
QString  Sound::getResultSoundFile_3(){return resultSoundFile_3 ;}
QString  Sound::getResultSoundFile_4(){return resultSoundFile_4 ;}

Sound::~Sound(){ delete qMediaPlayer ; }
