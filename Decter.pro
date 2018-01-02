QT       += core gui multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Decter


TEMPLATE = app

SOURCES += main.cpp \
    view.cpp \
    model.cpp \
    mainwindow.cpp \
    video.cpp \
    node.cpp \
    trajectory.cpp \
    objectinformation.cpp \
    shiftmaxwindow.cpp \
    objecthisrogramwindow.cpp \
    algocolors.cpp \
    algosubstraction.cpp \
    thresholdvideowindow.cpp \
    extractvideowindow.cpp \
    sound.cpp \
    controller.cpp \
    gestionvideo.cpp \
    QCustomPlot/qcustomplot.cpp

HEADERS += \
    view.h \
    model.h \
    mainwindow.h \
    video.h \
    node.h \
    trajectory.h \
    objectinformation.h \
    shiftmaxwindow.h \
    objecthisrogramwindow.h \
    algocolors.h \
    algosubstraction.h \
    thresholdvideowindow.h \
    extractvideowindow.h \
    sound.h \
    controller.h \
    gestionvideo.h \
    QCustomPlot/qcustomplot.h

#si opencv non trouvé après installation eéxécuter la commande suivante en remplaçant le chemin par le votre : setx -m OPENCV_DIR C:\opencv\build\x86\vc12
INCLUDEPATH += C:\\opencv\\build/include \
INCLUDEPATH += C:\\ffmpeg\\include \
INCLUDEPATH += "C:\\aquila\\include"
CONFIG(debug, debug|release){
LIBS += -LC:\\opencv\\build\\x86\\vc12\\lib -lopencv_calib3d249d -lopencv_contrib249d -lopencv_features2d249d -lopencv_flann249d -lopencv_highgui249d -lopencv_imgproc249d -lopencv_objdetect249d -lopencv_video249d -lopencv_core249d \
        -LC:\\opencv\\build\\x86\\vc12\\bin -lopencv_calib3d249d -lopencv_contrib249d -lopencv_features2d249d -lopencv_flann249d -lopencv_highgui249d -lopencv_imgproc249d -lopencv_objdetect249d -lopencv_video249d -lopencv_core249d \
        -LC:\\ffmpeg\\lib -lavformat -lavcodec -lavutil -lswscale -lswresample -lavfilter \
        -LC:\\ffmpeg\\bin -lavformat -lavcodec -lavutil -lswscale -lswresample -lavfilter
LIBS += "C:\\aquila\\lib\\debug\\aquila.lib"
LIBS += "C:\\aquila\\lib\\debug\\Ooura_fft.lib"
}
CONFIG(release, debug|release){
LIBS += -LC:\\opencv\\build\\x86\\vc12\\lib -lopencv_calib3d249 -lopencv_contrib249 -lopencv_features2d249 -lopencv_flann249 -lopencv_highgui249 -lopencv_imgproc249 -lopencv_objdetect249 -lopencv_video249 -lopencv_core249 \
        -LC:\\opencv\\build\\x86\\vc12\\bin -lopencv_calib3d249 -lopencv_contrib249 -lopencv_features2d249 -lopencv_flann249 -lopencv_highgui249 -lopencv_imgproc249 -lopencv_objdetect249 -lopencv_video249 -lopencv_core249 \
        -LC:\\ffmpeg\\lib -lavformat -lavcodec -lavutil -lswscale -lswresample -lavfilter \
        -LC:\\ffmpeg\\bin -lavformat -lavcodec -lavutil -lswscale -lswresample -lavfilter
LIBS += "C:\\aquila\\lib\\release\\aquila.lib"
LIBS += "C:\\aquila\\lib\\release\\Ooura_fft.lib"
}

