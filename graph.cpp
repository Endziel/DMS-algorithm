#include "graph.h"
#include "graphtask.h"
#include "ui_graph.h"

#include <iostream>


#include <QtCharts>
#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>


Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{

}

Graph::Graph(QTableWidget *tableToPass):
     ui(new Ui::Graph)
{
    ui->setupUi(this);

    table = tableToPass;
    DrawGraph();


}

Graph::Graph(mainLogic *logicToPass):ui(new Ui::Graph)
{
    ui->setupUi(this);
    this->logic = logicToPass;




    DrawGraph();

}

void Graph::DrawGraph()
{
    QPalette pal = window()->palette();
    pal.setColor(QPalette::Window, QRgb(0x018bba));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    window()->setPalette(pal);
    QPen pen(Qt::transparent);
    pen.setWidth(0);

    QChart *chart = new QChart();

    QString taskName = "Zadanie ";
    int nameIterator = 0;


    QValueAxis *axisX = new QValueAxis;
    axisX->setTickType(QValueAxis::TicksDynamic);
    axisX->setTickAnchor(0.0);
    axisX->setTickInterval(5);
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->setRange(0,logic->getSumOfComputationTimes());
    axisX->setMinorTickCount(4);

    QPen majorGridPen(Qt::GlobalColor::red,3,Qt::SolidLine);
    QPen minorGridPen(Qt::GlobalColor::blue,0.2,Qt::DashLine);

    axisX->setMinorGridLinePen(minorGridPen);
    axisX->setGridLinePen(majorGridPen);
    axisX->setTitleText("Czas");

    QCategoryAxis *axisY = new QCategoryAxis;
    axisY->setRange(0.5,logic->getTable()->rowCount() + 0.5);
    axisY->setTickCount(logic->getTable()->rowCount() + 1);

    axisY->setStartValue(0.5);

    for(int i = 1; i <= logic->getTable()->rowCount(); ++i ){
        axisY->append(QString::number(i),i+0.5);

    }

    axisY->setTitleText("Nr zadania");


    chart->addAxis(axisY, Qt::AlignLeft);

    for(int i = 0; i < logic->getTable()->rowCount(); ++i){
        std::vector<int> computationTimes;
        for(auto task : logic->getTasks()){
            if(task.getTaskId() == i){
                for(auto oneComputationTimeOfOneTask: task.getMyComputationTimes()){
                    computationTimes.push_back(oneComputationTimeOfOneTask);
                }
            }
        }

         graphTask taskToAdd;
                 for(int j = 0; j < logic->getSumOfComputationTimes(); ++j){
                    std::vector<int>::const_iterator ite;
                    ite = std::find(computationTimes.begin(),computationTimes.end(),j);
                    if(ite != computationTimes.end()){
                        taskToAdd.addToSiriesVisible(j,i + 1);
                    }else{
                        taskToAdd.addToSeriesInvisible(j,i + 1);
                    }
                 }
                 QAreaSeries *seriesN = new QAreaSeries(taskToAdd.getLowerSeries(), taskToAdd.getUpperSeries());
                 seriesN->setPen(pen);

                 seriesN->setName(taskName + QString::number(i + 1) );
                 chart->addSeries(seriesN);

                     seriesN->attachAxis(axisX);
                     seriesN->attachAxis(axisY);



    }

    chart->setTitle("Harmonogram z użyciem algorytmu DMS");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout->addWidget(chartView, 1, 0);



}

Graph::~Graph()
{
    delete ui;
}



void Graph::on_spinBox_valueChanged(int arg1)
{
            logic->resizeTasks(arg1);
            DrawGraph();
}

