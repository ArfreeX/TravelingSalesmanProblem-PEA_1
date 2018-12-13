#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "helpers/FileStream.h"
#include "helpers/Timer.h"
#include "tsp/GenericTsp.h"
#include "tsp/SimulatedAnnealing.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_runButton_clicked();

    void on_bruteForce_clicked();

    void on_dynamicProgramming_clicked();

    void on_boundAndBranchOne_clicked();

    void on_boundAndBranchTwo_clicked();



    void on_testModuleButton_clicked();

    void on_spinBox_3_valueChanged(int arg1);

    void on_boundAndBranchTwo_2_clicked();

    void on_bruteForce_2_clicked();

    void on_dynamicProgramming_2_clicked();

    void on_boundAndBranchOne_2_clicked();

private:
    void printMatrix();

    void printResult(std::string result);

    Ui::MainWindow *ui;
    helpers::FileStream file;
    std::vector<std::vector<int>> roadMap;
    long long int timeLimit;

    enum class Algorithm
    {
        bruteForce,
        dynamicProgramming,
        boundAndBranch,
        simulatedAnnealing,
        tabuSearch,
        unchecked
    };
    std::unique_ptr<tsp::GenericTsp> tspSolver;
    Algorithm selectedAlgorithm = Algorithm::unchecked;
    tsp::SimulatedAnnealing::NeighbourhoodMove neighbourhoodStrategy =
            tsp::SimulatedAnnealing::NeighbourhoodMove::UNCHECKED;
    helpers::Timer timer;
};

#endif // MAINWINDOW_H
