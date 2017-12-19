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

int SelectExecutor::selectAll()
{
    Table* table = new Table();
    table->open(ctfp.name,false);

    setStatus(1);
    return getStatus();
}


int SelectExecutor::execute(query_tree qt)
{

     if(sw.isAll == 1)//全选
        {
                if(ctfp.currentFp == NULL)
            {
                setStatus(-11);
                return getStatus();
            }
            selectAll();
        }
    return getStatus();
}
