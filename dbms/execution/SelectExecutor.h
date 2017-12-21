#ifndef SELECTEXECUTOR_H_INCLUDED
#define SELECTEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"
#include <stack>
#include <iostream>

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
    void selectAll();
private:
    int chdNum;
    int condCursor;
    int fieldNum;
    stack<char*> sd;
    stack<int> sdType;
    Condition cond[MAX_CONDITION_LEN];
    bool parse();
    bool decorate(int cursor);
    void parseField();
};

#endif // SELECTEXECUTOR_H_INCLUDED
