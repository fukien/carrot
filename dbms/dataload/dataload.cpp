#include <cstdlib>
#include <cstdio>
#include <climits>
#include <iostream>
#include "../storage/DBFile.h"
#include "../storage/FreeBuffer.h"
#include "../storage/PageUtil.h"
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
#include "../index/PrimaryHashIndex.h"
#include "../SPJ/SPJ.h"
#include "../SPJ/Projection.h"
#include "../SPJ/Selection.h"
#include "../SPJ/Join.h"

void fillMetaSegmentDataload(TableMeta* meta,MetaDataSegment *ms)
{
   /*    //NATION
    meta->fieldNum=4 ;
    strcpy(meta->tname,"NATION");
    meta->tid=0;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=meta->fieldNum;
    parts->tid=meta->tid;
     parts->fieldList = new Field[meta->fieldNum];
     int leng[]={4,28,4,152};
     int stype[]={DataTypeFlag::INTEGER,DataTypeFlag::CHAR,
                                DataTypeFlag::INTEGER,DataTypeFlag::VARCHAR};
     char name[meta->fieldNum][MAX_TABLE_NAME_LEN]={"N_NATIONKEY","N_NAME","N_REGIONKEY","N_COMMENT"};
     int offset = 0;
     for(int i=0;i<meta->fieldNum;i++)
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
*/

   /*     //REGION
    meta->fieldNum=3 ;
    strcpy(meta->tname,"REGION");
    meta->tid=1;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=meta->fieldNum;
    parts->tid=meta->tid;
     parts->fieldList = new Field[meta->fieldNum];
     int leng[]={4,28,152};
     int stype[]={DataTypeFlag::INTEGER,DataTypeFlag::CHAR,
                                DataTypeFlag::VARCHAR};
     char name[meta->fieldNum][MAX_TABLE_NAME_LEN]={"R_REGIONKEY", "R_NAME", "R_COMMENT"};
     int offset = 0;
     for(int i=0;i<meta->fieldNum;i++)
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
     */

   /*          //PART
    meta->fieldNum=9 ;
    strcpy(meta->tname,"PART");
    meta->tid=2;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=meta->fieldNum;
    parts->tid=meta->tid;
     parts->fieldList = new Field[meta->fieldNum];
     int leng[]={4,56,28,12,28,4,12,4,24};
     int stype[]={DataTypeFlag::INTEGER, DataTypeFlag::VARCHAR,
                                DataTypeFlag::CHAR, DataTypeFlag::CHAR,
                                DataTypeFlag::VARCHAR, DataTypeFlag::INTEGER,
                                DataTypeFlag::CHAR, DataTypeFlag::FLOAT,
                                DataTypeFlag::VARCHAR};
     char name[meta->fieldNum][MAX_TABLE_NAME_LEN]={"P_PARTKEY", "P_NAME", "P_MFGR", "P_BRAND",
                            "P_TYPE", "P_SIZE", "P_CONTAINER", "P_RETAILPRICE", "P_COMMENT"};
     int offset = 0;
     for(int i=0;i<meta->fieldNum;i++)
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
*/


 //SUPPLIER
    meta->fieldNum= 7;
    strcpy(meta->tname,"SUPPLIER");
    meta->tid=3;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=7;
    parts->tid=3;
     parts->fieldList = new Field[7];
     int leng[]={4,28,40,4,16,4,104};
     int stype[]={DataTypeFlag::INTEGER,DataTypeFlag::CHAR,DataTypeFlag::VARCHAR,
     DataTypeFlag::INTEGER,DataTypeFlag::CHAR,DataTypeFlag::FLOAT,DataTypeFlag::VARCHAR
     };
     char name[7][MAX_TABLE_NAME_LEN]={"S_SUPPKEY","S_NAME","S_ADDRESS","S_NATIONKEY","S_PHONE","S_ACCTBAL","S_COMMENT"};
     int offset = 0;
     for(int i=0;i<7;i++)
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



   /* // PARTSUPP
   meta->fieldNum=5 ;
    strcpy(meta->tname,"PARTSUPP");
    meta->tid=4;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=meta->fieldNum;
    parts->tid=meta->tid;
     parts->fieldList = new Field[meta->fieldNum];
     int leng[]={4,4,4,4,200};
     int stype[]={DataTypeFlag::INTEGER, DataTypeFlag::INTEGER,
                                DataTypeFlag::INTEGER, DataTypeFlag::FLOAT,
                                DataTypeFlag::VARCHAR};
     char name[meta->fieldNum][MAX_TABLE_NAME_LEN]={"PS_PARTKEY", "PS_SUPPKEY", "PS_AVAILQTY", "PS_SUPPLYCOST", "PS_COMMENT"};
     int offset = 0;
     for(int i=0;i<meta->fieldNum;i++)
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
     */

   /*  // CUSTOMER
   meta->fieldNum=8 ;
    strcpy(meta->tname,"CUSTOMER");
    meta->tid=5;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=meta->fieldNum;
    parts->tid=meta->tid;
     parts->fieldList = new Field[meta->fieldNum];
     int leng[]={4, 28, 40, 4, 16, 4, 12, 120};
     int stype[]={DataTypeFlag::INTEGER, DataTypeFlag::VARCHAR,
                                DataTypeFlag::VARCHAR, DataTypeFlag::INTEGER,
                                DataTypeFlag::CHAR, DataTypeFlag::FLOAT,
                                DataTypeFlag::CHAR, DataTypeFlag::VARCHAR};
     char name[meta->fieldNum][MAX_TABLE_NAME_LEN]={"C_CUSTKEY", "C_NAME",
            "C_ADDRESS", "C_NATIONKEY", "C_PHONE", "C_ACCTBAL",
            "C_MKTSEGMENT", "C_COMMENT"};
     int offset = 0;
     for(int i=0;i<meta->fieldNum;i++)
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
        */

    /*     // ORDERS
   meta->fieldNum=9 ;
    strcpy(meta->tname,"ORDERS");
    meta->tid=6;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=meta->fieldNum;
    parts->tid=meta->tid;
     parts->fieldList = new Field[meta->fieldNum];
     int leng[]={4, 4, 4, 4, 16,  16, 16, 4, 80};
     int stype[]={DataTypeFlag::INTEGER, DataTypeFlag::INTEGER,
                                DataTypeFlag::CHAR, DataTypeFlag::FLOAT,
                                DataTypeFlag::DATE, DataTypeFlag::CHAR,
                                DataTypeFlag::CHAR, DataTypeFlag::INTEGER,
                                DataTypeFlag::VARCHAR};
     char name[meta->fieldNum][MAX_TABLE_NAME_LEN]={"O_ORDERKEY", "O_CUSTKEY",
            "O_ORDERSTATUS", "O_TOTALPRICE", "O_ORDERDATE", "O_ORDERPRIORITY",
            "O_CLERK", "O_SHIPPRIORITY", "O_COMMENT"};

     int offset = 0;
     for(int i=0;i<meta->fieldNum;i++)
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
        */

  /*           // LINEITEM
   meta->fieldNum=16;
    strcpy(meta->tname,"LINEITEM");
    meta->tid=7;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=meta->fieldNum;
    parts->tid=meta->tid;
     parts->fieldList = new Field[meta->fieldNum];
     int leng[]={4,4,4,4,     4,4,4,4,    4, 4,16,16,   16,28,12,44};
     int stype[]={DataTypeFlag::INTEGER,DataTypeFlag::INTEGER,DataTypeFlag::INTEGER,DataTypeFlag::INTEGER,
    DataTypeFlag::FLOAT,DataTypeFlag::FLOAT,DataTypeFlag::FLOAT,DataTypeFlag::FLOAT,
    DataTypeFlag::CHAR,DataTypeFlag::CHAR,DataTypeFlag::DATE,DataTypeFlag::DATE,DataTypeFlag::DATE,
    DataTypeFlag::CHAR,DataTypeFlag::CHAR,DataTypeFlag::VARCHAR
     };
     char name[meta->fieldNum][MAX_TABLE_NAME_LEN]={"L_ORDERKEY","L_PARTKEY","L_SUPPKEY","L_LINENUMBER",
     "L_QUANTITY","L_EXTENDEDPRICE","L_DISCOUNT","L_TAX","L_RETURNFLAG",
     "L_LINESTATUS","L_SHIPDATE","L_COMMITDATE","L_RECEIPTDATE","L_SHIPINSTRUCT",
     "L_SHIOMODE","L_COMMENT"
     };

     int offset = 0;
     for(int i=0;i<meta->fieldNum;i++)
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
        */
}

void packageLoad(Tuple* tuple,char** mp,TableMeta* meta) // transfer strings to columns
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

int writedbDataload()
{

       //char s[] = "data/nation.tb";
       //char data[] = "benchmark_data/benchmark_data/nation.tbl";
        //char s[] = "data/region.tb";
        //char data[] = "benchmark_data/benchmark_data/region.tbl";
        //char s[] = "data/part.tb";
       // char data[] = "benchmark_data/benchmark_data/part.tbl";
        char s[] = "data/supplier.tb";
        char data[] = "benchmark_data/benchmark_data/supplier.tbl";
       //char s [] = "data/partsupp.tb";
       //char data[] = "benchmark_data/benchmark_data/partsupp.tbl";
        //char s [] = "data/customer.tb";
        //char data [] = "benchmark_data/benchmark_data/customer.tbl";
        //char s [] = "data/orders.tb";
        //char data [] = "benchmark_data/benchmark_data/orders.tbl";
        //char s [] = "data/lineitem.tb";
        //char data [] = "benchmark_data/benchmark_data/lineitem.tbl";

        Table* table = new Table();
        table->open(s,false);
        TableMeta* meta = table->getTableMeta();
        fillMetaSegmentDataload(meta,0);
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
        int cnt=0;
        while(len>1)
        {
        packageLoad(tuple,ms,meta);
        //unpackage(tuple,meta);
         Addr w = table->insertTuple(tuple);
        m++;
        printf("m=%d\n",m);
        len = 0;
        len = k.findNext(ms);
       // cnt++;
     //   if(cnt>20) break;
        }
        //printf("sss%s",ms[1]);
        k.close();
       printf("built a bpt now!\n");
        getchar();
        //idxseg->createIndex(0,IndexType::bptidx);
        printf("built a bpt finish\n!");
        printf("built another bpt now!\n");
        //Index* hashIndex=idxseg->createIndex(5,IndexType::bptidx);
        printf("built another bpt finish!\n");
        getchar();
        for(int i=0;i<30;i++)
        {
            delete[] ms[i];
        }
        delete[] ms;
        table->releaseEmptyTuple(tuple);
        table->close();
         delete table;
         table = 0;
         //string filename="";
}

int mainDataload()
{
    writedbDataload();
}
