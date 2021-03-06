#-------------------------------------------------
#
# Project created by QtCreator 2018-11-03T01:01:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TspGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        gui/mainwindow.cpp \
        helpers/FileStream.cpp \
        tsp/BranchAndBound.cpp \
        tsp/BruteForce.cpp \
        tsp/DynamicProgramming.cpp \
        tsp/GenericTsp.cpp \
    gui/TestModule.cpp \
    tsp/TabuSearch.cpp \
    tsp/SimulatedAnnealing.cpp \
    tsp/TabuList.cpp \
    tsp/GeneticAlgorithm.cpp

HEADERS += \
        gui/mainwindow.h \
        helpers/FileStream.h \
        helpers/RandomNumberGenerator.h \
        helpers/Timer.h \
        tests/DataGenerator.h \
        tsp/BranchAndBound.h \
        tsp/BruteForce.h \
        tsp/DynamicProgramming.h \
        tsp/GenericTsp.h \
    gui/TestModule.h \
    tsp/TabuSearch.h \
    tsp/SimulatedAnnealing.h \
    tsp/TabuList.h \
    tsp/GeneticAlgorithm.h

FORMS += \
        gui/mainwindow.ui \
    gui/TestModule.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
