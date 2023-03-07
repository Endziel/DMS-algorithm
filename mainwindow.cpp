    #include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "graph.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <iostream>
#include "mainlogic.h"
#include "myExceptions.h"
#include "wronginputerror.h"
#include "notschedulableerror.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette pal = window()->palette();
    pal.setColor(QPalette::Window, QRgb(0x018bba));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    window()->setPalette(pal);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    try{
        mainLogic logic(ui->tableWidget);

        Graph graphWindow(&logic);

        graphWindow.setModal(true);
        graphWindow.exec();
    }catch(Err_WrongInputs &e){
        WrongInputError errorscreen;
        errorscreen.setModal(true);
        errorscreen.exec();

    }
    catch(Err_NotSchedulable &e){
        notSchedulableError errorscreen;
        std::cout << "nie mozna ulozyc zadania nr: " << e.TaskId << std::endl;
        errorscreen.setModal(true);
        errorscreen.exec();
    }

}


void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(1);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->tableWidget->insertRow(1);
}




void MainWindow::on_pushButton_2_clicked()
{
    readDataFromFile();

}

void MainWindow::readDataFromFile()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(1);

    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Wybierz plik z harmonogramem"),
                "",
                "Text File(*.txt)"
                );
    QFile file(filename);
    if(!file.exists()){
        qCritical() << "nie znaleziono pliku";
        return;
    }

    if(!file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        qCritical() << file.errorString();
        return;
    }

    QTextStream stream(&file);
    int iterator = 0;
    while(!stream.atEnd()){
        QString line = stream.readLine();
        auto parts = line.split(QLatin1Char('\t'));
        ui->tableWidget->setRowCount(iterator + 1);

        for(int i = 0; i < 3; ++i){
            ui->tableWidget->setItem(iterator,i,new QTableWidgetItem(parts[i]));
        }
        iterator++;
    }
    file.close();

}

