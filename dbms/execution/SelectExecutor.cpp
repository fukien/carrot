#include "SelectExecutor.h"

SelectExecutor::SelectExecutor()
{
     chdNum = 0;
    QueryExecutor::setStatus(0);
    strcpy(QueryExecutor::workDir,"workspace/");
}

SelectExecutor::~SelectExecutor()
{
    chdNum = 0;
    QueryExecutor::setStatus(0);
    memset(QueryExecutor::workDir,'\0',strlen(workDir));
}

void SelectExecutor::setStatus(int a)
{
    QueryExecutor::setStatus(a);
}

int SelectExecutor::getStatus()
{
    return QueryExecutor::getStatus();
}

void SelectExecutor::setChdNum(int a)
{
    chdNum = a;
}

int SelectExecutor::getChdNum()
{
    return chdNum;
}

int SelectExecutor::execute(query_tree qt)
{
    setStatus(1);
    return getStatus();
}
