#include "InsertExecutor.h"
#include <iostream>
using namespace std;
InsertExecutor::InsertExecutor()
{
    chdNum = 0;
    QueryExecutor::setStatus(0);
    strcpy(QueryExecutor::workDir,"workspace/");
}

InsertExecutor::~InsertExecutor()
{
    chdNum = 0;
    QueryExecutor::setStatus(0);
    memset(QueryExecutor::workDir,'\0',strlen(workDir));
}

void InsertExecutor::setChdNum(int a)
{
    chdNum = a;
}

int InsertExecutor::getChdNum()
{
    return chdNum;
}

void InsertExecutor::setStatus(int a)
{
    QueryExecutor::setStatus(a);
}

int InsertExecutor::getStatus()
{
    return QueryExecutor::getStatus();
}

int InsertExecutor::execute(query_tree qt)
{
    int intCursor = 0;
    int floatCursor = 0;
    int stringCursor = 0;
    char dir[64];
    strcpy(dir,QueryExecutor::workDir);
    strcat(dir,ttit.tableName);
    strcat(dir,".tb");
    FILE *f = fopen(dir,"r");
    if(f == NULL)
        {
            setStatus(-18);
            return getStatus();
        }
    Table* table = new Table();
    table->open(dir,false);
    TableMeta * meta = table->getTableMeta();
    Tuple * tuple = table ->buildEmptyTuple();
    FieldPart* fp = meta->head;
    //printf("TABLE FIELD NUMBER %d\n", fp->partNum);
    //printf("TUPLE FIELD NUMBER %d\n", ttit.fieldNum);
    if(fp->partNum!=ttit.fieldNum)
    {
            table -> releaseEmptyTuple(tuple);
            table ->close();
            delete table;
            table = 0;
         setStatus(-16);//元组属性数量和表属性数量不匹配
          return getStatus();
    }
    for(int i = 0; i < fp->partNum; i ++)
        {
            switch(tuple->column[i].field->dataType)
            {
            case DataTypeFlag::INTEGER:
                TableUtil::writeColumn(&ttit.intField[intCursor],&tuple->column[i]);
                intCursor ++;
                break;
            case DataTypeFlag::FLOAT:
                TableUtil::writeColumn(&ttit.floatField[floatCursor],&tuple->column[i]);
                floatCursor++;
                break;
            case DataTypeFlag::CHAR:
            case DataTypeFlag::VARCHAR:
            case DataTypeFlag::DATE:
                //cout<<"元组字符长度"<<strlen(ttit.stringField[stringCursor])<<endl;
                //cout<<"属性字符长度"<<fp->fieldList[i].len<<endl;
                if(strlen(ttit.stringField[stringCursor]) > fp->fieldList[i].len)
                {
                    table -> releaseEmptyTuple(tuple);
                    table ->close();
                    delete table;
                    table = 0;
                    cout<<ttit.stringField[stringCursor]<<endl;
                    setStatus(-17); // 字符串长度不匹配
                    return getStatus();
                }
                DataUtil::str2col(ttit.stringField[stringCursor],tuple->column[i]);
                stringCursor++;
                break;
            default:
                break;
            }
        }
    Addr w = table -> insertTuple(tuple);
    table -> releaseEmptyTuple(tuple);
    table ->close();
    delete table;
    table = 0;
    setStatus(1); //成功创建
    setChdNum(1);// 置插入条数为1
    return getStatus();
}

