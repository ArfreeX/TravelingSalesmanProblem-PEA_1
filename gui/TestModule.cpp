#include <QFileDialog>
#include "TestModule.h"
#include "tests/DataGenerator.h"
#include "ui_TestModule.h"

TestModule::TestModule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestModule)
{
    ui->setupUi(this);
}

TestModule::~TestModule()
{
    delete ui;
}

void TestModule::on_horizontalSlider_valueChanged(int value)
{
    ui->spinBox->setValue(value);
}

void TestModule::on_spinBox_valueChanged(int arg1)
{
    dataSize = static_cast<unsigned>(arg1);
}

void TestModule::on_horizontalSlider_2_valueChanged(int value)
{
    ui->spinBox_2->setValue(value);
}

void TestModule::on_spinBox_2_valueChanged(int arg1)
{
    dataRange = static_cast<unsigned>(arg1);
}

void TestModule::on_pushButton_clicked()
{
    data = tests::DataGenerator::drawData(dataSize, dataRange);
}

void TestModule::on_pushButton_2_clicked()
{
    std::string filename = QFileDialog::getOpenFileName(this, tr("Open file"), "/home/arfree/Desktop/PEA_DATA_SETS",
                                                    "All files (*);;"
                                                    "Text file (*.txt)"
                                                    ).toUtf8().constData();
    if(filename.empty())
    {
        return;
    }

    file.write(data, filename);
}
