#include "DeleteExecutor.h"
#include <iostream>

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

int DeleteExecutor::deleteAll(char * tableName)
{
    Addr tempTupleAddr;
    char dir[64];
    strcpy(dir,QueryExecutor::workDir);
    strcat(dir,tableName);
    strcat(dir,".tb");

    FILE *f = fopen(dir,"r");
    if(f == NULL)
        {
            setStatus(-26);  // TABLE NOT FOUND
            return getStatus();
        }

    Table* table = new Table();
    table->open(dir,false);
    TableMeta * meta = table->getTableMeta();
    Tuple* tuple = table ->buildEmptyTuple();
    table->findFirstTuple(tuple);
    if(tuple->tupleAddr == tempTupleAddr)
        {
            setStatus(-27); // NOT A TUPLE LEFT
            return getStatus();
        }
    while(tuple->tupleAddr != tempTupleAddr)
    {
            tempTupleAddr = tuple->tupleAddr;
            table->deleteTuple(tuple);
            table->findNextTuple(tuple,tuple);
    }
    table->releaseEmptyTuple(tuple);
    table->close();
    delete table;
    setStatus(1); //success
    return getStatus();
}

int DeleteExecutor::execute(query_tree qt)
{
    cout<<dw.tableName<<"\n"<<endl;
    if(dw.whereCursor == 0)
    {
        return deleteAll(dw.tableName); //全删
    }

    for(int i = 0; i < dw.whereCursor; i++)
        {
            cout<<dw.where[i]<<endl;
        }
    setStatus(1);
    return getStatus();
}
