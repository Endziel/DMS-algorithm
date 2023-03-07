#ifndef TASK_H
#define TASK_H



#include <vector>

class Task
{
private:
    int arrivalTime;
    int computationTime;
    int deadLine;
    int taskId;
    std::vector<int> myComputationTimes;

public:
    Task(int arrivalTime, int computation, int deadLine, int id);
    int getPeriod() const;
    int getComputationTime() const;
    int getDeadLine() const;
    int getArrivalTime() const;



    void computeTask(int computationFrame);
    const std::vector<int> &getMyComputationTimes() const;
    int getTaskId() const;
};

#endif // TASK_H
