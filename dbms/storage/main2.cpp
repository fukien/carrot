#include <cstdlib>
#include <cstdio>
#include <climits>
#include "DBFile.h"
#include "FreeBuffer.h"
#include "PageUtil.h"
#include "../util/Thread.h"
#include "../buffer/BufferManager.h"
#include "../buffer/ClockFIFOStrategy.h"
#include "../segment/Segment.h"
#include "../segment/DirectorySegment.h"
#include "../segment/MetaDataSegment.h"
#include "../table/meta.h"
#include "../segment/DataSegment.h"
#include "../table/Table.h"
#include "../test/test.h"
#include "../dataInput/inputer.h"
#include "../util/DataUtil.h"
#include "../segment/IndexSegment.h"
#include "../index/Index.h"
#include "../index/BPTree.h"

void fillMetaSegment2(TableMeta* meta,MetaDataSegment *ms)
{
    meta->fieldNum= 16;
    strcpy(meta->tname,"LINEITEM");
    meta->tid=1;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=16;
    parts->tid=1;
     parts->fieldList = new Field[16];
     int leng[]={4,4,4,4,4,4,4,4,4,16,16,16,28,12,44};
     int stype[]={DataTypeFlag::INTEGER,DataTypeFlag::INTEGER,DataTypeFlag::INTEGER,DataTypeFlag::INTEGER,
    DataTypeFlag::FLOAT,DataTypeFlag::FLOAT,DataTypeFlag::FLOAT,DataTypeFlag::FLOAT,
    DataTypeFlag::CHAR,DataTypeFlag::CHAR,DataTypeFlag::CHAR,DataTypeFlag::CHAR,DataTypeFlag::CHAR,
    DataTypeFlag::CHAR,DataTypeFlag::CHAR,DataTypeFlag::VARCHAR
     };
     char name[16][MAX_TABLE_NAME_LEN]={"L_ORDERKEY","L_PARTKEY","L_SUPPKEY","L_LINENUMBER",
     "L_QUANTITY","L_EXTENDEDPRICE","DISCOUNT","L_TAX","L_RETURNFLAG",
     "L_LINESTATUS","L_SHIPDATE","L_COMMITDATE","L_RECEIPTDATE","L_SHIPINSTRUCT",
     "L_SHIOMODE","L_COMMENT"
     };
     int offset = 0;
     for(int i=0;i<16;i++)
     {
         parts->fieldList[i].fid=i;
         parts->fieldList[i].dataType=stype[i];
         parts->fieldList[i].flag=0;
        strcpy(parts->fieldList[i].fname,name[i]);
         //parts->fieldList[i].fname=;
         parts->fieldList[i].len=leng[i];
         parts->fieldList[i].offsetInTuple=offset;
         offset +=parts->fieldList[i].len;
     }
     parts->next=0;
     if(ms!=0)ms->createOrUpdate();
}

void unpackage2(Tuple* tuple,TableMeta* meta)
{
    char ccc[255];
    FieldPart* fp = meta->head;
    char cstr[8092];
    for(int i=0;i<fp->partNum;i++)
    {
        DataUtil::col2str(tuple->column[i],ccc);
        printf("%s|",ccc);
    }
    printf("\n");
}
void package22(Tuple* tuple,char** mp,TableMeta* meta)
{
    char strings[8092];
    FieldPart* fp = meta->head;
    for(int i=0;i<fp->partNum;i++)
    {
        DataUtil::str2col(mp[i],tuple->column[i]);
        //Column* col = &tuple->column[i];
        //DataUtil::parseFromString(col->data,mp[i],col->field->dataType,col->field->len);
    }
}
int writedb2(char* s,char* data)
{
 //    char s[] = "/F/datasetMaker/benchmark_data/testkc.hdb";
// char data[] = "/F/datasetMaker/benchmark_data/benchmark_data/lineitem.tbl";
 Table* table = new Table();
table->open(s,false);
TableMeta* meta = table->getTableMeta();
fillMetaSegment2(meta,0);
table->updateTableMeta();
IndexSegment* idxseg = table->getIndexSegment();
Tuple* tuple = table->buildEmptyTuple();
//char heiheihei[]="/home/hagen/dataset/benchmark_data/benchmark_data/supplier.tbl";
 char** ms = new char*[30];
 for(int i=0;i<30;i++)
 {
     ms[i]=new char[255];
 }
DataInput k;
k.open(data);
int len = k.findNext(ms);
int m = 0;
getchar();
while(len>1)
{
package22(tuple,ms,meta);
//unpackage(tuple,meta);
 Addr w = table->insertTuple(tuple);
m++;
if(m%100000==0)printf("m=%d\n",m);
//printf("m=%d\n",m);
len = 0;
len = k.findNext(ms);
}
//printf("sss%s",ms[1]);
k.close();
printf("built a bpt now!");
getchar();
idxseg->createIndex(0,IndexType::bptidx);
printf("built a bpt finish!");
printf("built another bpt now!");
idxseg->createIndex(5,IndexType::bptidx);
printf("built another bpt finish!");
getchar();
for(int i=0;i<30;i++)
{
    delete[] ms[i];
}
delete[] ms;

//getchar();
//Addr addr= table->insertTuple(tuple);
printf("\ninsert addr %llx\n",tuple->tupleAddr);
table->releaseEmptyTuple(tuple);
table->close();
 delete table;
 table = 0;
 //string filename="";
 return 0;
}
/*
int main(int argc,char** argv)
{
    if(argc<3)
    {
        printf("need more argument.\n");
        exit(0);
    }
   writedb2(argv[1],argv[2]);
    //readIndex();
}*/
