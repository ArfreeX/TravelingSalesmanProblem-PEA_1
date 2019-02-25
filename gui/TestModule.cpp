#include <memory>

#include <QFileDialog>

#include "TestModule.h"
#include "tests/DataGenerator.h"
#include "tsp/BranchAndBound.h"
#include "tsp/BruteForce.h"
#include "tsp/DynamicProgramming.h"

#include "ui_TestModule.h"

TestModule::TestModule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestModule)
{
    ui->setupUi(this);
    algorithmChecked.resize(4);
    std::fill(algorithmChecked.begin(), algorithmChecked.end(), 0);
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

void TestModule::on_horizontalSlider_3_valueChanged(int value)
{
    ui->spinBox_3->setValue(value);
}

void TestModule::on_spinBox_3_valueChanged(int arg1)
{
    numberOfRepeats = static_cast<unsigned>(arg1);
}


void TestModule::measureTime()
{
    data = tests::DataGenerator::drawData(dataSize, dataRange);

    if(algorithmChecked[0])
    {
        for(int i = 0; i < numberOfRepeats; i++)
        {
            tsp::BruteForce algorithm(data);
            timer.start();
            algorithm.computeBestRoute();
            timeResults[0] += timer.ns_to_ms((timer.elapsed()));
        }
        timeResults[0] /= numberOfRepeats;
    }

    if(algorithmChecked[1])
    {
        for(int i = 0; i < numberOfRepeats; i++)
        {
            tsp::DynamicProgramming algorithm(data);
            timer.start();
            algorithm.computeBestRoute();
            timeResults[1] += timer.ns_to_ms((timer.elapsed()));
        }
        timeResults[1] /= numberOfRepeats;
    }

    if(algorithmChecked[2])
    {
        for(int i = 0; i < numberOfRepeats; i++)
        {
            tsp::BranchAndBound algorithm(data);
            timer.start();
            algorithm.computeBestRoute();
            timeResults[2] += timer.elapsed();
        }
        timeResults[2] /= numberOfRepeats;
    }

    if(algorithmChecked[3])
    {
        for(int i = 0; i < numberOfRepeats; i++)
        {
            tsp::BranchAndBound algorithm(data);
            timer.start();
            algorithm.computeBestRoute();
            timeResults[3] += timer.elapsed();
        }
        timeResults[3] /= numberOfRepeats;
    }

}

void TestModule::printTimeTable()
{
    std::string results = "Brute force time: "
                            + std::to_string(timeResults[0]) + " ms"
                            + "\nDynamic programming time: "
                            + std::to_string(timeResults[1]) + " ms"
                            + "\nBranch and Bound time: "
                            + std::to_string(static_cast<double>(timeResults[2]) / 1000000) + " ms"
                            + "\nBranch and Bound time: "
                            + std::to_string(static_cast<double>(timeResults[3]) / 1000000) + " ms";

    ui->textBrowser->clear();
    ui->textBrowser->append(QString::fromStdString(results));
}

void TestModule::on_pushButton_4_clicked()
{
    timeResults.resize(4);
    std::fill(timeResults.begin(), timeResults.end(), 0);

    data = tests::DataGenerator::drawData(dataSize, dataRange);

    measureTime();

    printTimeTable();
}

void TestModule::on_pushButton_3_clicked()
{
    std::string filename = QFileDialog::getOpenFileName(this, tr("Open file"), "/home/arfree/Desktop/PEA_DATA_SETS",
                                                    "All files (*);;"
                                                    "Text file (*.txt)"
                                                    ).toUtf8().constData();
    if(filename.empty())
    {
        return;
    }

    file.write(timeResults, data.size(), filename);
}

void TestModule::on_checkBox_stateChanged(int arg1)
{
    algorithmChecked[0] = arg1;
}

void TestModule::on_checkBox_2_stateChanged(int arg1)
{
    algorithmChecked[1] = arg1;
}

void TestModule::on_checkBox_3_stateChanged(int arg1)
{
    algorithmChecked[2] = arg1;
}

void TestModule::on_checkBox_4_stateChanged(int arg1)
{
    algorithmChecked[3] = arg1;
}
