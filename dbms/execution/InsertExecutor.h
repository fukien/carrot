#ifndef INSERTEXECUTOR_H_INCLUDED
#define INSERTEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"

class InsertExecutor:QueryExecutor
{
public:
    InsertExecutor();
    ~InsertExecutor();
    int execute(query_tree qt);
    void setStatus(int a);
     int getStatus();
     void setChdNum(int a);
     int getChdNum();
private:
    int chdNum;
};

#endif // INSERTEXECUTOR_H_INCLUDED
