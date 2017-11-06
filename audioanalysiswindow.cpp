#include "audioanalysiswindow.h"

AudioAnalysisWindow::AudioAnalysisWindow(){
    qVBoxLayout = new QVBoxLayout ;

    qHBoxLayoutClass = new QHBoxLayout ;
    qLabelNbClass = new QLabel("Veuillez sélectionner le nombre de classes : ") ;
    qComboBoxClass = new QComboBox ;

    qHBoxLayoutClass_0 = new QHBoxLayout ;
    qTextEditClass_0 = new QTextEdit ;
    qPushButtonClass_0 = new QPushButton("...") ;
    qTextEditResultClass_0 = new QTextEdit ;

    qHBoxLayoutClass_1 = new QHBoxLayout ;
    qTextEditClass_1 = new QTextEdit ;
    qPushButtonClass_1 = new QPushButton("...") ;
    qTextEditResultClass_1 = new QTextEdit ;

    qHBoxLayoutClass_2 = new QHBoxLayout ;
    qTextEditClass_2 = new QTextEdit ;
    qPushButtonClass_2 = new QPushButton("...") ;
    qTextEditResultClass_2 = new QTextEdit ;

    qHBoxLayoutClass_3 = new QHBoxLayout ;
    qTextEditClass_3 = new QTextEdit ;
    qPushButtonClass_3 = new QPushButton("...") ;
    qTextEditResultClass_3 = new QTextEdit ;

    qHBoxLayoutClass_4 = new QHBoxLayout ;
    qTextEditClass_4 = new QTextEdit ;
    qPushButtonClass_4 = new QPushButton("...") ;
    qTextEditResultClass_4 = new QTextEdit ;

    qPushButtonAnalyse = new QPushButton("Lancer l'analyse") ;

    init() ;
}

void AudioAnalysisWindow::init(){
    setModal(true);
    qVBoxLayout->setAlignment(Qt::AlignCenter) ;
    for(int i = 1 ; i < 6 ; i++)
        qComboBoxClass->addItem(QString::number(i));

    enableClass(false, false, false, false);

    qHBoxLayoutClass->addWidget(qLabelNbClass);
    qHBoxLayoutClass->addWidget(qComboBoxClass);
    qVBoxLayout->addLayout(qHBoxLayoutClass);

    qTextEditClass_0->setFixedHeight(30);
    qTextEditClass_0->setReadOnly(true);
    qPushButtonClass_0->setFixedHeight(30);
    qTextEditResultClass_0->setFixedSize(70,30);
    qTextEditResultClass_0->setReadOnly(true);
    qHBoxLayoutClass_0->addWidget(qTextEditClass_0);
    qHBoxLayoutClass_0->addWidget(qPushButtonClass_0);
    qHBoxLayoutClass_0->addWidget(qTextEditResultClass_0);
    qVBoxLayout->addLayout(qHBoxLayoutClass_0);

    qTextEditClass_1->setFixedHeight(30);
    qTextEditClass_1->setReadOnly(true);
    qPushButtonClass_1->setFixedHeight(30);
    qTextEditResultClass_1->setFixedSize(70,30);
    qTextEditResultClass_1->setReadOnly(true);
    qHBoxLayoutClass_1->addWidget(qTextEditClass_1);
    qHBoxLayoutClass_1->addWidget(qPushButtonClass_1);
    qHBoxLayoutClass_1->addWidget(qTextEditResultClass_1);
    qVBoxLayout->addLayout(qHBoxLayoutClass_1);

    qTextEditClass_2->setFixedHeight(30);
    qTextEditClass_2->setReadOnly(true);
    qPushButtonClass_2->setFixedHeight(30);
    qTextEditResultClass_2->setFixedSize(70,30);
    qTextEditResultClass_2->setReadOnly(true);
    qHBoxLayoutClass_2->addWidget(qTextEditClass_2);
    qHBoxLayoutClass_2->addWidget(qPushButtonClass_2);
    qHBoxLayoutClass_2->addWidget(qTextEditResultClass_2);
    qVBoxLayout->addLayout(qHBoxLayoutClass_2);

    qTextEditClass_3->setFixedHeight(30);
    qTextEditClass_3->setReadOnly(true);
    qPushButtonClass_3->setFixedHeight(30);
    qTextEditResultClass_3->setFixedSize(70,30);
    qTextEditResultClass_3->setReadOnly(true);
    qHBoxLayoutClass_3->addWidget(qTextEditClass_3);
    qHBoxLayoutClass_3->addWidget(qPushButtonClass_3);
    qHBoxLayoutClass_3->addWidget(qTextEditResultClass_3);
    qVBoxLayout->addLayout(qHBoxLayoutClass_3);

    qTextEditClass_4->setFixedHeight(30);
    qTextEditClass_4->setReadOnly(true);
    qPushButtonClass_4->setFixedHeight(30);
    qTextEditResultClass_4->setFixedSize(70,30);
    qTextEditResultClass_4->setReadOnly(true);
    qHBoxLayoutClass_4->addWidget(qTextEditClass_4);
    qHBoxLayoutClass_4->addWidget(qPushButtonClass_4);
    qHBoxLayoutClass_4->addWidget(qTextEditResultClass_4);
    qVBoxLayout->addLayout(qHBoxLayoutClass_4);

    qVBoxLayout->addWidget(qPushButtonAnalyse);

    setLayout(qVBoxLayout);
}

void AudioAnalysisWindow::enableClass(bool class_1, bool class_2, bool class_3, bool class_4){
    qTextEditClass_1->setEnabled(class_1);
    qPushButtonClass_1->setEnabled(class_1);
    qTextEditResultClass_1->setEnabled(class_1);

    qTextEditClass_2->setEnabled(class_2);
    qPushButtonClass_2->setEnabled(class_2);
    qTextEditResultClass_2->setEnabled(class_2);

    qTextEditClass_3->setEnabled(class_3);
    qPushButtonClass_3->setEnabled(class_3);
    qTextEditResultClass_3->setEnabled(class_3);

    qTextEditClass_4->setEnabled(class_4);
    qPushButtonClass_4->setEnabled(class_4);
    qTextEditResultClass_4->setEnabled(class_4);
}

QComboBox* AudioAnalysisWindow::getQComboBox(){return qComboBoxClass ;}
QPushButton* AudioAnalysisWindow::getQPushButtonClass_0(){return qPushButtonClass_0 ;}
QPushButton* AudioAnalysisWindow::getQPushButtonClass_1(){return qPushButtonClass_1 ;}
QPushButton* AudioAnalysisWindow::getQPushButtonClass_2(){return qPushButtonClass_2 ;}
QPushButton* AudioAnalysisWindow::getQPushButtonClass_3(){return qPushButtonClass_3 ;}
QPushButton* AudioAnalysisWindow::getQPushButtonClass_4(){return qPushButtonClass_4 ;}
QPushButton* AudioAnalysisWindow::getQPushButtonAnalyse(){return qPushButtonAnalyse ;}

QTextEdit* AudioAnalysisWindow::getQTextEditClass_0(){return qTextEditClass_0 ;}
QTextEdit* AudioAnalysisWindow::getQTextEditClass_1(){return qTextEditClass_1 ;}
QTextEdit* AudioAnalysisWindow::getQTextEditClass_2(){return qTextEditClass_2 ;}
QTextEdit* AudioAnalysisWindow::getQTextEditClass_3(){return qTextEditClass_3 ;}
QTextEdit* AudioAnalysisWindow::getQTextEditClass_4(){return qTextEditClass_4 ;}

QTextEdit* AudioAnalysisWindow::getQTextEditResultClass_0(){return qTextEditResultClass_0 ;}
QTextEdit* AudioAnalysisWindow::getQTextEditResultClass_1(){return qTextEditResultClass_1 ;}
QTextEdit* AudioAnalysisWindow::getQTextEditResultClass_2(){return qTextEditResultClass_2 ;}
QTextEdit* AudioAnalysisWindow::getQTextEditResultClass_3(){return qTextEditResultClass_3 ;}
QTextEdit* AudioAnalysisWindow::getQTextEditResultClass_4(){return qTextEditResultClass_4 ;}

AudioAnalysisWindow::~AudioAnalysisWindow(){

    delete qPushButtonAnalyse;

    delete qTextEditResultClass_4;
    delete qPushButtonClass_4;
    delete qTextEditClass_4;
    delete qHBoxLayoutClass_4;

    delete qTextEditResultClass_3;
    delete qPushButtonClass_3;
    delete qTextEditClass_3;
    delete qHBoxLayoutClass_3;

    delete qTextEditResultClass_2;
    delete qPushButtonClass_2;
    delete qTextEditClass_2;
    delete qHBoxLayoutClass_2;

    delete qTextEditResultClass_1;
    delete qPushButtonClass_1;
    delete qTextEditClass_1;
    delete qHBoxLayoutClass_1;

    delete qTextEditResultClass_0;
    delete qPushButtonClass_0;
    delete qTextEditClass_0;
    delete qHBoxLayoutClass_0;

    delete qComboBoxClass;
    delete qLabelNbClass;
    delete qHBoxLayoutClass;

    delete qVBoxLayout;
    /*delete qHBoxLayoutClass ;
    delete qLabelNbClass ;
    delete qComboBoxClass ;

    delete qHBoxLayoutClass_0 ;
    delete qTextEditClass_0 ;
    delete qPushButtonClass_0 ;
    delete qTextEditResultClass_0 ;

    delete qHBoxLayoutClass_1 ;
    delete qTextEditClass_1 ;
    delete qPushButtonClass_1 ;
    delete qTextEditResultClass_1 ;

    delete qHBoxLayoutClass_2 ;
    delete qTextEditClass_2 ;
    delete qPushButtonClass_2 ;
    delete qTextEditResultClass_2 ;

    delete qHBoxLayoutClass_3 ;
    delete qTextEditClass_3 ;
    delete qPushButtonClass_3 ;
    delete qTextEditResultClass_3 ;

    delete qHBoxLayoutClass_4 ;
    delete qTextEditClass_4 ;
    delete qPushButtonClass_4 ;
    delete qTextEditResultClass_4 ;

    delete qPushButtonAnalyse ;*/
}


