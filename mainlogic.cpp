#include "mainlogic.h"
#include <iostream>
#include <ostream>


mainLogic::mainLogic(QTableWidget *tableToPass)
{
    table = tableToPass;
    initiateTable(1);
    generateDeadlinePriorityOftable();
    if(!checkIfTasksAreSchedulable()){
        Err_NotSchedulable error;
        throw error;
    }
    generateSumOFComputationTimes();
    generateTaskPriority();

}

const std::vector<Task> &mainLogic::getTasks() const
{
    return tasks;
}

int mainLogic::getSumOfComputationTimes() const
{
    return sumOfComputationTimes;
}


QTableWidget *mainLogic::getTable() const
{
    return table;
}

void mainLogic::resizeTasks(int size)
{
    initiateTable(size);
    generateSumOFComputationTimes();
    generateTaskPriority();

}



bool mainLogic::checkCorrectTableInput(int row)
{
    if(table->model()->index(row,0).data().toInt() <=0){
        return false;
    }
    if(table->model()->index(row,1).data().toInt() <=0){
        return false;
    }
    if(table->model()->index(row,2).data().toInt() <=0){
        return false;
    }
    return true;

}

void mainLogic::initiateTable(int taskMultiplier)
{
    tasks.clear();
    tasks.reserve(table->rowCount()* taskMultiplier);

    for(int i = 0; i < table->rowCount(); ++i){
        if(checkCorrectTableInput(i) ){
        int howManyTasksWithSameId = ((table->model()->index(tableIdWithLongestPeriod(),0).data().toInt() * taskMultiplier)
                                      + table->model()->index(tableIdWithLongestPeriod(),2).data().toInt())
                / (table->model()->index(i,0).data().toInt());

        for(int j = 1; j <= howManyTasksWithSameId; ++j ){
                int arrivalTime = table->model()->index(i,0).data().toInt() * (j-1) ;
                int computationTime = table->model()->index(i,1).data().toInt() ;
                int deadLine = arrivalTime + table->model()->index(i,2).data().toInt();
                tasks.push_back(Task(arrivalTime,computationTime,deadLine,i));
            }
        }else{
            Err_WrongInputs error;
            throw error;
        }
    }
}

int mainLogic::checkLongestPeriod()
{
    int longestPeriod = table->model()->index(0,0).data().toInt();
    if(table->rowCount()>1){
        for(int i = 1; i < table->rowCount(); ++i){
            if(table->model()->index(i,0).data().toInt() > longestPeriod){
                longestPeriod = table->model()->index(i,0).data().toInt();
            }
        }

    }
    return longestPeriod;
}

int mainLogic::tableIdWithLongestPeriod(){
    int j = 0;
    int longestPeriod = table->model()->index(0,0).data().toInt();
    if(table->rowCount()>1){
        for(int i = 1; i < table->rowCount(); ++i){
            if(table->model()->index(i,0).data().toInt() > longestPeriod){
                longestPeriod = table->model()->index(i,0).data().toInt();
                j = i;
            }
        }

    }
    return j;

}

int mainLogic::sumOfFirstComputationTimes(int howManyFirstRows)
{
    int sum = 0;
    auto itr = deadlinePrioritys.begin();
    for(int i = 1; i <= howManyFirstRows; ++i){
        sum+= itr->first;
        ++itr;
    }
    return sum;

}

int mainLogic::interference(int tasks, int time)
{
    int sum = 0;
    auto itr = deadlinePrioritys.begin();

    for(int j = 1; j <= tasks - 1; ++j){
        sum += ceil((double)time / table->model()->index(itr->second,0).data().toInt()) * table->model()->index(itr->second,1).data().toInt();
        itr++;

    }
    return sum;

}

void mainLogic::generateDeadlinePriorityOftable()
{    

    for(int i = 0; i< table->rowCount(); ++i){
        deadlinePrioritys.insert(std::pair<int, int>(table->model()->index(i,2).data().toInt(), i));
    }
}

void mainLogic::generateTaskPriority()
{
    int currentTime = 0;
    int taskWithLowestDeadline;

    for(int remainingComputation = 0 ; remainingComputation < sumOfComputationTimes; ++remainingComputation){
        int closestDeadline = INT_MAX;
        int i = -1;
        bool anyTaskCompute = false;
        for(auto task: tasks){
            i++;
            if(task.getComputationTime() > 0){
                if(task.getArrivalTime() <= remainingComputation){
                    if(task.getDeadLine() < closestDeadline){
                        closestDeadline = task.getDeadLine();
                        taskWithLowestDeadline = i;
                        anyTaskCompute = true;
                    }
                }
            }
        }
        if(anyTaskCompute){
            tasks[taskWithLowestDeadline].computeTask(remainingComputation);
        }
    }
}

void mainLogic::generateSumOFComputationTimes()
{
    sumOfComputationTimes = 0;
    for(auto task: tasks){
        sumOfComputationTimes += task.getComputationTime();
    }

}

bool mainLogic::checkIfTasksAreSchedulable()
{
    int iterator = 1;
    for(auto& [key, value]: deadlinePrioritys){
        double time = sumOfFirstComputationTimes(iterator);
        bool cont = true;
        while(cont){
            if( ((double)interference(iterator,time)/time) + ((double)table->model()->index(value,1).data().toInt() /time) <= 1  ){
                cont = false;
                continue;
            }else{
                time = interference(iterator,time) + table->model()->index(value ,1).data().toInt();
            }
            if(time > table->model()->index(value,2).data().toInt() ){
                Err_NotSchedulable error;
                error.TaskId = value  +1 ;
                throw error;
            }
        }
        iterator++;
    }
    return true;
}

void mainLogic::testFun()
{
    for(auto task : tasks){
        std::cout << task.getArrivalTime() << " "<<task.getDeadLine() << std::endl;
    }
}
