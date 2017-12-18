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

int DeleteExecutor::deleteAll(char * dir)
{
    Addr tempTupleAddr = 0u;
    Table* table = new Table();
    table->open(dir,false);
    TableMeta * meta = table->getTableMeta();
    Tuple* tuple = table ->buildEmptyTuple();
    table->findFirstTuple(tuple);
    if(tuple->tupleAddr == tempTupleAddr)
        {
            table->releaseEmptyTuple(tuple);
            table->close();
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

void DeleteExecutor::decorate(Condition * cond, char * dir)
{
    switch(sdType.top())
    {
    case 0:
        cond->conditionType = 2; // COLUMN
        cond->value = sd.top();
        cond->len = sizeof(sd.top());
        Table * table = new Table();
        table->open(dir,false);
        TableMeta * meta = table->getTableMeta();
        //TODO FIND DATA TYPE FOR THE COLUMN IN THE META FROM TABLE

        sd.pop();
        sdType.pop();
        cond->filedName = sd.top();
        sd.pop();
        sdType.pop();
    }
}

void DeleteExecutor::parse(char * dir)
{
        for(int i = 0; i < dw.whereCursor; i++)
        {
            if(dw.type[i] == 0)
                {
                    sd.push(dw.where[i]);
                    sdType.push(dw.type[i]);
                }
                else if(dw.type[1] < 4)
                    {
                        sd.push(dw.where[i]);
                        sdType.push(dw.type[i]);
                    }
                else if(((dw.type[i] >= 12) && (dw.type[i] <=15)) || ((dw.type[i] >=24) && (dw.type[i] <= 25))||dw.type[i] == 9)
                    {
                        Condition *cond;
                        switch(dw.type[i])
                        {
                        case 12:
                            cond->compare = CompareType::LESS;
                            decorate(cond, dir);
                        }
                    }
        }
}

int DeleteExecutor::execute(query_tree qt)
{

    char dir[64];
    strcpy(dir,QueryExecutor::workDir);
    strcat(dir,dw.tableName);
    strcat(dir,".tb");
    FILE *f = fopen(dir,"r");
    if(f == NULL)
        {
            setStatus(-26);  // TABLE NOT FOUND
            return getStatus();
        }

    if(dw.whereCursor == 0)
    {
        return deleteAll(dir); //全删
    }

    parse(dir);
/*
    for(int i = 0; i < dw.whereCursor; i++)
        {
            cout<<dw.where[i]<<endl;
        }
*/

    setStatus(1);
    return getStatus();
}



