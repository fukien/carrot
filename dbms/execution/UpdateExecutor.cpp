#include "UpdateExecutor.h"

UpdateExecutor::UpdateExecutor()
{
    chdNum = 0;
    QueryExecutor::setStatus(0);
    strcpy(QueryExecutor::workDir,"workspace/");
}

UpdateExecutor::~UpdateExecutor()
{
    chdNum = 0;
    QueryExecutor::setStatus(0);
    memset(QueryExecutor::workDir,'\0',strlen(workDir));
}

void UpdateExecutor::setStatus(int a)
{
    QueryExecutor::setStatus(a);
}

int UpdateExecutor::getStatus()
{
    return QueryExecutor::getStatus();
}

void UpdateExecutor::setChdNum(int a)
{
    chdNum = a;
}

int UpdateExecutor::getChdNum()
{
    return chdNum;
}

int UpdateExecutor::execute(query_tree qt)
{
    setStatus(1);
    return getStatus();
}


