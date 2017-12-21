#include "UpdateExecutor.h"
using namespace std;

UpdateExecutor::UpdateExecutor()
{
    chdNum = 0;
    condCursor = 0;
    assCursor = 0;
    QueryExecutor::setStatus(0);
    strcpy(QueryExecutor::workDir,"workspace/");

    intValue = 0;
    floatValue = 0.0;
    memset(str,'\0', sizeof(str));
    memset(fieldName,'\0',sizeof(fieldName));
    flag = 0;
}

UpdateExecutor::~UpdateExecutor()
{
    chdNum = 0;
    condCursor = 0;
    assCursor = 0;
    QueryExecutor::setStatus(0);
    memset(QueryExecutor::workDir,'\0',strlen(workDir));

    intValue = 0;
    floatValue = 0.0;
    memset(str,'\0', sizeof(str));
    memset(fieldName,'\0',sizeof(fieldName));
    flag = 0;
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
    for(int i = 0; i <=uw.assCursor; i++)
        {
              switch(uw.assType[i])
             {
                 /*
                 case 0: //COLUMN
                     strcpy(fieldName,uw.assWhere[i]);
                    break;
                    */
                 case 1: //INTEGER
                    intValue =  atoi(uw.assWhere[i]);
                    flag = 0; //INTEGER FLAG
                    break;
                 case 2://FLOAT
                    floatValue = atof(uw.assWhere[i]);
                    flag = 1;//FLOAT FLAG
                    break;
                 case 3://STRING
                    strcpy(str, uw.assWhere[i]);
                    flag = 2;//STRING FLAG
                    break;
                 case  26: //ASSIGN
                    strcpy(fieldName,uw.assWhere[i]);
                    break;
                 default:
                    break;
             }
        }
}

bool UpdateExecutor::decorate(int cursor)
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

bool UpdateExecutor::parse()
{
        for(int i =0; i < uw.whereCursor; i++)
        {
            if(uw.type[i] == 0)
                {
                    sd.push(uw.where[i]);
                    sdType.push(uw.type[i]);
                }
            else if(uw.type[i] < 4)
            {
                sd.push(uw.where[i]);
                sdType.push(uw.type[i]);
            }else if((uw.type[i]>=12)&&(uw.type[i]<=15))
                {
                    switch (uw.type[i])
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
                else if(uw.type[i] == 24)
                    {
                        cond[condCursor].compare = CompareType::LESSEQUAL;
                        bool decCorrect = decorate(condCursor);
                        if(decCorrect == false)
                            {
                                return decCorrect;
                            }
                        condCursor++;
                    }
                    else if(uw.type[i] == 25)
                        {
                            cond[condCursor].compare = CompareType::GREATEREQUAL;
                            bool decCorrect = decorate(condCursor);
                                if(decCorrect == false)
                                    {
                                        return decCorrect;
                                    }
                                condCursor ++;
                        }else if(uw.type[i] == 9|| uw.type[i] == 10) //AND OR
                        {

                        }
                        else if(uw.type[i] == 11)// WHERE
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

int UpdateExecutor::execute(query_tree qt)
{
        char dir[64];
        strcpy(dir,uw.tableName);
        FILE *f = fopen(dir,"r");
        if(f == NULL)
        {
            setStatus(-21);  // TABLE NOT FOUND
            return getStatus();
        }
        parseAss();
        bool parseCorrect = parse();
        if(parseCorrect == false)
        {
            setStatus(-22);
            return getStatus();
        }

        Table * table = new Table();
        table->open(dir, false);
        Selection *spj = new Selection(OperatorType::SELECTION, SPJ::TABLEINITIAL);
        Condition * condition = new Condition[condCursor];
        for(int i =0; i < condCursor; i ++)
            {
                condition[i].compare = cond[i].compare;
                condition[i].conditionType = cond[i].conditionType;
                condition[i].DataType = cond[i].DataType;
                condition[i].filedName = cond[i].filedName;
                condition[i].len = cond[i].len;
                condition[i].value = cond[i].value;
            }
        spj->initSelection(table, condition, condCursor);
        SPJItem * item = spj->buildSPJItem();
        int temp = spj->spjForUpdate(item, fieldName, intValue, floatValue, str, flag);
        if(temp == 0)
            {
                setStatus(-23);
                return getStatus();
            }
            else
                {
                    setChdNum(temp);
                }
        table->close();
        delete spj;
        delete item;
        setStatus(1);
        return getStatus();
}



