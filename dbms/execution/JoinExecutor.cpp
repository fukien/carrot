#include "JoinExecutor.h"

JoinExecutor::JoinExecutor()
{
    chdNum = 0;
    condCursor = 0;
    QueryExecutor::setStatus(0);
    strcpy(QueryExecutor::workDir,"workspace/");
}

JoinExecutor::~JoinExecutor()
{
    chdNum = 0;
    condCursor = 0;
    QueryExecutor::setStatus(0);
    memset(QueryExecutor::workDir,'\0',strlen(workDir));
}

void JoinExecutor::setStatus(int a)
{
    QueryExecutor::setStatus(a);
}

int JoinExecutor::getStatus()
{
    QueryExecutor::getStatus();
}

void JoinExecutor::setChdNum(int a)
{
    chdNum = a;
}

int JoinExecutor::getChdNum()
{
    return chdNum;
}

int JoinExecutor::execute(query_tree qt)
{

   return getStatus();
}

