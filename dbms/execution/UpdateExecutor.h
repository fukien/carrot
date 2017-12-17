#ifndef UPDATEEXECUTOR_H_INCLUDED
#define UPDATEEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"

class UpdateExecutor:QueryExecutor
{
public:
    UpdateExecutor();
    ~UpdateExecutor();
    int execute(query_tree qt);
    void setStatus(int a);
    int getStatus();
    void setChdNum(int a);
    int getChdNum();
private:
    int chdNum;
};

#endif // UPDATEEXECUTOR_H_INCLUDED
