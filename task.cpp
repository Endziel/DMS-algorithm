#include "task.h"




int Task::getComputationTime() const
{
    return computationTime;
}

int Task::getDeadLine() const
{
    return deadLine;
}

int Task::getArrivalTime() const
{
    return arrivalTime;
}

void Task::computeTask(int computationFrame)
{
    computationTime--;
    myComputationTimes.push_back(computationFrame);
}

const std::vector<int> &Task::getMyComputationTimes() const
{
    return myComputationTimes;
}

int Task::getTaskId() const
{
    return taskId;
}

Task::Task(int arrivalTime, int computation, int deadLine, int id)
{
    this->deadLine = deadLine;
    this->arrivalTime = arrivalTime;
    this->computationTime = computation;
    this->taskId = id;


}
