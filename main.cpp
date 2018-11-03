#include <iostream>
#include <vector>

#include <QApplication>

#include "gui/mainwindow.h"

#include "helpers/Timer.h"
#include "helpers/RandomNumberGenerator.h"
#include "helpers/FileStream.h"

#include "tests/DataGenerator.h"

#include "tsp/BranchAndBound.h"
#include "tsp/BruteForce.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


//#include "mainwindow.h"
//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}
