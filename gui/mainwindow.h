#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "helpers/FileStream.h"
#include "helpers/Timer.h"
#include "tsp/GenericTsp.h"
#include "tsp/GeneticAlgorithm.h"
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

    void on_spinBox_4_valueChanged(int arg1);

    void on_spinBox_5_valueChanged(int arg1);

    void on_spinBox_6_valueChanged(int arg1);

    void on_boundAndBranchTwo_3_clicked();

    void on_bruteForce_3_clicked();

    void on_dynamicProgramming_3_clicked();

    void on_bruteForce_4_clicked();

    void on_dynamicProgramming_4_clicked();

private:
    void printMatrix();

    void printResult(std::string result);

    Ui::MainWindow *ui;
    helpers::FileStream file;
    std::vector<std::vector<int>> roadMap;
    std::vector<std::vector<int>> notSorted;
    long long int timeLimit;

    enum class Algorithm
    {
        bruteForce,
        dynamicProgramming,
        boundAndBranch,
        simulatedAnnealing,
        tabuSearch,
        genetic,
        unchecked
    };
    std::unique_ptr<tsp::GenericTsp> tspSolver;
    Algorithm selectedAlgorithm = Algorithm::unchecked;
    tsp::SimulatedAnnealing::NeighbourhoodMove neighbourhoodStrategy =
            tsp::SimulatedAnnealing::NeighbourhoodMove::UNCHECKED;
    tsp::GeneticAlgorithm::MutatingStrategy mutatingStrategy =
            tsp::GeneticAlgorithm::MutatingStrategy::UNCHECKED;
    tsp::GeneticAlgorithm::CrossingStrategy crossingStrategy =
            tsp::GeneticAlgorithm::CrossingStrategy::NONE;
    helpers::Timer timer;

    int geneticPopulation = 0;
    int geneticCrossingFactor = 0;
    int geneticMutationFactor = 0;
};

#endif // MAINWINDOW_H
