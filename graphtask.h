#ifndef GRAPHTASK_H
#define GRAPHTASK_H

#include "qlineseries.h"
#pragma once
#include <QDialog>



class graphTask
{
private:
    QLineSeries *upperSeries = new QLineSeries();
    QLineSeries *lowerSeries = new QLineSeries();


public:
    graphTask();
    void addToSiriesVisible(int xCoord, int nrOfTask);
    void addToSeriesInvisible(int xCoord, int nrOfTask);



    QLineSeries *getUpperSeries() const;
    QLineSeries *getLowerSeries() const;
};

#endif // GRAPHTASK_H
