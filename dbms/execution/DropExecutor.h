#ifndef DROPEXECUTOR_H_INCLUDED
#define DROPEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"

class DropExecutor:QueryExecutor
{
public:
    DropExecutor();
    ~DropExecutor();
    int execute(query_tree qt);
    void setStatus(int a);
    int getStatus();
};

#endif // DROPEXECUTOR_H_INCLUDED
