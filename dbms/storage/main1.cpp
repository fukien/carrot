#include <cstdlib>
#include <cstdio>
#include <climits>
#include <iostream>
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
#include "../index/PrimaryHashIndex.h"
#include "../SPJ/SPJ.h"
#include "../SPJ/Projection.h"
#include "../SPJ/Selection.h"
#include "../SPJ/Join.h"
using namespace std;

void fillTuple(Tuple* tuple)
{
    int suppkey = 1;
    char s_name[]="Supplier#000000001";
    char s_address[] = " N kD4on9OM Ipw3,gf0JBoQDd7tgrzrddZ";
    int s_nationkey = 17;
    char s_phone[] = "27-918-335-1736";
    float s_acctbal = 5755.94;
    char s_comment[] = "each slyly above the careful";
    TableUtil::writeColumn(&suppkey,&tuple->column[0]);
    TableUtil::writeColumn(s_name,&tuple->column[1]);
    TableUtil::writeColumn(s_address,&tuple->column[2]);
    TableUtil::writeColumn(&s_nationkey,&tuple->column[3]);
    TableUtil::writeColumn(s_phone,&tuple->column[4]);
    TableUtil::writeColumn(&s_acctbal,&tuple->column[5]);
    TableUtil::writeColumn(s_comment,&tuple->column[6]);
}
void fillMetaSegment(TableMeta* meta,MetaDataSegment *ms)
{

    meta->fieldNum= 7;
    strcpy(meta->tname,"SUPPLIER");
    meta->tid=1;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=7;
    parts->tid=1;
     parts->fieldList = new Field[7];
     int leng[]={4,25,40,4,15,4,101};
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


    /*
    meta->fieldNum= 4;
    strcpy(meta->tname,"NATION");
    meta->tid=1;
    FieldPart* parts = meta->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }currentTableListNum
    parts->partNum=4;
    parts->tid=1;
     parts->fieldList = new Field[4];
     int leng[]={4,25,4,152};
     int stype[]={DataTypeFlag::INTEGER,DataTypeFlag::CHAR,DataTypeFlag::INTEGER,
     DataTypeFlag::VARCHAR};
     char name[4][MAX_TABLE_NAME_LEN]={"N_NATIONKEY","N_NAME","N_REGIONKEY","N_COMMENT"
     };
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
        */
}
void unpackage(Tuple* tuple, TableMeta* meta)   // transfer columns to strings
{
    char ccc[255];
    FieldPart* fp = meta->head;
    char cstr[8092];
    for(int i=0; i<fp->partNum; i++)
    {
        DataUtil::col2str(tuple->column[i],ccc);
        printf("%s|",ccc);
    }
    printf("\n");
}
void package2(Tuple* tuple,char** mp,TableMeta* meta) // transfer strings to columns
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
/*
int readIndex()
{
     char s[] = "../../data/testk.hdb";
 //char data[] = "/home/hagen/dataset/benchmark_data/benchmark_data/supplier.tbl";
 Table* table = new Table();
table->open(s,false);
TableMeta* meta = table->getTableMeta();
//fillMetaSegment(meta,0);
//table->updateTableMeta();
IndexSegment* idxseg = table->getIndexSegment();
Tuple* tuple = table->buildEmptyTuple();
printf("loading bpt tree!\n");
Index* idx = idxseg->findIndex(0,IndexType::bptidx);
int id = 3120;
int id2 = 4223;
BPTree* tree = dynamic_cast<BPTree*>(idx);
IndexIterator* iter = tree->findByRange(&id,&id2);
IndexItem* item = idx->buildItem();
iter->findFirst(item);
if(item->addr!=0)
{
    Addr old = item->addr;
    table->findTupleAtPosition(tuple,item->addr);
    unpackage(tuple,meta);
    iter->findNext(item);
    while(item->addr!=old)
    {
                old = item->addr;
        table->findTupleAtPosition(tuple,item->addr);
        unpackage(tuple,meta);
        iter->findNext(item);
    }
}
idx->releaseIndexItem(item);
idx->destoryIterator(iter);
iter = 0;
if(idx!=0)
{
    printf("loaded!\n");
}
getchar();
idx = idxseg->findIndex(5,IndexType::bptidx);
if(idx!=0)
{
    printf("loaded!\n");
}
 tree = dynamic_cast<BPTree*>(idx);
float id11= 340.0;
float id22 = 400.0;
iter = tree->findByRange(&id11,&id22);
item = idx->buildItem();
iter->findFirst(item);
if(item->addr!=0)
{
    Addr old = item->addr;
    table->findTupleAtPosition(tuple,item->addr);
    unpackage(tuple,meta);
    iter->findNext(item);
    while(item->addr!=old)
    {
                old = item->addr;
        table->findTupleAtPosition(tuple,item->addr);
        unpackage(tuple,meta);
        iter->findNext(item);
    }
}else
{
    printf("\n not found!\n");
}
idx->releaseIndexItem(item);
idx->destoryIterator(iter);
iter = 0;
//Addr addr= table->insertTuple(tuple);
printf("\ninsert addr %llx\n",tuple->tupleAddr);
table->releaseEmptyTuple(tuple);

table->close();
 delete table;
 table = 0;
 //string filename="";
}*/
int readdb()
{
    char s[] = "data/nation.db";
    //char data[] = "/home/hagen/dataset/benchmark_data/benchmark_data/supplier.tbl";
    Table* table = new Table();
    table->open(s,false);
    TableMeta* meta = table->getTableMeta();
    //fillMetaSegment(meta,0);
    //table->updateTableMeta();
    //IndexSegment* idxseg = table->getIndexSegment();
    Tuple* tuple = table->buildEmptyTuple();
    vector<string> mp;
    getchar();
    table->findFirstTuple(tuple);
    unpackage(tuple,meta);
    while(tuple->tupleAddr>0)
    {
        Addr old = tuple->tupleAddr;
        table->findNextTuple(tuple,tuple);
            if(tuple->tupleAddr==old)
        {
            break;
        }
        unpackage(tuple,meta);

    }
    /*printf("loading bpt tree!\n");
    Index* idx = idxseg->findIndex(0,IndexType::bptidx);
    if(idx!=0)
    {
        printf("loaded!\n");
    }*/
    getchar();
    Addr addr= table->insertTuple(tuple);
    printf("\ninsert addr %llx\n",tuple->tupleAddr);
    table->releaseEmptyTuple(tuple);

    table->close();
    delete table;
    table = 0;
     //string filename="";
}

int writedb()
{
        char s[] = "data/supplier.db";
        char data[] = "benchmark_data/benchmark_data/supplier.tbl";
        //char s[] = "data/nation.db";
        //char data[] = "benchmark_data/benchmark_data/nation.tbl";
        Table* table = new Table();
        table->open(s,false);
        TableMeta* meta = table->getTableMeta();
        fillMetaSegment(meta,0);
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
        package2(tuple,ms,meta);
        //unpackage(tuple,meta);
         Addr w = table->insertTuple(tuple);
        //m++;
        //printf("m=%d\n",m);
        len = 0;
        len = k.findNext(ms);
        cnt++;
        if(cnt>20) break;
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

        //getchar();
        //Addr addr= table->insertTuple(tuple);
       // printf("\ninsert addr %llx\n",tuple->tupleAddr);
        table->releaseEmptyTuple(tuple);
        table->close();
         delete table;
         table = 0;
         //string filename="";
}

int main()
{
    writedb();
}

int mainSMR()
{
   //readdb();
  // writedb();
   //printf("begin test");
   // return 0;
   Table**tableList=new Table*[2];
   SPJ**spjList=new SPJ*[2];
   tableList[0]=new Table();
   tableList[1]=new Table();
   char s[] = "data/supplier.db";
   tableList[0]->open(s,false);
   char s1[]="data/nation.db";
   tableList[1]->open(s1,false);
   Projection*pspj1=new Projection(OperatorType::PROJECTION,SPJ::TABLEINITIAL);
   string columnName1[2]={"S_SUPPKEY","S_NATIONKEY"};
   pspj1->initProjection(tableList[0],columnName1,2);
   Projection*pspj2=new Projection(OperatorType::PROJECTION,SPJ::TABLEINITIAL);
   string columnName2[2]={"N_NATIONKEY","N_NAME"};
   pspj2->initProjection(tableList[1],columnName2,2);
   /*SPJItem* pitem=pspj2->buildSPJItem();
   int cnt=0;
   pspj2->getFirst(pitem);
   while(pitem->use!=0){
        char*str=new char[1000];
        //printf("fieldNum:: %d\n",item->fieldNum);
        for(int i=0;i<pitem->fieldNum&&pitem->use!=0;i++){
            DataUtil::toString(str,pitem->data[i],pitem->dataType[i]);
           // printf("%s\n",str);
        }
        cnt++;
        pspj2->getNext(pitem);
        printf("###################\n");
        //break;
        //if(cnt>=20000)break;
    }*/
   spjList[0]=pspj1;
   spjList[1]=pspj2;
   //TableMeta* meta = tableList[0]->getTableMeta();
   //printf("meta fieldNum:%d\n",meta->fieldNum);
   Condition * condition=new Condition[1];
   //Selection*spj=new Selection(OperatorType::SELECTION,SPJ::ITERATORINITIAL);
   condition[0].conditionType=2;
   condition[0].filedName="S_NATIONKEY";
   condition[0].compare=CompareType::LESSEQUAL;
   condition[0].DataType=DataTypeFlag::INTEGER;
   //int ss=9990;
   char ss[] = "N_NATIONKEY";
   //printf("ss len: %d\n",sizeof(ss));
   condition[0].value=ss;
   condition[0].len=sizeof(ss);
    /* condition[1].conditionType=1;
   condition[1].filedName="S_SUPPKEY";
   condition[1].compare=CompareType::LESS;
   condition[1].DataType=DataTypeFlag::INTEGER;
   int  skey=20;
   condition[1].value=&skey;*/

   // Projection*pspj=new Projection(OperatorType::PROJECTION,SPJ::TABLEINITIAL);
    //string columns[2]={"S_SUPPKEY","S_ADDRESS"};
    //pspj->initProjection(table,columns,2);
    //spj->initSelection(pspj,condition,1);
    Join*spj=new Join(OperatorType::JOIN,SPJ::TABLEINITIAL,JoinType::NESTLOOPJOIN);
    //spj->initJoin(tableList,2,0,0,condition,1);
    spj->initJoin(tableList,2,0,0,0,0);
    SPJItem*item=spj->buildSPJItem();
    spj->getFirst(item);
    int cnt=0;
    while(item->use!=0){
        char*str=new char[1000];
        //printf("fieldNum:: %d\n",item->fieldNum);
        for(int i=0;i<item->fieldNum&&item->use!=0;i++){
            DataUtil::toString(str,item->data[i],item->dataType[i]);
            printf("%s\n",str);
        }
        cnt++;
        spj->getNext(item);
        printf("###################\n");
        //break;
        //if(cnt>=20000)break;
    }
    printf("The whole size::%d\n",cnt);
    /*while(true){
        spj->getNext(item);
        for(int i=0;i<item->fieldNum;i++){
            DataUtil::toString(str,item->data[i],item->dataType[i]);
            printf("%s   ",str);
        }
        printf("\n");
        if(item->use==0) break;
      //  printf("%d\n",item->fieldNum);
    }*/
    spj->releaseSPJItem(item);
    spj->destroy();
   // pspj->destroy();
}
int mainHH2()
{
    //    Buffer* b = fb.allocBuffer();
    char s[] = "data/nation.db";
    char s1[] = "hello!world!";
    DBFile* dbfile = new DBFile();
    dbfile->open(s,false);
    FreeBuffer* fb = new FreeBuffer();
    PageUtil* util = new PageUtil(dbfile,fb);
    ClockFIFOStrategy* sts = new ClockFIFOStrategy();
    BufferManager* mgr=new BufferManager(sts,util);
    DirectorySegment* ds = new DirectorySegment(mgr);
    MetaDataSegment *ms = new MetaDataSegment(mgr,ds);
    TableMeta* metas = ms->getMetaData();
   //fillMetaSegment(metas,ms);
    DataSegment* dataseg = new DataSegment(mgr,ds,metas);
    Tuple* tuple = dataseg->buildEmptyTuple();
    //fillTuple(tuple);
    //dataseg->insertTuple(tuple);

    dataseg->findFirstTuple(tuple);

    char s_name[]="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

    TableUtil::readColumn(s_name, &tuple->column[1]); // MAYBE, triggers a Segmentation Fault (Core Dumped)

    printf("\nfind addr %llx\n",tuple->tupleAddr);
    printf("s_name %s\n",s_name);
    dataseg->releaseEmptyTuple(tuple);
    /*
    metas->fieldNum=2;
    strcpy(metas->tname,"tbl_hello");
    metas->tid=1;
    FieldPart* parts = metas->head;
    if(parts->fieldList!=0)
    {
        delete parts->fieldList;
    }
    parts->partNum=2;
    parts->tid=1;
    parts->fieldList = new Field[2];
    parts->fieldList[0].fid=1;
    parts->fieldList[0].dataType=DataTypeFlag::INTEGER;
    strcpy(parts->fieldList[0].fname,"ID");
    parts->fieldList[0].len=4;
    parts->fieldList[1].fid=2;
    parts->fieldList[1].dataType=DataTypeFlag::INTEGER;
    strcpy(parts->fieldList[1].fname,"Key");
    parts->fieldList[1].len=4;
    ms->createOrUpdate();
    */
     Addr add = ds->allocateBlock(SegmentType::DataSeg,PageStatus::EmptyPage);
      //printf("alloc page no %lld ds =%lld \n",pageNo,add);
    // add &= 0x8fffffff;
     Addr pageNo = PAGE_ID(add);
     printf("alloc page no %llx ds =%llx \n",pageNo,add);
     BufferFrame* frame = mgr->requestPageForRead(add);
     mgr->finishRead(frame);
     Addr pageAddr = ds->findFreeSapceBlock(SegmentType::DataSeg);
     printf(" the page Addr with first free Space is %lld\n",pageAddr);


//    for(int i=0;i<DIRPAGE_BODY+3;i++)
  //  {
//        Addr add = ds->allocateBlock(SegmentType::DataSeg,PageStatus::EmptyPage);
//        BufferFrame* frame = mgr->requestPageForRead(add);
//        mgr->finishRead(frame);
//      printf("alloc page no %lld\n",PAGE_ID(add));
//    }
   // getchar();
    /*
    BufferFrame* frame = mgr->requestPageForWrite(0,false);
    printf("\nused Byte %u\n",frame->page->usedByte);
    frame->edit=true;
    Addr addr = util->allocSpace(*frame->page,strlen(s1));
    short  pa = addr;
     printf("alloc addr %lld\n used Byte %u\n",addr,frame->page->usedByte);
    memcpy(frame->page->data+pa,s1,strlen(s1));
    util->freeSpace(*frame->page,addr,strlen(s));
    mgr->finishWrite(frame);
    */
    delete dataseg;
    delete ms;
    delete ds;
    dbfile->flush();
    delete mgr;
    delete sts;
    delete util;

   // delete frees;
       dbfile->close();
    delete dbfile;
      delete fb;
}

int mainHH1()
{
        printf("WELCOME TO USE OUR DATABSE: CARROT!!!\n");
/*

    DBFile file;
    char s[] = "/home/hagen/202";
   bool t=  file.open(s,false);
   if(t)
   {
    unsigned   char buffer[80];
    printf("content %s\n",buffer);
    printf("size %d\n",file.size);
    file.read(buffer,0,80);
    printf("content %s\n",buffer);
    bool t = file.growing(1024);
    if(t)
    {
        printf("growing successful");
    }
    file.close();

   }   */
    FreeBuffer fb;
    Buffer* b = fb.allocBuffer();
    fb.freeBuffer(b);

    BufferFrame**  array = new BufferFrame*[10];
    std::queue<BufferFrame*>* que = 0;
    std::map<Addr,BufferFrame*>* pageMap = 0;
    ClockFIFOStrategy s;
    s.initialize(que, pageMap);
    for(int i=0;i<10;i++)
    {
        array[i]=new BufferFrame();
        array[i]->pageNo=i+1;
        s.whenRead(array[i]);
    }
    s.whenRead(array[1]);

    std::vector<Addr> vec;
    s.electPageToDrop(vec,10);
    s.whenRead(array[1]);
    s.electPageToDrop(vec,5);

    for(int i=0;i<10;i++)
    {
        delete array[i];
    }
    s.release(que,pageMap);
    delete[] array;
//   delete file;
//
//
}
