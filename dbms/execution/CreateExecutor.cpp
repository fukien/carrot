#include "CreateExecutor.h"
#include <memory.h>

CreateExecutor::CreateExecutor(){
QueryExecutor::setStatus(0);
strcpy(QueryExecutor::workDir,"workspace/");
}

CreateExecutor::~CreateExecutor(){
QueryExecutor::setStatus(0);
memset(QueryExecutor::workDir,'\0',strlen(workDir));
}

void CreateExecutor::setStatus(int a)
{
    QueryExecutor::setStatus(a);
}

int CreateExecutor::getStatus()
{
    return QueryExecutor::getStatus();
}

int CreateExecutor::execute(query_tree qt){
    int fieldCursor= 0;
    int offset = 0;
    char dir[64];
    strcpy(dir,QueryExecutor::workDir);
    strcat(dir,qt.tableList[qt.fromListNum-1].name);
    strcat(dir,".tb");
    FILE *fp = fopen(dir,"w");
    fclose(fp);
    fp = NULL;
    Table * table = new Table ();
    table-> open(dir,false);
    /*************************************************
    fill meta data
    ************************************************/
    TableMeta * meta = table ->getTableMeta();
    meta->fieldNum = qt.tableList[qt.fromListNum-1].fieldNum;
    strcpy(meta->tname, qt.tableList[qt.fromListNum-1].name);
    meta->tid = currentTableListNum;
    FieldPart * parts = meta -> head;
    if(parts->fieldList != 0 )
    {
        delete parts->fieldList;
    }
    parts->partNum = meta->fieldNum;
    parts->tid = meta->tid;
    parts->fieldList = new Field[meta->fieldNum];
    for(int i = 0;  i < mfListCursor; i++) //处理非char属性的填充
    {
        parts->fieldList[fieldCursor].fid = fieldCursor;
        parts->fieldList[fieldCursor].dataType = qt.tableList[qt.fromListNum-1].mf_list[i].dataTypeFlag;
        parts->fieldList[fieldCursor].flag = 0;
        strcpy(parts->fieldList[fieldCursor].fname,qt.tableList[qt.fromListNum-1].mf_list[i].fieldName);
        parts ->fieldList[fieldCursor].len = getTypeLength(parts->fieldList[fieldCursor].dataType);
        parts->fieldList[fieldCursor].offsetInTuple = offset;
        offset += parts->fieldList[fieldCursor].len;
        fieldCursor ++;
    }
    for(int i = 0; i < mfcListCursor; i ++) //处理char与varchar属性的填充
    {
        parts->fieldList[fieldCursor].fid = fieldCursor;
        parts->fieldList[fieldCursor].dataType = qt.tableList[qt.fromListNum-1].mfc_list[i].dataTypeFlag;
        parts->fieldList[fieldCursor].flag = 0;
        strcpy(parts->fieldList[fieldCursor].fname, qt.tableList[qt.fromListNum-1].mfc_list[i].fieldName);
        if(qt.tableList[qt.fromListNum-1].mfc_list[i].len%4 != 0)
        {
                parts->fieldList[fieldCursor].len = qt.tableList[qt.fromListNum-1].mfc_list[i].len+ 4 - (qt.tableList[qt.fromListNum-1].mfc_list[i].len%4);
        }else
        {
                parts->fieldList[fieldCursor].len = qt.tableList[qt.fromListNum-1].mfc_list[i].len;
        }
        parts->fieldList[fieldCursor].offsetInTuple = offset;
        offset += parts->fieldList[fieldCursor].len;
        fieldCursor++;
    }
    parts->next = 0;
    /*************************************************
    end of fill meta data
    ************************************************/
    table->updateTableMeta();
    table -> close();
    delete table;
    table = 0;
    setStatus(1);
    return getStatus();
}

