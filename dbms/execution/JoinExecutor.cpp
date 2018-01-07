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
    int cursor = 0;
     for(int j = 0; j<seq; j++)
            {
                tb[j] = str[j];
                cursor ++;
            }
            tb[cursor] = '\0';
            cursor = 0;
    for(int j =seq+1; j<strlen(str); j++)
            {
                field[j-seq-1] = str[j];
                cursor++;
            }
            field[cursor] = '\0';
}

bool JoinExecutor::decorate(int cursor)
{
   switch(sdType.top())
   {
        case 0: // ACTUALLY, IN JOIN ONLY COLUMN ARE CONSIDERED. THEREFORE, OTHER DATATYPE WON'T BE EXECUTED
        {
            cond[cursor].conditionType = 2; // COLUMN
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
                cond[cursor].conditionType = 1; //VALUE
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
   }//SWITCH END
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
                    char * tb = new char[100];
                    char * field = new char [100];
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
    char dir[64] = "workspace/";
    int allColumn = 0;
    int columnTableCursor = 0;
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

        Table ** table = new Table *[jw.tableCursor];

        for(int i = 0; i < jw.tableCursor; i++)
        {
                strcpy(dir,"workspace/");
                strcat(dir,jw.tableList[i]);
                strcat(dir,".tb");
                table[i] = new Table();
                table[i]->open(dir,false);
                strcpy(dir,"\0");
        }
        for(int i = 0; i < jw.tableCursor; i ++)
            {
                TableMeta * meta = table[i]->getTableMeta();
                FieldPart * fp =  meta->head;
                allColumn += fp ->partNum;
            }
        string* column = new string[allColumn];
        for(int i = 0; i < jw.tableCursor; i++)
            {

                TableMeta * meta = table[i]->getTableMeta();
                FieldPart * fp =  meta->head;
                Tuple * tuple = table[i]->buildEmptyTuple();
                for(int j = 0; j< fp->partNum;j++)
                    {
                        column[columnTableCursor] = tuple->column[j].field->fname;
                        columnTableCursor++;
                    }
            }

        Join *jspj = new Join(OperatorType::JOIN,SPJ::TABLEINITIAL,JoinType::NESTLOOPJOIN);
        jspj->initJoin(table, jw.tableCursor, 0,0, condition, condCursor);
        SPJItem * item = jspj ->buildSPJItem();
        jspj->getFirst(item);
        int cnt = 0;
        while(item->use != 0)
            {
                cnt++;
                jspj->getNext(item);
            }
        if(cnt == 0)
            {
                setStatus(-33);
            }

        Projection * pspj = new Projection(OperatorType::PROJECTION,SPJ::ITERATORINITIAL);
        pspj->initProjection(jspj, column, allColumn);
        int cnt1 = 0;
        SPJItem * item1 = pspj->buildSPJItem();
        pspj->getFirst(item1);

        for(int i = 0; i< allColumn; i++)
        {
            cout<<"|\t"<<item1->fieldName[i]<<"\t|";
        }
        cout<<endl;
            while(item1->use!=0)
        {
            char *str = new char[1000];
            for(int i =0; i< allColumn &&  item1->use != 0; i ++)
                {
                    DataUtil::toString(str,item1->data[i],  item1->dataType[i]);
                    printf("|\t%s\t|", str);
                }
            printf("\n");
            cnt1 ++;
            if(jw.isLimit == 1)
            {
               if(cnt1 >= jw.limit)
               {
                   break;
               }
            }
            pspj->getNext(item1);
            delete str;
        }
        if(cnt1 == 0)
        {
                setStatus(-33);
        }
        else
        {
            setChdNum(cnt1);
            setStatus(1);
        }
    delete [] condition;
    delete [] column;
    for(int i = 0; i<jw.tableCursor; i++)
        {
            table[i]->close();
        }
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
        if(parseCorrect == false)
            {
                setStatus(-32);
                return getStatus();
            }

        if(jw.isAll)
            {
                selectAll();
                return getStatus();
            }
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

        Table ** table = new Table *[jw.tableCursor];
        for(int i = 0; i < jw.tableCursor; i++)
        {
                strcpy(dir,"workspace/");
                strcat(dir,jw.tableList[i]);
                strcat(dir,".tb");
                table[i] = new Table();
                table[i]->open(dir,false);
                strcpy(dir,"\0");
        }
        Join *jspj = new Join(OperatorType::JOIN,SPJ::TABLEINITIAL,JoinType::NESTLOOPJOIN);
        jspj->initJoin(table, jw.tableCursor, 0,0, condition, condCursor);
        SPJItem * item = jspj ->buildSPJItem();
        jspj->getFirst(item);
        int cnt = 0;
        while(item->use != 0)
            {
                cnt++;
                jspj->getNext(item);
            }
        if(cnt == 0)
            {
                setStatus(-33);
                return getStatus();
            }

        string* column = new string[jw.fieldNum];
        for(int i =0; i <jw.fieldNum; i++)
        {
            column[i] = jw.fieldList[i];
        }
        Projection * pspj = new Projection(OperatorType::PROJECTION,SPJ::ITERATORINITIAL);
        pspj->initProjection(jspj, column, jw.fieldNum);
        int cnt1 = 0;
        SPJItem * item1 = pspj->buildSPJItem();
        pspj->getFirst(item1);
        for(int i = 0; i< jw.fieldNum; i++)
        {
            cout<<"|\t"<<item1->fieldName[i]<<"\t|";
        }
        cout<<endl;
            while(item1->use!=0)
        {
            char *str = new char[1000];
            for(int i =0; i< jw.fieldNum &&  item1->use != 0; i ++)
                {
                    DataUtil::toString(str,item1->data[i],  item1->dataType[i]);
                    printf("|\t%s\t|", str);
                }
            printf("\n");
            cnt1 ++;
            if(jw.isLimit == 1)
                {
                    if(cnt1 >= jw.limit)
                    {
                        break;
                    }
                }
            pspj->getNext(item1);
            delete str;
        }
        if(cnt1 == 0)
        {
                setStatus(-33);
        }
        else
        {
            setChdNum(cnt1);
            setStatus(1);
        }
    delete [] condition;
    delete [] column;
    for(int i = 0; i<jw.tableCursor; i++)
        {
            table[i]->close();
        }
    return getStatus();
}

void JoinExecutor::selectAllM()
{
         char dir[64] = "workspace/";
    int allColumn = 0;
    int columnTableCursor = 0;
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

        Table ** table = new Table *[jw.tableCursor];
        for(int i = 0; i < jw.tableCursor; i++)
        {
                strcpy(dir,"workspace/");
                strcat(dir,jw.tableList[i]);
                strcat(dir,".tb");
                table[i] = new Table();
                table[i]->open(dir,false);
                strcpy(dir,"\0");
        }
        for(int i = 0; i < jw.tableCursor; i ++)
            {
                TableMeta * meta = table[i]->getTableMeta();
                FieldPart * fp =  meta->head;
                allColumn += fp ->partNum;
            }
        string* column = new string[allColumn];
        for(int i = 0; i < jw.tableCursor; i++)
            {

                TableMeta * meta = table[i]->getTableMeta();
                FieldPart * fp =  meta->head;
                Tuple * tuple = table[i]->buildEmptyTuple();
                for(int j = 0; j< fp->partNum;j++)
                    {
                        column[columnTableCursor] = tuple->column[j].field->fname;
                        columnTableCursor++;
                    }
            }

            Table ** tableInitial = new Table*[2];
            tableInitial[0] = table[0];
            tableInitial[1] = table[1];
            Join * jspjInitial = new Join(OperatorType::JOIN, SPJ::TABLEINITIAL, JoinType::NESTLOOPJOIN);
            jspjInitial->initJoin(tableInitial, 2, 0, 0, 0, 0);


            Join * jspjIterator = new Join(OperatorType::JOIN, SPJ::HYBRIDINITIAL, JoinType::NESTLOOPJOIN);

            for(int i =2; i < jw.tableCursor; i ++)
            {
                    if(i == 2)
                        {
                            Table ** tmpTable = new Table * [1];
                            tmpTable[0] = table[i];
                            SPJ ** spj = new SPJ*[1];
                            spj[0] = jspjInitial;
                            jspjIterator->initJoin(tmpTable, 1, spj, 1, 0 ,0);
                        }
                        else
                            {
                                Join * tmp = new Join(OperatorType::JOIN, SPJ::HYBRIDINITIAL, JoinType::NESTLOOPJOIN);
                                Table ** tmpTable = new Table * [1];
                                tmpTable[0] = table[i];
                                SPJ ** spj = new SPJ*[1];
                                spj[0] = jspjIterator;
                                tmp->initJoin(tmpTable, 1, spj, 1, 0 ,0 );
                                jspjIterator = tmp;
                            }
            }


            Selection * sspj = new Selection(OperatorType::SELECTION,SPJ::ITERATORINITIAL);
            sspj->initSelection(jspjIterator, condition, condCursor);

    /*        SPJItem * item = sspj ->buildSPJItem();
             sspj->getFirst(item);
             int cnt = 0;
                while(item->use != 0)
                 {
                    cnt++;
                    sspj->getNext(item);
                  }
                   cout<<"after selection \t"<<cnt<<endl;
*/


            Projection *pspj = new Projection(OperatorType::PROJECTION, SPJ::ITERATORINITIAL);
            pspj->initProjection(sspj, column, allColumn);

            int cnt1 = 0;
            SPJItem * item1 = pspj ->buildSPJItem();
            pspj->getFirst(item1);
            for(int i =0; i < allColumn; i++)
                {
                    cout<<"|\t"<<item1->fieldName[i]<<"\t|";
                }
                 cout<<endl;
                 while(item1->use!=0)
                    {
                    char *str = new char[1000];
                    for(int i =0; i< allColumn &&  item1->use != 0; i ++)
                        {
                            DataUtil::toString(str,item1->data[i],  item1->dataType[i]);
                            printf("|\t%s\t|", str);
                        }
                    printf("\n");
                    cnt1 ++;

                    if(jw.isLimit == 1)
                    {
                       if(cnt1 >= jw.limit)
                       {
                           break;
                       }
                    }
                    //cout << "HIYOU" <<cnt1<< endl;
                    pspj->getNext(item1);

                    delete str;

                }


                if(cnt1 == 0)
                {
                        setStatus(-33);
                }
                else
                {
                    setChdNum(cnt1);
                    setStatus(1);
                }
            delete [] condition;
            delete [] column;
            for(int i = 0; i<jw.tableCursor; i++)
                {
                    table[i]->close();
                }
}

int JoinExecutor::executeM(query_tree qt)
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
        if(parseCorrect == false)
            {
                setStatus(-32);
                return getStatus();
            }
        if(jw.isAll)
            {
                selectAllM();
                return getStatus();
            }

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

            Table ** table = new Table *[jw.tableCursor];
            for(int i = 0; i < jw.tableCursor; i++)
            {
                strcpy(dir,"workspace/");
                strcat(dir,jw.tableList[i]);
                strcat(dir,".tb");
                table[i] = new Table();
                table[i]->open(dir,false);
                strcpy(dir,"\0");
            }



    return getStatus();
}
