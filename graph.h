#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include "mainlogic.h"
#include "qtablewidget.h"

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    explicit Graph(QTableWidget *tableToPass = nullptr);
    explicit Graph(mainLogic *logicToPass = nullptr);


//    void setData(*vec)
    void DrawGraph();
    ~Graph();



private slots:
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::Graph *ui;
    QTableWidget *table;
    mainLogic *logic;
};

#endif // GRAPH_H
