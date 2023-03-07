#include "graphtask.h"

QLineSeries *graphTask::getUpperSeries() const
{
    return upperSeries;
}

QLineSeries *graphTask::getLowerSeries() const
{
    return lowerSeries;
}

graphTask::graphTask()
{

}

void graphTask::addToSiriesVisible(int xCoord, int nrOfTask)
{
    *lowerSeries << QPointF(xCoord, nrOfTask - 0.5) << QPointF(xCoord + 1, nrOfTask - 0.5) ;
    *upperSeries << QPointF(xCoord, nrOfTask + 0.5) << QPointF(xCoord + 1, nrOfTask + 0.5) ;



}

void graphTask::addToSeriesInvisible(int xCoord, int nrOfTask)
{
    *lowerSeries << QPointF(xCoord, -1) << QPointF(xCoord + 1, -1) ;
    *upperSeries << QPointF(xCoord, -1) << QPointF(xCoord + 1, -1) ;

}
