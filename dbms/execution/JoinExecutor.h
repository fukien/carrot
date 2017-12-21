#ifndef JOINEXECUTOR_H_INCLUDED
#define JOINEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"
#include <stack>
#include <iostream>

class JoinExecutor:QueryExecutor
{
public:
    JoinExecutor();
    ~JoinExecutor();
    int execute(query_tree qt);
    void setStatus(int a);
    int getStatus();
    void setChdNum(int a);
    int getChdNum();

private:
    int chdNum;
    int condCursor;
    stack<char*> sd;
    stack<int> sdType;
    Condition cond[MAX_CONDITION_LEN];
    bool parse();
    bool decorate(int cursor);
};

#endif // JOINEXECUTOR_H_INCLUDED
