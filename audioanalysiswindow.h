#ifndef AUDIOANALYSISWINDOW_H
#define AUDIOANALYSISWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QString>

class AudioAnalysisWindow : public QDialog{
    private:

        QVBoxLayout* qVBoxLayout ;

        QHBoxLayout* qHBoxLayoutClass ;
        QLabel* qLabelNbClass ;
        QComboBox* qComboBoxClass ;

        QHBoxLayout* qHBoxLayoutClass_0 ;
        QTextEdit* qTextEditClass_0 ;
        QPushButton* qPushButtonClass_0 ;
        QTextEdit* qTextEditResultClass_0 ;

        QHBoxLayout* qHBoxLayoutClass_1 ;
        QTextEdit* qTextEditClass_1 ;
        QPushButton* qPushButtonClass_1 ;
        QTextEdit* qTextEditResultClass_1 ;

        QHBoxLayout* qHBoxLayoutClass_2 ;
        QTextEdit* qTextEditClass_2 ;
        QPushButton* qPushButtonClass_2 ;
        QTextEdit* qTextEditResultClass_2 ;

        QHBoxLayout* qHBoxLayoutClass_3 ;
        QTextEdit* qTextEditClass_3 ;
        QPushButton* qPushButtonClass_3 ;
        QTextEdit* qTextEditResultClass_3 ;

        QHBoxLayout* qHBoxLayoutClass_4 ;
        QTextEdit* qTextEditClass_4 ;
        QPushButton* qPushButtonClass_4 ;
        QTextEdit* qTextEditResultClass_4 ;

        QPushButton* qPushButtonAnalyse ;

        void init() ;
    public:
        AudioAnalysisWindow();
        void enableClass(bool class_1, bool class_2, bool class_3, bool class_4) ;

        QComboBox* getQComboBox() ;
        QPushButton* getQPushButtonClass_0() ;
        QPushButton* getQPushButtonClass_1() ;
        QPushButton* getQPushButtonClass_2() ;
        QPushButton* getQPushButtonClass_3() ;
        QPushButton* getQPushButtonClass_4() ;
        QPushButton* getQPushButtonAnalyse() ;

        QTextEdit* getQTextEditClass_0() ;
        QTextEdit* getQTextEditClass_1() ;
        QTextEdit* getQTextEditClass_2() ;
        QTextEdit* getQTextEditClass_3() ;
        QTextEdit* getQTextEditClass_4() ;

        QTextEdit* getQTextEditResultClass_0() ;
        QTextEdit* getQTextEditResultClass_1() ;
        QTextEdit* getQTextEditResultClass_2() ;
        QTextEdit* getQTextEditResultClass_3() ;
        QTextEdit* getQTextEditResultClass_4() ;

        ~AudioAnalysisWindow() ;
};

#endif // AUDIOANALYSISWINDOW_H
