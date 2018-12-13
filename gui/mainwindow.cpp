#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "tsp/BranchAndBound.h"
#include "tsp/BruteForce.h"
#include "tsp/DynamicProgramming.h"
#include "tsp/SimulatedAnnealing.h"
#include "tsp/TabuSearch.h"
#include "ui_mainwindow.h"
#include "gui/TestModule.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timeLimit(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::string filename = QFileDialog::getOpenFileName(this, tr("Open file"), "/home/arfree/Desktop/PEA_DATA_SETS",
                                                    "All files (*);;"
                                                    "Text file (*.txt)"
                                                    ).toUtf8().constData();
    if(filename.empty())
    {
        return;
    }

    if(file.openFile(filename))
    {
    roadMap = file.readData();
    }
    printMatrix();
}

void MainWindow::printMatrix()
{
    ui->textBrowser->clear();

    if(roadMap.empty())
    {
        ui->textBrowser->append("No routes found, try to read data again");
        return;
    }

    for(auto & road : roadMap)
    {
        QString oneLine("");
        for(unsigned i = 0; i < road.size(); i++)
        {
            oneLine += QString::number(road[i]) + " ";
        }
        ui->textBrowser->append(oneLine);
    }
}

void MainWindow::printResult(std::string result)
{
    ui->textBrowser_2->clear();

    ui->textBrowser_2->append(QString::fromStdString(result));
}

void MainWindow::on_bruteForce_clicked()
{
    selectedAlgorithm = Algorithm::bruteForce;
}

void MainWindow::on_dynamicProgramming_clicked()
{
    selectedAlgorithm = Algorithm::dynamicProgramming;
}

void MainWindow::on_boundAndBranchOne_clicked()
{
    selectedAlgorithm = Algorithm::boundAndBranch;
}

void MainWindow::on_boundAndBranchTwo_clicked()
{
    selectedAlgorithm = Algorithm::simulatedAnnealing;
}

void MainWindow::on_boundAndBranchTwo_2_clicked()
{
   selectedAlgorithm = Algorithm::tabuSearch;
}

void MainWindow::on_runButton_clicked()
{
    if(roadMap.empty())
    {
        printResult("Please load data first");
        return;
    }

    switch(selectedAlgorithm)
    {
        case Algorithm::bruteForce:
            tspSolver = std::make_unique<tsp::BruteForce>(roadMap);
            break;

        case Algorithm::dynamicProgramming:
            tspSolver = std::make_unique<tsp::DynamicProgramming>(roadMap);
            break;

        case Algorithm::boundAndBranch:
            tspSolver = std::make_unique<tsp::BranchAndBound>(roadMap);
            break;

        case Algorithm::simulatedAnnealing:
        {
            if(neighbourhoodStrategy == tsp::SimulatedAnnealing::NeighbourhoodMove::UNCHECKED)
            {
                tspSolver = nullptr;
            }
            else
            {
                tspSolver = std::make_unique<tsp::SimulatedAnnealing>(roadMap, timeLimit, neighbourhoodStrategy);
            }
        }
            break;

        case Algorithm::tabuSearch:
        {
            if(neighbourhoodStrategy == tsp::SimulatedAnnealing::NeighbourhoodMove::UNCHECKED)
            {
                tspSolver = nullptr;
            }
            else
            {
                tspSolver = std::make_unique<tsp::TabuSearch>(roadMap, timeLimit, neighbourhoodStrategy);
            }
        }
            break;

        case Algorithm::unchecked:
            tspSolver = nullptr;
            break;
    }

    if(!tspSolver)
    {
        printResult("Please choose an algorithm");
        return;
    }

    timer.start();
    tspSolver->computeBestRoute();
    std::string timeResult = "\nExec time: "
            + std::to_string(timer.ns_to_ms((timer.elapsed()))) + " ms";
    printResult(tspSolver->resultToString() + timeResult);
}

void MainWindow::on_testModuleButton_clicked()
{
    TestModule d;
    d.show();
    d.exec();
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    timeLimit  = static_cast<unsigned long long>(arg1);
}

void MainWindow::on_bruteForce_2_clicked()
{
    neighbourhoodStrategy = tsp::SimulatedAnnealing::NeighbourhoodMove::SWAP;
}

void MainWindow::on_dynamicProgramming_2_clicked()
{
    neighbourhoodStrategy = tsp::SimulatedAnnealing::NeighbourhoodMove::INSERT;
}

void MainWindow::on_boundAndBranchOne_2_clicked()
{
    neighbourhoodStrategy = tsp::SimulatedAnnealing::NeighbourhoodMove::INVERT;
}
