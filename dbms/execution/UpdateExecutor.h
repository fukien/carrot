#ifndef UPDATEEXECUTOR_H_INCLUDED
#define UPDATEEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"
#include <stack>

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
};

#endif // UPDATEEXECUTOR_H_INCLUDED
