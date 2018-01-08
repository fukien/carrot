#ifndef SQLEXECUTOR_CPP_INCLUDED
#define SQLEXECUTOR_CPP_INCLUDED
#include "QueryExecutor.h"

QueryExecutor::QueryExecutor(){
    status = 0;
    strcpy(workDir,"workspace/");
}

QueryExecutor::~QueryExecutor(){
    status = 0;
    memset(workDir,'\0',strlen(workDir));
}

int QueryExecutor::execute(){
    return status;
}

void QueryExecutor::setStatus(int a)
{
    status = a;
}

int QueryExecutor::getStatus()
{
    return status;
}

#endif // SQLEXECUTOR_CPP_INCLUDED
