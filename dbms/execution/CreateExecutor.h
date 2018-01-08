#ifndef CREATEEXECUTOR_H_INCLUDED
#define CREATEEXECUTOR_H_INCLUDED
#include "QueryExecutor.h"

class CreateExecutor: QueryExecutor
{
public:
    CreateExecutor();
    ~CreateExecutor();
    int execute(query_tree qt);
    void setStatus(int a);
     int getStatus();
};

#endif // CREATEEXECUTOR_H_INCLUDED
