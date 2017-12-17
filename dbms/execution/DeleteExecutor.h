#ifndef DELETEEXECUTOR_H_INCLUDED
#define DELETEEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"

class DeleteExecutor:QueryExecutor
{
public:
    DeleteExecutor();
    ~DeleteExecutor();
    int execute(query_tree qt);
    void setStatus(int a);
    int getStatus();
    void setChdNum(int a);
    int getChdNum();
private:
    int chdNum;
};


#endif // DELETEEXECUTOR_H_INCLUDED
