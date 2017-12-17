#include "DropExecutor.h"

DropExecutor::DropExecutor()
{
    QueryExecutor::setStatus(0);
    strcpy(QueryExecutor::workDir,"workspace/");
}

DropExecutor::~DropExecutor()
{
    QueryExecutor::setStatus(0);
    memset(QueryExecutor::workDir,'\0',strlen(workDir));
}

void DropExecutor::setStatus(int a)
{
    QueryExecutor::setStatus(a);
}

int DropExecutor::getStatus()
{
    return QueryExecutor::getStatus();
}

int DropExecutor::execute(query_tree qt)
{
    if(ctfp.currentFp == NULL)
    {
            setStatus(-6);
            return getStatus();
    }
    if(remove(ctfp.name) == 0)
        {
            setStatus(1);
        }
    else
        {
            setStatus(-7);
        }
    return getStatus();
}
