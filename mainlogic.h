#ifndef MAINLOGIC_H
#define MAINLOGIC_H
#pragma once
#include "qtablewidget.h"
#include "task.h"
#include "myExceptions.h"



class mainLogic
{
private:
    QTableWidget *table;
    std::vector<Task> tasks;
    std::vector<int> computationPriorityInEveryFrame;
    std::multimap<int,int> deadlinePrioritys;

    int sumOfComputationTimes;


    bool checkCorrectTableInput(int row);
    void initiateTable(int taskMultiplier);
    int checkLongestPeriod();
    int tableIdWithLongestPeriod();
    int sumOfFirstComputationTimes(int howManyFirstRows);
    int interference(int tasks, int time);
    void generateDeadlinePriorityOftable();

    void generateTaskPriority();
    void generateSumOFComputationTimes();
    bool checkIfTasksAreSchedulable();


    void testFun();
public:
    mainLogic(QTableWidget *tableToPass);
    const std::vector<Task> &getTasks() const;
    int getSumOfComputationTimes() const;
    QTableWidget *getTable() const;
    void resizeTasks(int size);
};

#endif // MAINLOGIC_H
