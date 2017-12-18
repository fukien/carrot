#ifndef DELETEEXECUTOR_H_INCLUDED
#define DELETEEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"
#include <stack>

class DeleteExecutor:QueryExecutor
{
public:
    DeleteExecutor();
    ~DeleteExecutor();
    int execute(query_tree qt);
    int deleteAll(char *tableName);
    void setStatus(int a);
    int getStatus();
    void setChdNum(int a);
    int getChdNum();

private:
    void parse(char * dir);
    void decorate(Condition * cond, char * dir);
    int chdNum;
    stack<char*> sd;
    stack <int> sdType;
};


#endif // DELETEEXECUTOR_H_INCLUDED
