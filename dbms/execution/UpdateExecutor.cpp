#include "UpdateExecutor.h"

UpdateExecutor::UpdateExecutor()
{
    chdNum = 0;
    condCursor = 0;
    assCursor = 0;
    QueryExecutor::setStatus(0);
    strcpy(QueryExecutor::workDir,"workspace/");
}

UpdateExecutor::~UpdateExecutor()
{
    chdNum = 0;
    condCursor = 0;
    assCursor = 0;
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


void UpdateExecutor::parseAss()
{

}

bool UpdateExecutor::decorate(int cursor)
{
    return true;
}

bool UpdateExecutor::parse()
{
    return true;
}

int UpdateExecutor::execute(query_tree qt)
{

        char dir[64];
        strcpy(dir,QueryExecutor::workDir);
        strcat(dir,dw.tableName);
        strcat(dir,".tb");
        FILE *f = fopen(dir,"r");
        if(f == NULL)
        {
            setStatus(-21);  // TABLE NOT FOUND
            return getStatus();
        }

        setStatus(1);
        return getStatus();
}



