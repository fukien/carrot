#ifndef SELECTEXECUTOR_H_INCLUDED
#define SELECTEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"

class SelectExecutor:QueryExecutor
{
public:
    SelectExecutor();
    ~SelectExecutor();
    int execute(query_tree qt);
    void setStatus(int a);
    int getStatus();
    void setChdNum(int a);
    int getChdNum();
    int selectAll();
private:
    int chdNum;
};

#endif // SELECTEXECUTOR_H_INCLUDED
