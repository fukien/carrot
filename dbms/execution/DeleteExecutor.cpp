#include "DeleteExecutor.h"
#include <iostream>


DeleteExecutor::DeleteExecutor()
{
        chdNum = 0;
        condCursor  = 0;
        QueryExecutor::setStatus(0);
        strcpy(QueryExecutor::workDir,"workspace/");
}

DeleteExecutor::~DeleteExecutor()
{
    chdNum = 0;
    condCursor = 0;
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

bool DeleteExecutor::decorate(int cursor)
{
    switch(sdType.top())
    {
    case 0:
        {
            cond[cursor].conditionType = 2;// COLUMN
            cond[cursor].value = sd.top();
            cond[cursor].len = strlen(sd.top());
            sd.pop();
            sdType.pop();
            cond[cursor].filedName = sd.top();
            sd.pop();
            sdType.pop();
        }
        break;
    case 1:
        {
            cond[cursor].conditionType = 1;//VALUE
            int*temp = new int[1];
            temp[0]=atoi(sd.top());
            cond[cursor].value = temp;
            cond[cursor].DataType = DataTypeFlag::INTEGER;
            sd.pop();
            sdType.pop();
            cond[cursor].filedName = sd.top();
            sd.pop();
            sdType.pop();
        }
        break;
    case 2:
        {
            cond[cursor].conditionType = 1; //VALUE
            float *temp = new float[1];
            temp[0]= atof(sd.top());
            cond[cursor].value = temp;

            cond[cursor].DataType = DataTypeFlag::FLOAT;
            sd.pop();
            sdType.pop();
            cond[cursor].filedName = sd.top();
            sd.pop();
            sdType.pop();
        }
        break;
    case 3:
        {
            cond[cursor].conditionType = 1;//VALUE
            cond[cursor].value =sd.top();
            cond[cursor].DataType = DataTypeFlag::VARCHAR;
            cond[cursor].len= strlen(sd.top());

                /************************
                char*str=new char[1000];
                DataUtil::toString(str, cond[cursor].value, DataTypeFlag::VARCHAR);
                printf("%s\n",str);
            ************************/

            sd.pop();
            sdType.pop();
            cond[cursor].filedName = sd.top();
            sd.pop();
            sdType.pop();
        }
        break;
    }
    return true;
}
bool DeleteExecutor::parse()
{
    for(int i =0; i < dw.whereCursor; i++)
        {
            if(dw.type[i] == 0)
                {
                    sd.push(dw.where[i]);
                    sdType.push(dw.type[i]);
                }
            else if(dw.type[i] < 4)
            {
                sd.push(dw.where[i]);
                sdType.push(dw.type[i]);
            }else if((dw.type[i]>=12)&&(dw.type[i]<=15))
                {
                    switch (dw.type[i])
                    {
                        case 12:
                        {
                            cond[condCursor].compare = CompareType::LESS;
                            bool decCorrect = decorate(condCursor);

                            if(decCorrect == false)
                                {
                                    return decCorrect;
                                }
                            condCursor ++;
                        }
                        break;
                        case 13:
                        {
                            cond[condCursor].compare = CompareType::GREATER;
                            bool decCorrect = decorate(condCursor);
                            if(decCorrect == false)
                                {
                                    return decCorrect;
                                }
                                condCursor++;
                        }
                        break;
                        case 14:
                        {
                            cond[condCursor].compare = CompareType::NOTEQUAL;
                            bool decCorrect = decorate(condCursor);
                            if(decCorrect == false)
                                {
                                    return decCorrect;
                                }
                                condCursor++;
                        }
                        break;
                        case 15:
                        {
                            cond[condCursor].compare = CompareType::EQUAL;
                            bool decCorrect = decorate(condCursor);
                            if(decCorrect == false)
                                {
                                    return decCorrect;
                                }
                                condCursor++;
                        }
                        break;
                        default:
                            break;
                    }// SWITCH END
                }
                else if(dw.type[i] == 24)
                    {
                        cond[condCursor].compare = CompareType::LESSEQUAL;
                        bool decCorrect = decorate(condCursor);
                        if(decCorrect == false)
                            {
                                return decCorrect;
                            }
                        condCursor++;
                    }
                    else if(dw.type[i] == 25)
                        {
                            cond[condCursor].compare = CompareType::GREATEREQUAL;
                            bool decCorrect = decorate(condCursor);
                                if(decCorrect == false)
                                    {
                                        return decCorrect;
                                    }
                                condCursor ++;
                        }else if(dw.type[i] == 9|| dw.type[i] == 10) //AND OR
                        {

                        }
                        else if(dw.type[i] == 11)// WHERE
                            {
                                break;
                            }
        }
        /*****************************************************
                char*str=new char[1000];
                DataUtil::toString(str, cond[condCursor-1].value, DataTypeFlag::VARCHAR);
                printf("%s\n",str);
***********************************************************/
        return true;
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
/*
bool DeleteExecutor::decorate(Condition * cond, char * dir)
{
    int columnCursor;
    bool foundColumn = false;
    switch(sdType.top())
    {
        case 0:
        {
        cond->conditionType = 2; // COLUMN
        cond->value = sd.top();

        Table * table = new Table();
        table->open(dir,false);
        Tuple * tuple = table ->buildEmptyTuple();
        TableMeta * meta = table->getTableMeta();
        FieldPart * fp = meat->head;
        for(int i =0; i< fp->partNum; i ++)
            {
                    int temp = strcmp(tuple->column[i].field->fname, sd.top());//
                    if(temp ==0)//判断列名是否相同
                        {
                            foundColumn = true;
                            columnCursor = i;
                            cond->value = sd.top();
                            break;
                        }
            }
            if(foundColumn == false)
                {
                    setStatus(-28);
                    return false;
                }
              switch(tuple->column[columnCursor].field->dataType)
                {
                    case DataTypeFlag::INTEGER:
                        cond->DataType= DataTypeFlag::INTEGER;
                        break;
                    case DataTypeFlag::FLOAT:
                        cond->DataType = DataTypeFlag::FLOAT;
                        break;
                    case DataTypeFlag::CHAR:
                    case DataTypeFlag::VARCHAR:
                    case DataTypeFlag::DATE:
                        cond->DataType = DataTypeFlag::VARCHAR;
                        cond->len = tuple->column[columnCursor].field->len;
                        break;
                    default:
                        break;
                }
                table->close();
        }
        break;
        case 1:
                {
                    cond->conditionType = 1;
                    cond->value = &sd.top();
                    cond->DataType = DataTypeFlag::INTEGER;
                }
                break;
        case 2:
            {
                cond->conditionType = 2;
                cond->value = &sd.top();
                cond->DataType = DataTypeFlag::FLOAT;
            }
            break;
        case 3:
            {
               cond->conditionType = 3;
               cond->value = sd.top();
               cond->DataType = DataTypeFlag::VARCHAR;
               cond->len = sizeof(sd.top());
            }
            break;
        default:
            break;
    }
        sd.pop();
        sdType.pop();
        cond->filedName = sd.top();
        sd.pop();
        sdType.pop();
    return true;
}

bool DeleteExecutor::parse(char * dir)
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
                        switch(dw.type[i])
                        {
                        case 12: // <
                            {
                            cond[condCursor]->compare = CompareType::LESS;
                            bool dec = decorate(cond[condCursor], dir);
                            if(dec == false)
                                {
                                    return dec;
                                }
                            }
                            break;
                        case 13:// >
                            {
                            cond[condCursor]->compare = CompareType::GREATER;
                            bool dec = decorate(cond[condCursor], dir);
                            if(dec == false)
                                {
                                    return dec;
                                }
                            }
                            break;
                        case 14:// !=
                            {
                            cond[condCursor]->compare = CompareType::NOTEQUAL;
                            bool dec = decorate(cond[condCursor], dir);
                            if(dec == false)
                                {
                                    return dec;
                                }
                            }
                            break;
                        case 15: // =
                            {
                                cond[condCursor]->compare = CompareType::EQUAL;
                                bool dec = decorate(cond[condCursor], dir);
                                if(dec == false)
                                    {
                                        return dec;
                                    }
                            }
                            break;
                        case 25: // >=
                            {
                                cond[condCursor]->compare = CompareType::GREATEREQUAL;
                                bool dec = decorate(cond[condCursor], dir);
                                if(dec == false)
                                    {
                                        return dec;
                                    }
                            }
                            break;
                        case 26:// <=
                            {
                                cond[condCursor]->compare = CompareType::LESSEQUAL;
                                bool dec = decorate(cond[condCursor], dir);
                                if(dec == false)
                                    {
                                        return dec;
                                    }
                            }
                            break;
                        case 9:// AND

                            break;
                        default:
                            break;
                        }
                    }
        }
        return true;
}
*/
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

    bool parseCorrect = parse();
    if(parseCorrect == false)  //解析失败
        {
            setStatus(-28);
            return getStatus();
        }

    Table * table = new Table();
    table->open(dir,false);
    Selection *spj = new Selection(OperatorType::SELECTION,SPJ::TABLEINITIAL);
    Condition * condition = new Condition[condCursor];
    for(int i = 0; i < condCursor; i ++)
        {

            condition[i].compare = cond[i].compare;
            condition[i].conditionType = cond[i].conditionType;
            condition[i].DataType = cond[i].DataType;
            condition[i].filedName = cond[i].filedName;
            condition[i].len = cond[i].len;
            condition[i].value = cond[i].value;
          /**************************
             char*str=new char[1000];
                DataUtil::toString(str, condition[i].value, DataTypeFlag::VARCHAR);
                printf("%s\n",str);
       **************************/
        }

    spj->initSelection(table,condition,condCursor);
    SPJItem * item = spj->buildSPJItem();
    int temp = spj->spjForDelete(item);
    if(temp == 0)
        {
            setStatus(-29);
            return getStatus();
        }else
        {
            setChdNum(temp);
        }
    table->close();
    delete spj;
    delete item;

    /*
    bool dec = parse(dir);
    if(dec != false)
        {
            return getStatus();
        }
    */
/*
    for(int i = 0; i < dw.whereCursor; i++)

            cout<<dw.where[i]<<endl;
        }
*/
    setStatus(1);
    return getStatus();
}

