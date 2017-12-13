#include "controller.h"

#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QHash>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStringList>
#include <stdlib.h>



Controller::Controller(Model *model, View *view){
    this->model = model ;
    this->view = view ;

    if(!QDir("Videos").exists())
        QDir().mkdir("Videos") ;
    currentPath = QDir::currentPath() ;
    QDir::setCurrent(QDir::currentPath() + "/Videos") ;
    currentPathVideos = QDir::currentPath() ;


    qWidgetMainWindow = view->getMainWindow() ;
    qWidgetShiftMaxWindow = view->getShiftMaxWindow() ;
    qWidgetObjectHistogramWindow = view->getObjectHistogramWindow() ;
    qWidgetVideoThresholdWindow = view->getThresholdVideoWindow() ;
    qWidgetColorSelection = view->getQColorDialog() ;
    qWidgetExtractVideoWindow = view->getExtractVideoWindow() ;


    ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setMouseTracking(true);
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQActionShiftMax(), SIGNAL(triggered()), this, SLOT(displayShiftMaxDialog()) ) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQActionOpenVideo(), SIGNAL(triggered()), this, SLOT(openVideoFile()) ) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQActionObjectHistogram(), SIGNAL(triggered(bool)), this, SLOT(displayObjectHistogram())) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQActionAlgorithmColors(), SIGNAL(triggered(bool)), this, SLOT(algorithmColorsChecked(bool)) );
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQActionAlgorithmSubstraction(), SIGNAL(triggered(bool)), this, SLOT(algorithmSubstractionChecked(bool)) );
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQActionOpenThresholdVideo(), SIGNAL(triggered(bool)), this, SLOT(displayVideoThreshold()) );
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQActionOpenColorSelection(), SIGNAL(triggered(bool)), this, SLOT(displayColorSelection()) ) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQActionExtractVideo(), SIGNAL(triggered(bool)), this, SLOT(displayExtractVideo()) ) ;

    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay(), SIGNAL(mouseMoved(int,int)), this, SLOT(mouseMoving(int,int))) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay(), SIGNAL(mousePressed(int,int)), this, SLOT(mousePressed(int,int))) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay(), SIGNAL(mouseReleased(int,int)), this, SLOT(mouseReleased(int,int))) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay(), SIGNAL(mousePressedAndMoving(int,int)), this, SLOT(mouseMovingAndPressed(int,int))) ;

    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQSlider(), SIGNAL(sliderMoved(int)), this, SLOT(sliderVideoMoved(int))) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQSlider(), SIGNAL(sliderPressed()), this, SLOT(sliderVideoPressed()) ) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQSlider(), SIGNAL(sliderReleased()), this, SLOT(sliderVideoReleased()) ) ;

    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonFastBackward(), SIGNAL(clicked(bool)), this, SLOT(fastBackward()) );
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonFastForward(), SIGNAL(clicked(bool)), this, SLOT(fastForward()) );
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonBackward(), SIGNAL(clicked(bool)), this, SLOT(backward()) );
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonForward(), SIGNAL(clicked(bool)), this, SLOT(forward()) );
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonEnd(), SIGNAL(clicked(bool)), this, SLOT(endVideo()) );
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonStart(), SIGNAL(clicked(bool)), this, SLOT(beginningVideo()) );
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause(), SIGNAL(clicked(bool)), this, SLOT(playStopVideo()) ) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonSaveCoordinate(), SIGNAL(clicked(bool)), this, SLOT(saveTrajectory()) ) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonClear(), SIGNAL(clicked(bool)), this, SLOT(clearList()) ) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonStartVideoToExtract(), SIGNAL(clicked(bool)), this, SLOT(setStartVideoExtraction()) ) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQPushButtonEndVideoToExtract(), SIGNAL(clicked(bool)), this, SLOT(setEndVideoExtraction()) ) ;


    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQCheckBox(), SIGNAL(stateChanged(int)), this, SLOT(trajectoryChecked(int)) ) ;
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQRadioButtonTreatment(), SIGNAL(clicked(bool)), this, SLOT(treatmentChecked()) );
    QObject::connect( ((MainWindow*)qWidgetMainWindow)->getQRadioButtonVisualize(), SIGNAL(clicked(bool)), this, SLOT(visualizeChecked()) );


    QObject::connect( ((ShiftMaxWindow*)qWidgetShiftMaxWindow)->getQPushButton(), SIGNAL(clicked(bool)), this, SLOT(shitMaxEdited()) ) ;


    QObject::connect( ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQPushButton(), SIGNAL(clicked(bool)), this, SLOT(applyColor()) );

    QObject::connect( ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMinHue(), SIGNAL(sliderMoved(int)), this, SLOT(sliderMinHueMoved(int)) );
    QObject::connect( ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMaxHue(), SIGNAL(sliderMoved(int)), this, SLOT(sliderMaxHueMoved(int)) );
    QObject::connect( ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMinSaturation(), SIGNAL(sliderMoved(int)), this, SLOT(sliderMinSaturationMoved(int)) );
    QObject::connect( ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMaxSaturation(), SIGNAL(sliderMoved(int)), this, SLOT(sliderMaxSaturationMoved(int)) );
    QObject::connect( ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMinValue(), SIGNAL(sliderMoved(int)), this, SLOT(sliderMinValueMoved(int)) );
    QObject::connect( ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMaxValue(), SIGNAL(sliderMoved(int)), this, SLOT(sliderMaxValueMoved(int)) );


    QObject::connect( ((ExtractVideoWindow*)qWidgetExtractVideoWindow)->getQPushButton(), SIGNAL(clicked(bool)), this ,SLOT(extractVideo()) ) ;


    QObject::connect( model->getVideo(), SIGNAL(processedImage(QImage, int, QString)), this, SLOT(updateVideo(QImage, int, QString)));
    QObject::connect( model->getVideo(), SIGNAL(processedThresholdImage(QImage)), this, SLOT(updateThresholdVideo(QImage)) );

    model->getSound()->setSoundFileToCompare("");
}

void Controller::displayShiftMaxDialog(){ ((ShiftMaxWindow*)qWidgetShiftMaxWindow)->show();}
void Controller::displayVideoThreshold(){ ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->show();}
void Controller::displayColorSelection(){ ((QColorDialog*)qWidgetColorSelection)->show() ; }
void Controller::displayExtractVideo(){
    std::stringstream s ;
    if((((MainWindow*)qWidgetMainWindow)->getQLabelStartVideoToExtract()->text().compare("--:--") == 0) ||
            (((MainWindow*)qWidgetMainWindow)->getQLabelEndVideoToExtract()->text().compare("--:--") ==0)){
        s << "Veuillez choisir une durée à extraire !!" ;
        ((ExtractVideoWindow*)qWidgetExtractVideoWindow)->getQPushButton()->setVisible(false);
    }else if( ((MainWindow*)qWidgetMainWindow)->getQLabelStartVideoToExtract()->text().compare(((MainWindow*)qWidgetMainWindow)->getQLabelEndVideoToExtract()->text()) == 0 ){
        s << "Vous ne pouvez pas choisir la même durée !!" ;
        ((ExtractVideoWindow*)qWidgetExtractVideoWindow)->getQPushButton()->setVisible(false);
    }else{
        s << "Confirmez-vous de vouloir extraire la video sur la durée de [" << ((MainWindow*)qWidgetMainWindow)->getQLabelStartVideoToExtract()->text().toStdString() << " " << ((MainWindow*)qWidgetMainWindow)->getQLabelEndVideoToExtract()->text().toStdString() << "] ?" ;
        ((ExtractVideoWindow*)qWidgetExtractVideoWindow)->getQPushButton()->setVisible(true);
    }
    ((ExtractVideoWindow*)qWidgetExtractVideoWindow)->setQLabel(QString::fromStdString(s.str()));
    ((ExtractVideoWindow*)qWidgetExtractVideoWindow)->show();
}

void Controller::openVideoFile(){
    model->getVideo()->stop();
    model->getSound()->pause();
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");
    filename = QFileDialog::getOpenFileName(((MainWindow*)qWidgetMainWindow), "Ouvrir une vidéo", "../Videos", "Video Files (*.avi *.mpg *.mp4 *.asf *.mkv)") ;
    QMessageBox msgBox;

    if(!filename.isEmpty()){
        if(!model->getVideo()->loadVideo(filename.toStdString().data())){
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec() ;
        }

        QStringList list = filename.split("/") ;
        for(int i = 0 ; i < list.size()-1;i++)
        {
            folderName += list.at(i).toStdString().c_str();
            folderName += "/";
        }
        filename = list.at(list.size()-1).toStdString().c_str() ;
        list = filename.split(".") ;
        filename = list.at(0).toStdString().c_str() ;


        if(!QFile(folderName + filename+".wav").exists())
            msgBox.setText("in extract wav file!");
            msgBox.exec() ;
            model->getSound()->extractSound(folderName + filename);
        try {
            if(!QFile(folderName + filename+".png").exists() && QFile(folderName + filename+".wav").exists())
            {

                msgBox.setText("in extract waveform!");
                msgBox.exec() ;
                model->getSound()->extractWaveform(folderName + filename);
            }
        }
        catch(std::exception)
        {
            msgBox.setText("Cannot create Waveform");
            msgBox.exec();
        }

        ((MainWindow*)qWidgetMainWindow)->getQSlider()->setStyleSheet("margin-left: -70px; background-color :white; background-image: url("+folderName + filename+".png); ");
        model->getSound()->setMedia(folderName + filename+".wav");
        model->getSound()->setSoundFileToCompare(folderName + filename+".wav");

        int nbSeconds = model->getVideo()->getSecFromNbFrame(model->getVideo()->getNumberOfFrames()) ;
        std::stringstream s ;
        QString str;
        str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
        s << str.toStdString();
        //s << nbSeconds/60 << ":" << nbSeconds%60 ;
        ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");
        ((MainWindow*)qWidgetMainWindow)->enableControlButtons(true);
        ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setEnabled(true);
        ((MainWindow*)qWidgetMainWindow)->setWindowTitle(filename);
        ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setPixmap(QPixmap::fromImage(model->getVideo()->getFirstFrame()).scaled(((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
        ((MainWindow*)qWidgetMainWindow)->setQLabelFinishTime(QString::fromStdString(s.str()));
        ((MainWindow*)qWidgetMainWindow)->setQLabelCurrentTime(QString::fromStdString("00:00"));
        ((MainWindow*)qWidgetMainWindow)->getQSlider()->setMinimum(1);
        ((MainWindow*)qWidgetMainWindow)->getQSlider()->setMaximum(model->getVideo()->getNumberOfFrames());
        ((MainWindow*)qWidgetMainWindow)->getQSlider()->setValue(1);

        ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setChecked(false);
        ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setEnabled(false);
        ((MainWindow*)qWidgetMainWindow)->getQActionExtractVideo()->setEnabled(true);

        model->getVideo()->setTrajectoryChecked(false);
    }
}

void Controller::playStopVideo(){
    if(model->getVideo()->isStopped()){
        model->getVideo()->play();
        ((MainWindow*)qWidgetMainWindow)->setPlayPauseButton("Pause");
        model->getSound()->play();
    }else{
        model->getVideo()->stop();
        model->getSound()->pause();
        ((MainWindow*)qWidgetMainWindow)->setPlayPauseButton("Play");
    }

}

void Controller::displayObjectHistogram(){
    model->getVideo()->computeHistogramChosenObject();
    ((ObjectHistogramWindow*)qWidgetObjectHistogramWindow)->setQLabelHistogram(model->getVideo()->getHistRed(),
                                                                               model->getVideo()->getHistGreen(),
                                                                               model->getVideo()->getHistBlue(),
                                                                               model->getVideo()->getRedMin(),
                                                                               model->getVideo()->getRedMax(),
                                                                               model->getVideo()->getGreenMin(),
                                                                               model->getVideo()->getGreenMax(),
                                                                               model->getVideo()->getBlueMin(),
                                                                               model->getVideo()->getBlueMax());
    ((ObjectHistogramWindow*)qWidgetObjectHistogramWindow)->show();
}

void Controller::updateVideo(QImage img, int currentFrame, QString info){
    if(currentFrame == 1)
        ((MainWindow*)qWidgetMainWindow)->setPlayPauseButton("Play");

    ((MainWindow*)qWidgetMainWindow)->displayImageQLabelVideo(img);
    ((MainWindow*)qWidgetMainWindow)->getQSlider()->setValue(currentFrame);

    int nbSeconds = model->getVideo()->getSecFromNbFrame(currentFrame) ;
    std::stringstream s ;
    QString str;
    str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
    s << str.toStdString();
    //s << nbSeconds/60 << ":" << nbSeconds%60 ;
    ((MainWindow*)qWidgetMainWindow)->setQLabelCurrentTime(QString::fromStdString(s.str()));
    if(info != ""){
        QListWidgetItem* qListWidgetItem = new QListWidgetItem(info, ((MainWindow*)qWidgetMainWindow)->getQListWidget());
        ((MainWindow*)qWidgetMainWindow)->getQListWidget()->addItem(qListWidgetItem);
        ((MainWindow*)qWidgetMainWindow)->getQListWidget()->scrollToBottom();
    }
}

void Controller::updateThresholdVideo(QImage img){
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->displayImage(img);
}

void Controller::saveTrajectory(){
    std::stringstream s ;
    s << folderName.left(folderName.length() - 4).toStdString() << ".csv" ;

    QString filename = QFileDialog::getSaveFileName(((MainWindow*)qWidgetMainWindow), "Savegarder la trajectoire", QString::fromStdString(s.str()), "csv fichiers (*.csv);;All files (*.*)") ;
    QFile data(filename) ;

    if(data.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream output(&data) ;
        int count = ((MainWindow*)qWidgetMainWindow)->getQListWidget()->count() ;
        for(int i = 0 ; i < count ; i++){
            output << "" ;
            output << ((MainWindow*)qWidgetMainWindow)->getQListWidget()->item(i)->text() << "\n";
        }
    }

    data.close();
}
void Controller::loadTrajectory(){

}

void Controller::clearList(){((MainWindow*)qWidgetMainWindow)->getQListWidget()->clear();}

void Controller::shitMaxEdited(){
    model->getVideo()->setShiftMax(((ShiftMaxWindow*)qWidgetShiftMaxWindow)->getQLineEdit()->text().toInt());
    ((ShiftMaxWindow*)qWidgetShiftMaxWindow)->close() ;
}
void Controller::sliderVideoPressed(){
    model->getVideo()->stop();
    model->getSound()->stop();
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");
}

void Controller::sliderVideoMoved(int position){

    positionSlide = position;
    std::stringstream s ;
    int nbSeconds = model->getVideo()->getSecFromNbFrame(position) ;

    /*int nbMiliSecs = model->getVideo()->getCurrentFrameID() * 1000 / model->getVideo()->getFramerate();
    model->getSound()->setPosition(nbMiliSecs);*/
    QString str;
    str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
    s << str.toStdString();
    //s << nbSeconds/60 << ":" << nbSeconds%60 ;
    ((MainWindow*)qWidgetMainWindow)->setPlayPauseButton("Play");
    ((MainWindow*)qWidgetMainWindow)->setQLabelCurrentTime(QString::fromStdString(s.str()));
}

void Controller::sliderVideoReleased()
{
   model->getVideo()->setCurrentFrame(positionSlide);
   std::stringstream s ;
   int nbSeconds = model->getVideo()->getSecFromNbFrame(model->getVideo()->getCurrentFrameID()) ;

   int nbMiliSecs = model->getVideo()->getCurrentFrameID() * 1000 / model->getVideo()->getFramerate();
   model->getSound()->setPosition(nbMiliSecs);
   QString str;
   str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
   s << str.toStdString();
   //s << nbSeconds/60 << ":" << nbSeconds%60 ;
   ((MainWindow*)qWidgetMainWindow)->setPlayPauseButton("Play");
   ((MainWindow*)qWidgetMainWindow)->setQLabelCurrentTime(QString::fromStdString(s.str()));
}

void Controller::beginningVideo(){
    model->getVideo()->stop();
    model->getSound()->stop();
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");
    ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setPixmap(QPixmap::fromImage(model->getVideo()->getFirstFrame()).scaled(((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    ((MainWindow*)qWidgetMainWindow)->setQLabelCurrentTime(QString::fromStdString("00:00"));
    ((MainWindow*)qWidgetMainWindow)->getQSlider()->setValue(1);

}

void Controller::endVideo(){
    model->getVideo()->stop();
    model->getSound()->pause();
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");
    ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setPixmap(QPixmap::fromImage(model->getVideo()->getLastFrame()).scaled(((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    int nbSeconds = model->getVideo()->getSecFromNbFrame(model->getVideo()->getNumberOfFrames()) ;
    int nbMiliSecs = model->getVideo()->getCurrentFrameID() * 1000 / model->getVideo()->getFramerate();
    model->getSound()->setPosition(nbMiliSecs);
    //model->getSound()->setPosition(nbSeconds*1000);
    std::stringstream s ;
    QString str;
    str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
    s << str.toStdString();
    //s << nbSeconds/60 << ":" << nbSeconds%60 ;
    ((MainWindow*)qWidgetMainWindow)->setQLabelFinishTime(QString::fromStdString(s.str()));
    ((MainWindow*)qWidgetMainWindow)->getQSlider()->setValue(model->getVideo()->getNumberOfFrames());
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");
}

void Controller::backward(){
    model->getVideo()->stop();
    model->getSound()->pause();
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");

    if(model->getVideo()->getCurrentFrameID() > 0){
        ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setPixmap(QPixmap::fromImage(model->getVideo()->getPreviousFrame()).scaled(((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size(),Qt::KeepAspectRatio, Qt::FastTransformation));

        std::stringstream s ;
        int nbSeconds = model->getVideo()->getSecFromNbFrame(model->getVideo()->getCurrentFrameID()) ;
        int nbMiliSecs = model->getVideo()->getCurrentFrameID() * 1000 / model->getVideo()->getFramerate();
        model->getSound()->setPosition(nbMiliSecs);
        //model->getSound()->setPosition(nbSeconds*1000);
        QString str;
        str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
        s << str.toStdString();
        //s << nbSeconds/60 << ":" << nbSeconds%60 ;

        ((MainWindow*)qWidgetMainWindow)->setQLabelCurrentTime(QString::fromStdString(s.str()));
        ((MainWindow*)qWidgetMainWindow)->getQSlider()->setValue(model->getVideo()->getCurrentFrameID());
    }
}

void Controller::forward(){
    model->getVideo()->stop();
    model->getSound()->pause();
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");

    if(model->getVideo()->getCurrentFrameID() < model->getVideo()->getNumberOfFrames()){
        ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setPixmap(QPixmap::fromImage(model->getVideo()->getNextFrame()).scaled(((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size(),Qt::KeepAspectRatio, Qt::FastTransformation));

        std::stringstream s ;
        int nbSeconds = model->getVideo()->getSecFromNbFrame(model->getVideo()->getCurrentFrameID()) ;
        int nbMiliSecs = model->getVideo()->getCurrentFrameID() * 1000 / model->getVideo()->getFramerate();
        model->getSound()->setPosition(nbMiliSecs);
        //model->getSound()->setPosition(nbSeconds*1000);
        QString str;
        str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
        s << str.toStdString();
        //s << nbSeconds/60 << ":" << nbSeconds%60 ;

        ((MainWindow*)qWidgetMainWindow)->setQLabelCurrentTime(QString::fromStdString(s.str()));
        ((MainWindow*)qWidgetMainWindow)->getQSlider()->setValue(model->getVideo()->getCurrentFrameID());

    }
}

void Controller::fastBackward(){
    model->getVideo()->stop();
    model->getSound()->pause();
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");

    if(model->getVideo()->getCurrentFrameID() > 10){
        ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setPixmap(QPixmap::fromImage(model->getVideo()->getPreviousFrameExtended(10)).scaled(((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size(),Qt::KeepAspectRatio, Qt::FastTransformation));

        std::stringstream s ;
        int nbSeconds = model->getVideo()->getSecFromNbFrame(model->getVideo()->getCurrentFrameID()) ;
        int nbMiliSecs = model->getVideo()->getCurrentFrameID() * 1000 / model->getVideo()->getFramerate();
        model->getSound()->setPosition(nbMiliSecs);
        //model->getSound()->setPosition(nbSeconds*1000);
        QString str;
        str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
        s << str.toStdString();
        //s << nbSeconds/60 << ":" << nbSeconds%60 ;

        ((MainWindow*)qWidgetMainWindow)->setQLabelCurrentTime(QString::fromStdString(s.str()));
        ((MainWindow*)qWidgetMainWindow)->getQSlider()->setValue(model->getVideo()->getCurrentFrameID());

    }
}
void Controller::fastForward(){
    model->getVideo()->stop();
    model->getSound()->pause();
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");


    if(model->getVideo()->getCurrentFrameID() < model->getVideo()->getNumberOfFrames() - 10){
        ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setPixmap(QPixmap::fromImage(model->getVideo()->getNextFrameExtended(10)).scaled(((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size(),Qt::KeepAspectRatio, Qt::FastTransformation));

        std::stringstream s ;
        int nbSeconds = model->getVideo()->getSecFromNbFrame(model->getVideo()->getCurrentFrameID()) ;
        int nbMiliSecs = model->getVideo()->getCurrentFrameID() * 1000 / model->getVideo()->getFramerate();
        model->getSound()->setPosition(nbMiliSecs);
        //model->getSound()->setPosition(nbSeconds*1000);
        QString str;
        str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
        s << str.toStdString();
        //s << nbSeconds/60 << ":" << nbSeconds%60 ;

        ((MainWindow*)qWidgetMainWindow)->setQLabelCurrentTime(QString::fromStdString(s.str()));
        ((MainWindow*)qWidgetMainWindow)->getQSlider()->setValue(model->getVideo()->getCurrentFrameID());
    }
}

void Controller::algorithmColorsChecked(bool toogled){
    if(toogled)
    {
        ((MainWindow*)qWidgetMainWindow)->getQActionAlgorithmSubstraction()->setChecked(!toogled);
        ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setMouseTracking(!toogled);
        ((MainWindow*)qWidgetMainWindow)->getQActionOpenThresholdVideo()->setDisabled(!toogled);
        ((MainWindow*)qWidgetMainWindow)->getQActionOpenColorSelection()->setDisabled(!toogled);
        model->getVideo()->stop();
        model->getSound()->pause();
        ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");

        model->getVideo()->setAlgoIDtoRun(1);
        if(((MainWindow*)qWidgetMainWindow)->getQRadioButtonTreatment()->isChecked())
            ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setEnabled(toogled);
    }
    else
    {
        ((MainWindow*)qWidgetMainWindow)->getQActionAlgorithmSubstraction()->setChecked(!toogled);
        algorithmSubstractionChecked(!toogled);
    }

}

void Controller::algorithmSubstractionChecked(bool toogled){
    if(toogled)
    {
        ((MainWindow*)qWidgetMainWindow)->getQActionAlgorithmColors()->setChecked(!toogled);
        ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setMouseTracking(toogled);
        ((MainWindow*)qWidgetMainWindow)->getQActionOpenThresholdVideo()->setDisabled(toogled);
        ((MainWindow*)qWidgetMainWindow)->getQActionOpenColorSelection()->setDisabled(toogled);
        model->getVideo()->stop();
        model->getSound()->pause();
        ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");

        model->getVideo()->setAlgoIDtoRun(0);
        ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setEnabled(!toogled);
        ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setChecked(!toogled);

    }
    else
    {
        ((MainWindow*)qWidgetMainWindow)->getQActionAlgorithmColors()->setChecked(!toogled);
        algorithmColorsChecked(!toogled);
    }
}

void Controller::trajectoryChecked(int checked){
    bool c = (checked == 2) ? true : false ;
    model->getVideo()->setTrajectoryChecked(c);
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonSaveCoordinate()->setEnabled(c);
}
void Controller::visualizeChecked(){
    ((MainWindow*)qWidgetMainWindow)->getQListWidget()->clear();
    model->getVideo()->setVisualize(true);
    model->getVideo()->setTreatment(false);
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonSaveCoordinate()->setEnabled(false);
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonLoadCoordinate()->setEnabled(true);
    ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setChecked(false);
    ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setEnabled(false);
    model->getVideo()->setTrajectoryChecked(false);
}
void Controller::treatmentChecked(){
    ((MainWindow*)qWidgetMainWindow)->getQListWidget()->clear();
    model->getVideo()->setVisualize(false);
    model->getVideo()->setTreatment(true);
    if(((MainWindow*)qWidgetMainWindow)->getQActionAlgorithmColors()->isChecked())
        ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setEnabled(true);
    else if(((MainWindow*)qWidgetMainWindow)->getQActionObjectHistogram()->isEnabled())
    {
        model->getVideo()->isFirstFrame(true) ;
        model->getVideo()->toKeepRunning(false);
        ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setEnabled(true);
    }

    ((MainWindow*)qWidgetMainWindow)->getQPushButtonSaveCoordinate()->setEnabled(true);
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonLoadCoordinate()->setEnabled(false);
}

void Controller::mouseMoving(int x, int y){ ((MainWindow*)qWidgetMainWindow)->updateSatusBar(QString("Mouse's moving in :(%1,%2)").arg(x).arg(y));}

void Controller::mousePressed(int x, int y){
    model->getVideo()->stop();
    model->getSound()->pause();
    ((MainWindow*)qWidgetMainWindow)->getQPushButtonPlayPause()->setText("Play");
    int imgHeight = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().height();
    int videoDiplayHeight = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size().height();
    int imgWidth = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().width();
    int videoDiplayWidth = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size().width();

    if(x > (videoDiplayWidth - imgWidth)/2 && x < videoDiplayWidth - (videoDiplayWidth - imgWidth)/2
            && y > (videoDiplayHeight - imgHeight)/2 && y < videoDiplayHeight - (videoDiplayHeight - imgHeight)/2)
    {
        isMousePressed = false ;
        int ydecal = (videoDiplayHeight - imgHeight)/2;
        int xdecal = (videoDiplayWidth - imgWidth)/2;


        ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setPixmap(QPixmap::fromImage(model->getVideo()->getImageMousePressed(x - xdecal, y - ydecal,((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().height(),((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().width())).scaled(((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
        ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->adjustSize();
        ((MainWindow*)qWidgetMainWindow)->updateSatusBar(QString("Mouse pressed at :(%1,%2)").arg(x).arg(y));
        ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setChecked(false);
        ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setEnabled(false);
    }
    else
    {
        isMousePressed = false ;
        ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setChecked(false);
        ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setEnabled(false);
    }
    ((MainWindow*)qWidgetMainWindow)->getQActionObjectHistogram()->setDisabled(true);

}

void Controller::mouseMovingAndPressed(int x, int y){
    int imgHeight = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().height();
    int videoDiplayHeight = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size().height();
    int imgWidth = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().width();
    int videoDiplayWidth = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size().width();

    if(x > (videoDiplayWidth - imgWidth)/2 && x < videoDiplayWidth - (videoDiplayWidth - imgWidth)/2
            && y > (videoDiplayHeight - imgHeight)/2 && y < videoDiplayHeight - (videoDiplayHeight - imgHeight)/2)
    {
        isMousePressed = true ;
        int ydecal = (videoDiplayHeight - imgHeight)/2;
        int xdecal = (videoDiplayWidth - imgWidth)/2;
        QImage img = model->getVideo()->getImageMousePressedAndMoving(x - xdecal, y - ydecal,((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().height(),((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().width());
        if(img != (QImage)NULL)
        {
            ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setPixmap(QPixmap::fromImage(img).scaled(((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
            ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->adjustSize();
            ((MainWindow*)qWidgetMainWindow)->updateSatusBar(QString("Mouse pressed while moving :(%1,%2)").arg(x).arg(y));
            ((MainWindow*)qWidgetMainWindow)->getQActionObjectHistogram()->setDisabled(false);
        }

    }
    else
    {
        isMousePressed = true ;
    }
}

void Controller::mouseReleased(int x, int y){
    int imgHeight = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().height();
    int videoDiplayHeight = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size().height();
    int imgWidth = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().width();
    int videoDiplayWidth = ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size().width();

    if(isMousePressed)
    {
        int ydecal = (videoDiplayHeight - imgHeight)/2;
        int xdecal = (videoDiplayWidth - imgWidth)/2;
        QImage img = model->getVideo()->getImageMouseReleased(x - xdecal, y - ydecal,((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().height(),((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->pixmap()->size().width());
        if(img != (QImage)NULL)
        {
            ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->setPixmap(QPixmap::fromImage(img).scaled(((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
            ((MainWindow*)qWidgetMainWindow)->getQLabelVideoDisplay()->adjustSize();
            ((MainWindow*)qWidgetMainWindow)->updateSatusBar(QString("Mouse released at :(%1,%2)").arg(x).arg(y));
            ((MainWindow*)qWidgetMainWindow)->getQActionObjectHistogram()->setDisabled(false);
        }
        else
        {
            ((MainWindow*)qWidgetMainWindow)->getQActionObjectHistogram()->setDisabled(true);
        }
        if(((MainWindow*)qWidgetMainWindow)->getQRadioButtonTreatment()->isChecked() && img != (QImage)NULL){
            model->getVideo()->isFirstFrame(true) ;
            model->getVideo()->toKeepRunning(false);
            ((MainWindow*)qWidgetMainWindow)->getQCheckBox()->setEnabled(true);
        }
        isMousePressed = false;
    }
}

void Controller::applyColor(){
    QColor color = ((QColorDialog*)qWidgetColorSelection)->selectedColor() ;
    model->getVideo()->setMinHue(color.hue()) ;
    model->getVideo()->setMaxHue(color.hue()) ;

    model->getVideo()->setMaxSaturation(color.saturation());
    model->getVideo()->setMaxValue(color.value());

    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMinHue(QString::number(color.hue())) ;
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMinHue()->setValue(color.hue());
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMaxHue(QString::number(color.hue())) ;
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMaxHue()->setValue(color.hue());

    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMinSaturation(QString::number(color.saturation())) ;
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMinSaturation()->setValue(color.saturation());
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMaxSaturation(QString::number(color.saturation())) ;
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMaxSaturation()->setValue(color.saturation());

    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMinValue(QString::number(color.value())) ;
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMinValue()->setValue(color.value());
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMaxValue(QString::number(color.value())) ;
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->getQSliderMaxValue()->setValue(color.value());
}

void Controller::sliderMinHueMoved(int position){
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMinHue(QString::number(position)) ;
    model->getVideo()->setMinHue(position);
}
void Controller::sliderMaxHueMoved(int position){
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMaxHue(QString::number(position)) ;
    model->getVideo()->setMaxHue(position);
}
void Controller::sliderMinSaturationMoved(int position) {
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMinSaturation(QString::number(position)) ;
    model->getVideo()->setMinSaturation(position);
}
void Controller::sliderMaxSaturationMoved(int position) {
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMaxSaturation(QString::number(position)) ;
    model->getVideo()->setMaxSaturation(position);
}
void Controller::sliderMinValueMoved(int position) {
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMinValue(QString::number(position)) ;
    model->getVideo()->setMinValue(position);
}
void Controller::sliderMaxValueMoved(int position) {
    ((ThresholdVideoWindow*)qWidgetVideoThresholdWindow)->setQLabelMaxValue(QString::number(position)) ;
    model->getVideo()->setMaxValue(position);
}

void Controller::setStartVideoExtraction(){
    int nbSeconds = model->getVideo()->getSecFromNbFrame(model->getVideo()->getCurrentFrameID()) ;
    std::stringstream s ;
    QString str;
    str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
    s << str.toStdString();
    //s << nbSeconds/60 << ":" << nbSeconds%60 ;
    ((MainWindow*)qWidgetMainWindow)->setQLabelStartVideoToExtract(QString::fromStdString(s.str()));

    model->getVideo()->setFrameStartExtraction(model->getVideo()->getCurrentFrameID());

}

void Controller::setEndVideoExtraction(){
    int nbSeconds = model->getVideo()->getSecFromNbFrame(model->getVideo()->getCurrentFrameID()) ;
    std::stringstream s ;
    QString str;
    str.sprintf("%02d:%02d", nbSeconds/60, nbSeconds%60);
    s << str.toStdString();
    //s << nbSeconds/60 << ":" << nbSeconds%60 ;
    ((MainWindow*)qWidgetMainWindow)->setQLabelEndVideoToExtract(QString::fromStdString(s.str()));

    model->getVideo()->setFrameEndExtraction(model->getVideo()->getCurrentFrameID());
}

void Controller::extractVideo(){
    model->getVideo()->extractVideo(folderName + filename);
    ((ExtractVideoWindow*)qWidgetExtractVideoWindow)->close() ;
}

Controller::~Controller(){

}
