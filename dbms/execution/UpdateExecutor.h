#ifndef UPDATEEXECUTOR_H_INCLUDED
#define UPDATEEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"
#include <stack>
#include<iostream>



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
    int condCursor;
    int assCursor;
    stack<char*> sd;
    stack<int> sdType;
    Condition cond[MAX_CONDITION_LEN];
    bool parse();
    bool decorate(int cursor);
    void parseAss();
    char str[MAX_FIELD_NAME_LEN];
    char fieldName[MAX_FIELD_NAME_LEN];
    int intValue;
    float floatValue;
    int flag;
};

#endif // UPDATEEXECUTOR_H_INCLUDED
