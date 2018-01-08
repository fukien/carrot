#include "SelectExecutor.h"
using namespace std;

SelectExecutor::SelectExecutor()
{
     chdNum = 0;
     condCursor = 0;
    QueryExecutor::setStatus(0);
    strcpy(QueryExecutor::workDir,"workspace/");
}

SelectExecutor::~SelectExecutor()
{
    chdNum = 0;
    condCursor = 0;
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

bool SelectExecutor::decorate(int cursor)
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

bool SelectExecutor::parse()
{
    for(int i =0; i < sw.whereCursor; i++)
        {
            if(sw.type[i] == 0)
                {
                    sd.push(sw.where[i]);
                    sdType.push(sw.type[i]);
                }
            else if(sw.type[i] < 4)
            {
                sd.push(sw.where[i]);
                sdType.push(sw.type[i]);
            }else if((sw.type[i]>=12)&&(sw.type[i]<=15))
                {
                    switch (sw.type[i])
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
                else if(sw.type[i] == 24)
                    {
                        cond[condCursor].compare = CompareType::LESSEQUAL;
                        bool decCorrect = decorate(condCursor);
                        if(decCorrect == false)
                            {
                                return decCorrect;
                            }
                        condCursor++;
                    }
                    else if(sw.type[i] == 25)
                        {
                            cond[condCursor].compare = CompareType::GREATEREQUAL;
                            bool decCorrect = decorate(condCursor);
                                if(decCorrect == false)
                                    {
                                        return decCorrect;
                                    }
                                condCursor ++;
                        }else if(sw.type[i] == 9|| sw.type[i] == 10) //AND OR
                        {

                        }
                        else if(sw.type[i] == 11)// WHERE
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

void SelectExecutor::selectAll()
{
    Table* table = new Table();
    table->open(ctfp.name,false);
    TableMeta * meta = table->getTableMeta();
    FieldPart * fp =  meta->head;
    Tuple*tuple = table->buildEmptyTuple();
    string* column = new string[fp->partNum];
    for(int i =0; i < fp->partNum; i ++)
        {
            column[i] = tuple->column[i].field->fname;
        }

    bool parseCorrect = parse();
    if(parseCorrect == false)
        {
            setStatus(-13);
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

    Selection * sspj = new Selection(OperatorType::PROJECTION,SPJ::TABLEINITIAL);
    sspj->initSelection(table,condition, condCursor);

    Projection *proj = new Projection(OperatorType::PROJECTION, SPJ::ITERATORINITIAL);
    proj->initProjection(sspj, column, fp->partNum);

    int cnt = 0;
    SPJItem * item = proj->buildSPJItem();
    proj->getFirst(item);
    for(int i = 0; i < item->fieldNum; i++)
        {
            cout<<"|\t"<<item->fieldName[i]<<"\t|";
        }
    cout<<endl;
    while(item->use!=0)
        {
            char *str = new char[1000];
            for(int i =0; i< item->fieldNum &&  item->use != 0; i ++)
                {
                    DataUtil::toString(str,item->data[i],  item->dataType[i]);
                    printf("|\t%s\t|", str);
                }
                printf("\n");
            cnt ++;
            if(sw.isLimit == 1)
            {
                   if (cnt >= sw.limit)
                    break;
            }
            proj->getNext(item);
            delete str;
        }
    if(cnt == 0)
        {
                setStatus(-12);
        }
        else
        {
            setChdNum(cnt);
            setStatus(1);
        }
        //delete meta;
       //delete tuple;
        //delete fp;
        delete [] condition;
       delete[] column;
       delete proj;
       table->releaseEmptyTuple(tuple);
       table->close();

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
           return getStatus();
        }

    if(ctfp.currentFp == NULL)
        {
            setStatus(-11);
            return getStatus();
        }
    bool parseCorrect = parse();
    if(parseCorrect == false)
        {
            setStatus(-13);
            return getStatus();
        }

    Table* table = new Table();
    table->open(ctfp.name,false);
    TableMeta * meta = table->getTableMeta();
    FieldPart * fp =  meta->head;
    Tuple*tuple = table->buildEmptyTuple();
    string* column = new string[sw.fieldNum];
    for(int i =0; i <sw.fieldNum; i++)
        {
            column[i] = sw.fieldList[i];
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

    Selection * sspj = new Selection(OperatorType::SELECTION,SPJ::TABLEINITIAL);
    sspj->initSelection(table,condition, condCursor);

    Projection *proj = new Projection(OperatorType::PROJECTION, SPJ::ITERATORINITIAL);
    proj->initProjection(sspj, column, sw.fieldNum);

    int cnt = 0;
    SPJItem * item = proj->buildSPJItem();
    proj->getFirst(item);

    for(int i = 0; i< sw.fieldNum; i++)
        {
            cout<<"|\t"<<item->fieldName[i]<<"\t|";
        }

    cout<<endl;

    while(item->use!=0)
        {
            char *str = new char[1000];
            for(int i =0; i< sw.fieldNum &&  item->use != 0; i ++)
                {
                    DataUtil::toString(str,item->data[i],  item->dataType[i]);
                    printf("|\t%s\t|", str);
                }
            printf("\n");
            cnt ++;
            if(sw.isLimit == 1)
            {
                   if (cnt >= sw.limit)
                    break;
            }
            proj->getNext(item);
            delete str;
        }
    if(cnt == 0)
        {
                setStatus(-12);
        }
        else
        {
            setChdNum(cnt);
            setStatus(1);
        }

    delete [] condition;
    delete [] column;
    table->close();
    return getStatus();
}
