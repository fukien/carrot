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
    int chdNum;
    int condCursor;
    stack<char*> sd;
    stack <int> sdType;
    Condition cond[MAX_CONDITION_LEN];
    bool parse();
    bool decorate(int cursor);
};


#endif // DELETEEXECUTOR_H_INCLUDED
