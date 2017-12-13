#ifndef SOUND_H
#define SOUND_H

#include <QString>
#include <sstream>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QMediaPlayer>

class Sound{
    private:
        QString soundFileClass_0 ;
        QString soundFileClass_1 ;
        QString soundFileClass_2 ;
        QString soundFileClass_3 ;
        QString soundFileClass_4 ;
        QString soundFileToCompare ;

        QString resultSoundFile_0 ;
        QString resultSoundFile_1 ;
        QString resultSoundFile_2 ;
        QString resultSoundFile_3 ;
        QString resultSoundFile_4 ;

        QMediaPlayer* qMediaPlayer ;
    public:
        Sound();
        ~Sound();
        void extractSound(QString filename) ;
        void extractWaveform(QString filename) ;
        static void audio_encode(const char *filename);
        void setMedia(QString filename) ;
        void play() ;
        void pause() ;
        void stop() ;
        void setPosition(qint64 position) ;

        void setSoundFileClass_0(QString filename) ;
        void setSoundFileClass_1(QString filename) ;
        void setSoundFileClass_2(QString filename) ;
        void setSoundFileClass_3(QString filename) ;
        void setSoundFileClass_4(QString filename) ;
        void setSoundFileToCompare(QString filename) ;

        QString getResultSoundFile_0() ;
        QString getResultSoundFile_1() ;
        QString getResultSoundFile_2() ;
        QString getResultSoundFile_3() ;
        QString getResultSoundFile_4() ;
};

#endif // SOUND_H
