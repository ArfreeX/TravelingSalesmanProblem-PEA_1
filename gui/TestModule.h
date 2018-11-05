#ifndef TESTMODULE_H
#define TESTMODULE_H

#include <QDialog>
#include "helpers/FileStream.h"

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

private:
    Ui::TestModule *ui;
    std::vector<std::vector<int>> data;
    helpers::FileStream file;
    unsigned dataSize = 1, dataRange = 1;
    std::string filename = "";
};

#endif // TESTMODULE_H
