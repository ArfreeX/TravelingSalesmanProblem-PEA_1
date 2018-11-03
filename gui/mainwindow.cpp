#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::string filename = QFileDialog::getOpenFileName(this, tr("Open file"), "/home/usr",
                                                    "All files (*.*);;"
                                                    "Text file (*.txt)"
                                                    ).toUtf8().constData();
    file.openFile(filename);
    roadMap = file.readData();
    printMatrix();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->append("Kurwa xD");
}

void MainWindow::printMatrix()
{
    ui->textBrowser->append("Loaded data: ");

    if(roadMap.empty())
    {
        ui->textBrowser->append("No routes found");
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
