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


Sound::Sound(){
    qMediaPlayer = new QMediaPlayer ;
}

void Sound::extractSound(QString filename){
    std::string file = filename.toStdString() + ".mp4";
    std::string fileAudio = filename.toStdString() + ".wav";
    GestionVideo gestionExtractAudio(file);
    gestionExtractAudio.extractAudio(fileAudio);
}


void Sound::extractWaveform(QString filename){
    /* QString cmd = "ffmpeg -i " + filename + ".wav "
                      "-filter_complex \"aformat=channel_layouts=mono,showwavespic=s=1280x120\" -frames:v 1 " +
                      filename + ".png" ;
        system(cmd.toStdString().c_str());*/



        int width = 1280;
        int height = 120;
        QString fileIn = filename + ".wav";
        QString fileOut = filename + ".png";
        Aquila::WaveFile wav(fileIn.toStdString());
        int max = 0;
        int total = wav.getSamplesCount()/width;
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
        QImage image(width,height,QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter paint;
        paint.begin(&image);
        paint.setPen(QColor(255, 0, 0));
        for(unsigned int i = 0; i < result.size(); i++)
        {
            double value;
            if(max >=  (height/2)){
                value = result.at(i)*(height/2) / max;
            }
            else{
                value = result.at(i);
            }
            if(value >= 0){
                paint.drawLine(QLineF(QPointF(i, (height/2)), QPointF(i, value + (height/2))));
                paint.drawLine(QLineF(QPointF(i, (height/2)), QPointF(i, (height/2) - value)));
            }

        }

        paint.end();
        image.save(fileOut);
}

bool Sound::truncateSound(QString filename, double start)
{
    try
    {
        Aquila::WaveFile wav(filename.toStdString() + ".wav");

        int duration = wav.getAudioLength();
        start = duration * start;

        QFile infile(filename + ".wav");
        QFile outfile(filename + "New.wav");

        infile.open(QIODevice::ReadOnly);


        QByteArray data = infile.readAll();
        QByteArray newData;
        double temp = (data.length()*1.)/duration;
        int startTruncate = (start*1.) * temp;
        std::cout << "startTruncate : " << startTruncate << endl;

        infile.close();

        newData.resize(44+(data.length()-startTruncate));

        //on recopie l'entête du fichier wav dans le nouveau fichier
        int i = 0;
        for(i = 0; i < 44;i++)
        {
            newData[i] = data[i];
        }

        //on recopie les data du fichier wav dans le nouveau fichier à partir du nouvel instant 0
        i = 44;
        for(int y = 43 + startTruncate; y < data.length();y++)
        {
            newData[i] = data[y];
            i++;
        }

        outfile.open(QIODevice::WriteOnly);
        outfile.write(newData);
        outfile.close();


        //On génère le nouveau waveform correspondant au nouveau fichier wav
        infile.rename(filename + ".wav", filename + "Save.wav");
        outfile.rename(filename + "New.wav", filename + ".wav");

        QFile waveformBack(filename + ".png");
        waveformBack.rename(filename + ".png", filename + "Save.png");
        QFile waveform(filename + ".png");
        try
        {
            Model model;
            model.getSound()->extractWaveform(filename);
        }
        catch(std::exception)
        {
            QMessageBox msgBox;
            msgBox.setText("Cannot create Waveform");
            msgBox.exec();

            return false;
        }

    }
    catch(std::exception)
    {
        return false;
    }

    return true;
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

void Sound::runAnalysis(QString currentPath){


    if(soundFileToCompare.compare("") != 0)
    {

        Aquila::WaveFile * waveIn0 = new Aquila::WaveFile(soundFileToCompare.toStdString().c_str());
        Aquila::FramesCollection * frameCollection0 =new Aquila::FramesCollection(*waveIn0, 4096);
        std::vector<std::vector<double> > dtwdt0;
        Aquila::Mfcc mfcc0(4096);
        for(unsigned int i = 0; i < frameCollection0->count() ; i++)
        {
            Aquila::Frame frame = frameCollection0->frame(i);
            std::vector<double> mfccValues = mfcc0.calculate(frame);
            dtwdt0.push_back(mfccValues);
        }
        delete frameCollection0;
        delete waveIn0;
        if(soundFileClass_0.compare("") != 0){

            Aquila::WaveFile * waveIn1 = new Aquila::WaveFile(soundFileClass_0.toStdString().c_str());
            Aquila::FramesCollection * frameCollection1 = new Aquila::FramesCollection(*waveIn1, 4096);
            std::vector<std::vector<double> > dtwdt1;
            Aquila::Mfcc mfcc1(4096);
            for(unsigned int i = 0; i < frameCollection1->count(); i++)
            {
                Aquila::Frame frame = frameCollection1->frame(i);
                std::vector<double> mfccValues = mfcc1.calculate(frame);
                dtwdt1.push_back(mfccValues);
            }
            delete frameCollection1;
            delete waveIn1;
            Aquila::Dtw dtw(Aquila::euclideanDistance, Aquila::Dtw::PassType::Diagonals);
            double distance_1 = dtw.getDistance(dtwdt0, dtwdt1);
            resultSoundFile_0 = QString::number(distance_1);
        }
        if(soundFileClass_1.compare("") != 0){

            Aquila::WaveFile * waveIn1 = new Aquila::WaveFile(soundFileClass_2.toStdString().c_str());
            Aquila::FramesCollection * frameCollection1 = new Aquila::FramesCollection(*waveIn1, 4096);
            std::vector<std::vector<double> > dtwdt1;
            Aquila::Mfcc mfcc1(4096);
            for(unsigned int i = 0; i < frameCollection1->count(); i++)
            {
                Aquila::Frame frame = frameCollection1->frame(i);
                std::vector<double> mfccValues = mfcc1.calculate(frame);
                dtwdt1.push_back(mfccValues);
            }
            delete frameCollection1;
            delete waveIn1;
            Aquila::Dtw dtw(Aquila::euclideanDistance, Aquila::Dtw::PassType::Diagonals);
            double distance_1 = dtw.getDistance(dtwdt0, dtwdt1);
            resultSoundFile_2 = QString::number(distance_1);
        }
        if(soundFileClass_2.compare("") != 0){

            Aquila::WaveFile * waveIn1 = new Aquila::WaveFile(soundFileClass_2.toStdString().c_str());
            Aquila::FramesCollection * frameCollection1 = new Aquila::FramesCollection(*waveIn1, 4096);
            std::vector<std::vector<double> > dtwdt1;
            Aquila::Mfcc mfcc1(4096);
            for(unsigned int i = 0; i < frameCollection1->count(); i++)
            {
                Aquila::Frame frame = frameCollection1->frame(i);
                std::vector<double> mfccValues = mfcc1.calculate(frame);
                dtwdt1.push_back(mfccValues);
            }
            delete frameCollection1;
            delete waveIn1;
            Aquila::Dtw dtw(Aquila::euclideanDistance, Aquila::Dtw::PassType::Diagonals);
            double distance_1 = dtw.getDistance(dtwdt0, dtwdt1);
            resultSoundFile_2 = QString::number(distance_1);
        }
        if(soundFileClass_3.compare("") != 0){

            Aquila::WaveFile * waveIn1 = new Aquila::WaveFile(soundFileClass_3.toStdString().c_str());
            Aquila::FramesCollection * frameCollection1 = new Aquila::FramesCollection(*waveIn1, 4096);
            std::vector<std::vector<double> > dtwdt1;
            Aquila::Mfcc mfcc1(4096);
            for(unsigned int i = 0; i < frameCollection1->count(); i++)
            {
                Aquila::Frame frame = frameCollection1->frame(i);
                std::vector<double> mfccValues = mfcc1.calculate(frame);
                dtwdt1.push_back(mfccValues);
            }
            delete frameCollection1;
            delete waveIn1;
            Aquila::Dtw dtw(Aquila::euclideanDistance, Aquila::Dtw::PassType::Diagonals);
            double distance_1 = dtw.getDistance(dtwdt0, dtwdt1);
            resultSoundFile_3 = QString::number(distance_1);
        }
        if(soundFileClass_4.compare("") != 0){

            Aquila::WaveFile * waveIn1 = new Aquila::WaveFile(soundFileClass_4.toStdString().c_str());
            Aquila::FramesCollection * frameCollection1 = new Aquila::FramesCollection(*waveIn1, 4096);
            std::vector<std::vector<double> > dtwdt1;
            Aquila::Mfcc mfcc1(4096);
            for(unsigned int i = 0; i < frameCollection1->count(); i++)
            {
                Aquila::Frame frame = frameCollection1->frame(i);
                std::vector<double> mfccValues = mfcc1.calculate(frame);
                dtwdt1.push_back(mfccValues);
            }
            delete frameCollection1;
            delete waveIn1;
            Aquila::Dtw dtw(Aquila::euclideanDistance, Aquila::Dtw::PassType::Diagonals);
            double distance_1 = dtw.getDistance(dtwdt0, dtwdt1);
            resultSoundFile_4 = QString::number(distance_1);
        }
    }


    /*QString scriptFile = currentPath + "/s_compare.py" ;

    if(soundFileClass_0.compare("") != 0){
        process.start("python", QStringList() << scriptFile << soundFileToCompare << soundFileClass_0);
        process.waitForFinished() ;
        resultSoundFile_0 =  QString::fromStdString(process.readAllStandardOutput().toStdString());
    }

    if(soundFileClass_1.compare("") != 0){
        process.start("python", QStringList() << scriptFile << soundFileToCompare << soundFileClass_1);
        process.waitForFinished() ;
        resultSoundFile_1 =  QString::fromStdString(process.readAllStandardOutput().toStdString());
    }

    if(soundFileClass_2.compare("") != 0){
        process.start("python", QStringList() << scriptFile << soundFileToCompare << soundFileClass_2);
        process.waitForFinished() ;
        resultSoundFile_2 =  QString::fromStdString(process.readAllStandardOutput().toStdString());
    }

    if(soundFileClass_3.compare("") != 0){
        process.start("python", QStringList() << scriptFile << soundFileToCompare << soundFileClass_3);
        process.waitForFinished() ;
        resultSoundFile_3 =  QString::fromStdString(process.readAllStandardOutput().toStdString());
    }

    if(soundFileClass_4.compare("") != 0){
        process.start("python", QStringList() << scriptFile << soundFileToCompare << soundFileClass_4);
        process.waitForFinished() ;
        resultSoundFile_4 =  QString::fromStdString(process.readAllStandardOutput().toStdString());
    }*/

}

Sound::~Sound(){ delete qMediaPlayer ; }
