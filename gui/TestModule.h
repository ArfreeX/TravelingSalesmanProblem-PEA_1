#ifndef TESTMODULE_H
#define TESTMODULE_H

#include <memory>
#include <QDialog>
#include "helpers/FileStream.h"
#include "helpers/Timer.h"
#include "tsp/GenericTsp.h"

namespace Ui {
class TestModule;
}

class TestModule : public QDialog
{
    Q_OBJECT

public:
    explicit TestModule(QWidget *parent = nullptr);
    ~TestModule();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_3_valueChanged(int value);

    void on_spinBox_3_valueChanged(int arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

private:
    Ui::TestModule *ui;
    std::vector<std::vector<int>> data;
    std::vector<long double> timeResults;
    std::vector<bool> algorithmChecked;
    helpers::Timer timer;
    helpers::FileStream file;
    unsigned dataSize = 1, dataRange = 1, numberOfRepeats = 1;
    std::string filename = "";
    void measureTime();

    void printTimeTable();
};

#endif // TESTMODULE_H
