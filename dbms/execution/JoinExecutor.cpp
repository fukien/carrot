#include "JoinExecutor.h"

JoinExecutor::JoinExecutor()
{
    chdNum = 0;
    condCursor = 0;
    tableSeqCursor = 0;
    QueryExecutor::setStatus(0);
    strcpy(QueryExecutor::workDir,"workspace/");
    memset(tableSeq, 0, sizeof(tableSeq));
}

JoinExecutor::~JoinExecutor()
{
    chdNum = 0;
    condCursor = 0;
    tableSeqCursor = 0;
    QueryExecutor::setStatus(0);
    memset(QueryExecutor::workDir,'\0',strlen(workDir));
    memset(tableSeq, 0, sizeof(tableSeq));
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

int JoinExecutor::findChar(char *str, char a)
{
    int seq = 0;
    for(int i = 0; i < strlen(str); i ++ )
        {
            if (str[i] == a)
                {
                    seq = i;
                    break;
                }
        }
        return seq;
}

void JoinExecutor::refactorString(char * tb, char*field, char * str, int seq)
{
     for(int j = 0; j<seq; j++)
            tb[j] = str[j];

    for(int j =seq+1; j<strlen(str); j++)
            field[j-seq-1] = str[j];
}

bool JoinExecutor::decorate(int cursor)
{
   switch(sdType.top())
   {
    case 0:
        {
            cond[cursor].conditionType = 2; // COLUMN

        }
   }
    return true;
}
bool JoinExecutor::parse()
{
    for(int i =0; i < jw.whereCursor; i++)
        {
            if(jw.type[i] == 0)
                {
                    int seq = findChar(jw.where[i], '.');
                    if(seq == 0)
                        {
                            setStatus(-32);
                            return false;
                        }
                    char * tb;
                    char * field;
                    refactorString(tb, field, jw.where[i], seq);
                    strcpy(tableSeq[tableSeqCursor], tb);
                    tableSeqCursor ++;
                    sd.push(field);
                    sdType.push(jw.type[i]);
                }
            else if(jw.type[i] < 4) //NOT SUPPOTED NOW, NO NEED TO MODIFY, NO INFLUENCE At ALL
            {
                sd.push(jw.where[i]);
                sdType.push(jw.type[i]);
            }else if((jw.type[i]>=12)&&(jw.type[i]<=15))
                {
                    switch (jw.type[i])
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
                else if(jw.type[i] == 24)  //SMALLER EQUAL
                    {
                        cond[condCursor].compare = CompareType::LESSEQUAL;
                        bool decCorrect = decorate(condCursor);
                        if(decCorrect == false)
                            {
                                return decCorrect;
                            }
                        condCursor++;
                    }
                    else if(jw.type[i] == 25) // GREATER EQUAL
                        {
                            cond[condCursor].compare = CompareType::GREATEREQUAL;
                            bool decCorrect = decorate(condCursor);
                                if(decCorrect == false)
                                    {
                                        return decCorrect;
                                    }
                                condCursor ++;
                        }else if(jw.type[i] == 9|| jw.type[i] == 10) //AND OR
                        {

                        }
                        else if(jw.type[i] == 11)// WHERE
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

void JoinExecutor::selectAll()
{

}

int JoinExecutor::execute(query_tree qt)
{
    FILE * fp;
    char dir[64] = "workspace/";
    for(int i=0; i < jw.tableCursor;i++)
        {
                strcpy(dir,"workspace/");
                strcat(dir,jw.tableList[i]);
                strcat(dir,".tb");
                fp = fopen(dir,"r");
                if(fp == NULL)
                    {
                        setStatus(-31);
                        return getStatus();
                    }
                fclose(fp);
                fp = NULL;
                strcpy(dir, "\0");
        }

        bool parseCorrect = parse();

        Table ** table = new Table *[jw.tableCursor];
        for(int i = 0; i < jw.tableCursor; i++)
        {
                strcpy(dir,"workspace/");
                strcat(dir,jw.tableList[i]);
                strcat(dir,".tb");
                table[i]->open(dir,false);
                strcpy(dir,"\0");
        }


        Join *jspj = new Join(OperatorType::JOIN,SPJ::TABLEINITIAL,JoinType::NESTLOOPJOIN);




   return getStatus();
}

