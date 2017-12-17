#include "DeleteExecutor.h"

DeleteExecutor::DeleteExecutor()
{
        chdNum = 0;
        QueryExecutor::setStatus(0);
        strcpy(QueryExecutor::workDir,"workspace/");
}

DeleteExecutor::~DeleteExecutor()
{
    chdNum = 0;
    QueryExecutor::setStatus(0);
    memset(QueryExecutor::workDir,'\0',strlen(workDir));
}
void DeleteExecutor::setStatus(int a)
{
    QueryExecutor::setStatus(a);
}

int DeleteExecutor::getStatus()
{
    return QueryExecutor::getStatus();
}

void DeleteExecutor::setChdNum(int a)
{
    chdNum = a;
}

int DeleteExecutor::getChdNum()
{
    return chdNum;
}

int DeleteExecutor::execute(query_tree qt)
{
    setStatus(1);
    return getStatus();
}
