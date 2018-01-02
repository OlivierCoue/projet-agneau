#include "mainwindow.h"
#include <QVideoWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setWindowTitle("Decter");
    setFixedSize(1280, 780);

    qMenuFile = menuBar()->addMenu("&Fichier") ;
    qActionOpenVideo = new QAction(QIcon(":/images/lamb.png"), "&Ouvir un fichier...", this) ;
    qMenuFile->addAction(qActionOpenVideo) ;
    qActionQuit = new QAction("&Quitter", this) ;
    qMenuFile->addAction(qActionQuit) ;
    QObject::connect(qActionQuit, SIGNAL(triggered()), this, SLOT(close())) ;

    qMenuSetting = menuBar()->addMenu("&Réglage") ;
    qActionShiftMax = new QAction("&Déplacement max", this);
    qMenuSetting->addAction(qActionShiftMax) ;
    qMenueAlgorithms = qMenuSetting->addMenu("Algorithmes") ;
    qActionAlgorithmSubstraction = new QAction("&Algorithme soustraction", this) ;
    qActionAlgorithmSubstraction->setCheckable(true) ;
    qActionAlgorithmSubstraction->setChecked(true) ;
    qMenueAlgorithms->addAction(qActionAlgorithmSubstraction) ;
    qActionAlgorithmColors = new QAction("&Algorithme de couleur", this) ;
    qActionAlgorithmColors->setCheckable(true);
    qMenueAlgorithms->addAction(qActionAlgorithmColors) ;

    qMenuInformation = menuBar()->addMenu("&Information") ;
    qActionObjectHistogram = new QAction("&Information objet", this) ;
    qActionObjectHistogram->setDisabled(true);
    qMenuInformation->addAction(qActionObjectHistogram) ;
    qActionOpenThresholdVideo = new QAction("&Video seuillée", this) ;
    qActionOpenThresholdVideo->setDisabled(true);
    qMenuInformation->addAction(qActionOpenThresholdVideo) ;
    qActionOpenColorSelection = new QAction("&Selection de couleur", this) ;
    qActionOpenColorSelection->setDisabled(true);
    qMenuInformation->addAction(qActionOpenColorSelection) ;

    qMenueTools = menuBar()->addMenu("&Outil") ;
    qActionExtractVideo = new QAction("&Extraire une vidéo", this) ;
    qMenueTools->addAction(qActionExtractVideo) ;
    qActionExtractVideo->setDisabled(true);

    qVBoxLayout = new QVBoxLayout ;
    qHBoxLayoutVideo = new QHBoxLayout ;

    qLabelTimestampCurrent = new QLabel("--:--") ;
    qLabelTimestampFinish = new QLabel("--:--") ;
    qLabelVideoDisplay = new QLabelVideoDisplay();

    qHBoxLayoutGroupBox = new QHBoxLayout ;
    qGroupBox = new QGroupBox("Modalité") ;
    qRadioButtonTreatment = new QRadioButton("Traitement") ;
    qRadioButtonVisualize = new QRadioButton("Visualiser") ;

    qListWidgetCoordinates = new QListWidget ;
    qVBoxLayoutCoordinates = new QVBoxLayout ;
    qHBoxLayoutVideoControl = new QHBoxLayout ;

    qHBoxLayoutTrajectory = new QHBoxLayout ;
    qCheckBox = new QCheckBox ;
    qLabelTrajectory = new QLabel("Trajectoire") ;

    qHBoxLayoutSlider = new QHBoxLayout ;
    qSlider = new QSlider(Qt::Horizontal) ;
    qSlider->setFixedHeight(120);
    qSlider->setStyleSheet("background-color :white; "
                           "QSlider::groove::Horizontal{visibility:hidden;}");

    qPushButtonFastBackward = new QPushButton("<<") ;
    qPushButtonFastForward = new QPushButton(">>") ;
    qPushButtonPlayPause = new QPushButton("Play") ;
    qPushButtonForward = new QPushButton(">") ;
    qPushButtonBackward = new QPushButton("<") ;
    qPushButtonEnd = new QPushButton(">>|") ;
    qPushButtonStart = new QPushButton("|<<") ;

    // sound signal plot
    qHBoxLayoutSound = new QHBoxLayout();
    qCPsoundSignal = new QCustomPlot();
    /////

    qHBoxLayoutExtraction = new QHBoxLayout ;
    qHBoxLayoutExtraction->setAlignment(Qt::AlignCenter) ;
    qPushButtonStartVideoToExtract = new QPushButton("Début extraction") ;
    qPushButtonEndVideoToExtract = new QPushButton("Fin extraction") ;
    qLabelStartVideoToExtract = new QLabel("--:--") ;
    qLabelEndVideoToExtract = new QLabel("--:--") ;


    qPushButtonLoadCoordinates = new QPushButton("Charger") ;
    qPushButtonSaveCoordinates = new QPushButton("Sauvegarder") ;
    qPushButtonClearList = new QPushButton("Nettoyer") ;

    qHboxLayoutLoadSaveButton = new QHBoxLayout ;

    qWidget = new QWidget ;

    init() ;

    setVisible(true);
}

void MainWindow::init(){
    enableControlButtons(false);

    qHBoxLayoutGroupBox->addWidget(qRadioButtonVisualize);
    qHBoxLayoutGroupBox->addWidget(qRadioButtonTreatment);
    qHBoxLayoutGroupBox->addStretch(1);
    qRadioButtonVisualize->setChecked(true);
    qGroupBox->setLayout(qHBoxLayoutGroupBox);

    qGroupBox->setFixedSize(300, 60);
    qListWidgetCoordinates->setFixedSize(300, 400);

    qPushButtonSaveCoordinates->setEnabled(false);
    qHboxLayoutLoadSaveButton->addWidget(qPushButtonLoadCoordinates);
    qHboxLayoutLoadSaveButton->addWidget(qPushButtonSaveCoordinates);
    qHboxLayoutLoadSaveButton->addWidget(qPushButtonClearList);

    qVBoxLayoutCoordinates->addWidget(qGroupBox);
    qVBoxLayoutCoordinates->addWidget(qListWidgetCoordinates);
    qListWidgetCoordinates->setUniformItemSizes(true);
    qVBoxLayoutCoordinates->addLayout(qHboxLayoutLoadSaveButton);

    qHBoxLayoutVideo->addWidget(qLabelVideoDisplay);
    qHBoxLayoutVideo->addLayout(qVBoxLayoutCoordinates);

    qVBoxLayout->addLayout(qHBoxLayoutVideo);
    qSlider->setEnabled(false);
    qCheckBox->setChecked(false);
    qCheckBox->setEnabled(false);

    qHBoxLayoutSlider->addWidget(qLabelTimestampCurrent);
    qHBoxLayoutSlider->addWidget(qSlider);
    qHBoxLayoutSlider->addWidget(qLabelTimestampFinish);
    qVBoxLayout->addLayout(qHBoxLayoutSlider) ;

    qHBoxLayoutExtraction->addWidget(qPushButtonStartVideoToExtract);
    qHBoxLayoutExtraction->addWidget(qLabelStartVideoToExtract);
    qHBoxLayoutExtraction->addWidget(qLabelEndVideoToExtract);
    qHBoxLayoutExtraction->addWidget(qPushButtonEndVideoToExtract);
    qVBoxLayout->addLayout(qHBoxLayoutExtraction);

    qHBoxLayoutTrajectory->setAlignment(Qt::AlignLeft) ;
    qHBoxLayoutTrajectory->addWidget(qLabelTrajectory);
    qHBoxLayoutTrajectory->addWidget(qCheckBox);
    qVBoxLayout->addLayout(qHBoxLayoutTrajectory);

    // sound signal plot
    qCPsoundSignal->addGraph();
    qCPsoundSignal->setFixedHeight(120);
    qHBoxLayoutSound->addWidget(qCPsoundSignal);
    qVBoxLayout->addLayout(qHBoxLayoutSound);
    ///

    qHBoxLayoutVideoControl->addWidget(qPushButtonStart);
    qHBoxLayoutVideoControl->addWidget(qPushButtonFastBackward);
    qHBoxLayoutVideoControl->addWidget(qPushButtonBackward);
    qHBoxLayoutVideoControl->addWidget(qPushButtonPlayPause);
    qHBoxLayoutVideoControl->addWidget(qPushButtonForward);
    qHBoxLayoutVideoControl->addWidget(qPushButtonFastForward);
    qHBoxLayoutVideoControl->addWidget(qPushButtonEnd);

    qVBoxLayout->addLayout(qHBoxLayoutVideoControl);

    qWidget->setLayout(qVBoxLayout);

    qStatusBar = statusBar() ;
    qStatusBar->showMessage("Application ready to use");

    qLabelVideoDisplay->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    this->setCentralWidget(qWidget);
}

QAction* MainWindow::getQActionShiftMax(){ return qActionShiftMax ;}
QAction* MainWindow::getQActionObjectHistogram(){ return qActionObjectHistogram ;}
QAction* MainWindow::getQActionOpenVideo(){return qActionOpenVideo ;}
QAction* MainWindow::getQActionQuit(){return qActionQuit ;}
QAction* MainWindow::getQActionAlgorithmSubstraction(){return qActionAlgorithmSubstraction ;}
QAction* MainWindow::getQActionAlgorithmColors(){return qActionAlgorithmColors ;}
QAction* MainWindow::getQActionOpenThresholdVideo(){return qActionOpenThresholdVideo ;}
QAction* MainWindow::getQActionOpenColorSelection(){return qActionOpenColorSelection ;}
QAction* MainWindow::getQActionExtractVideo(){return qActionExtractVideo ;}

QPushButton* MainWindow::getQPushButtonPlayPause(){return qPushButtonPlayPause ;}
QPushButton* MainWindow::getQPushButtonFastForward(){return qPushButtonFastForward;}
QPushButton* MainWindow::getQPushButtonFastBackward(){return qPushButtonFastBackward ;}
QPushButton* MainWindow::getQPushButtonForward(){return qPushButtonForward ;}
QPushButton* MainWindow::getQPushButtonBackward(){return qPushButtonBackward ;}
QPushButton* MainWindow::getQPushButtonEnd(){return qPushButtonEnd ;}
QPushButton* MainWindow::getQPushButtonStart(){return qPushButtonStart ;}
QPushButton* MainWindow::getQPushButtonSaveCoordinate(){return qPushButtonSaveCoordinates ;}
QPushButton* MainWindow::getQPushButtonLoadCoordinate(){return qPushButtonLoadCoordinates ;}
QPushButton* MainWindow::getQPushButtonClear(){return qPushButtonClearList ;}
QPushButton* MainWindow::getQPushButtonStartVideoToExtract(){return qPushButtonStartVideoToExtract ;}
QPushButton* MainWindow::getQPushButtonEndVideoToExtract(){return qPushButtonEndVideoToExtract ;}

QRadioButton* MainWindow::getQRadioButtonVisualize(){return qRadioButtonVisualize ;}
QRadioButton* MainWindow::getQRadioButtonTreatment(){return qRadioButtonTreatment ;}

QCheckBox* MainWindow::getQCheckBox(){return qCheckBox ;}
QGroupBox* MainWindow::getQGroupBox(){ return qGroupBox;}

QLabelVideoDisplay *MainWindow::getQLabelVideoDisplay(){return qLabelVideoDisplay ; }
QSlider* MainWindow::getQSlider(){return qSlider ;}
QListWidget* MainWindow::getQListWidget(){return qListWidgetCoordinates;}

QLabel* MainWindow::getQLabelStartVideoToExtract(){return qLabelStartVideoToExtract ;}
QLabel* MainWindow::getQLabelEndVideoToExtract(){return qLabelEndVideoToExtract ;}

void MainWindow::setPlayPauseButton(QString qs){qPushButtonPlayPause->setText(qs);}
void MainWindow::updateSatusBar(QString status){qStatusBar->showMessage(status.toStdString().c_str());}

void MainWindow::enableControlButtons(bool b){
    qPushButtonPlayPause->setEnabled(b);
    qPushButtonFastBackward->setEnabled(b);
    qPushButtonFastForward->setEnabled(b);
    qPushButtonForward->setEnabled(b);
    qPushButtonEnd->setEnabled(b);
    qPushButtonBackward->setEnabled(b);
    qPushButtonStart->setEnabled(b);
    qSlider->setEnabled(b);
    qPushButtonStartVideoToExtract->setEnabled(b);
    qPushButtonEndVideoToExtract->setEnabled(b);
}

void MainWindow::setQLabelCurrentTime(QString q){qLabelTimestampCurrent->setText(q);}
void MainWindow::setQLabelFinishTime(QString q){qLabelTimestampFinish->setText(q);}
void MainWindow::setQLabelStartVideoToExtract(QString q){qLabelStartVideoToExtract->setText(q);}
void MainWindow::setQLabelEndVideoToExtract(QString q){qLabelEndVideoToExtract->setText(q);}

QCustomPlot* MainWindow::getQCPsoundSignal(){return qCPsoundSignal ;}

void MainWindow::displayImageQLabelVideo(QImage img){
    qLabelVideoDisplay->setPixmap(QPixmap::fromImage(img).scaled(qLabelVideoDisplay->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    qLabelVideoDisplay->adjustSize();
}


MainWindow::~MainWindow(){
    delete qHboxLayoutLoadSaveButton;

    delete qPushButtonClearList;
    delete qPushButtonSaveCoordinates;
    delete qPushButtonLoadCoordinates;

    delete qLabelEndVideoToExtract;
    delete qLabelStartVideoToExtract;
    delete qPushButtonEndVideoToExtract;
    delete qPushButtonStartVideoToExtract;
    delete qHBoxLayoutExtraction;

    delete qPushButtonStart;
    delete qPushButtonEnd;
    delete qPushButtonBackward;
    delete qPushButtonForward;
    delete qPushButtonPlayPause;
    delete qPushButtonFastForward;
    delete qPushButtonFastBackward;

    delete qSlider;
    delete qHBoxLayoutSlider;

    delete qLabelTrajectory;
    delete qCheckBox;
    delete qHBoxLayoutTrajectory;

    delete qHBoxLayoutVideoControl;
    delete qVBoxLayoutCoordinates;
    delete qListWidgetCoordinates;

    delete qRadioButtonVisualize;
    delete qRadioButtonTreatment;
    delete qHBoxLayoutGroupBox;
    delete qGroupBox;

    delete qLabelVideoDisplay;
    delete qLabelTimestampFinish;
    delete qLabelTimestampCurrent;

    delete qHBoxLayoutVideo;
    delete qVBoxLayout;

    delete qActionExtractVideo;
    delete qActionOpenColorSelection;
    delete qActionOpenThresholdVideo;
    delete qActionObjectHistogram;
    delete qActionAlgorithmColors;
    delete qActionAlgorithmSubstraction;
    delete qActionShiftMax;
    delete qActionQuit;
    delete qActionOpenVideo;

    delete qCPsoundSignal;
    delete qHBoxLayoutSound;

    delete qMenueTools ;
    delete qMenueAlgorithms ;
    delete qMenuInformation ;
    delete qMenuSetting ;
    delete qMenuFile;

    delete qStatusBar;
    delete qWidget;
}
