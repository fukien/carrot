#include "Table.h"
#include <cstdio>
#include <cstdlib>
Table::Table(){
strategy=0;
dirseg = 0;
metaseg=0;
 dataseg=0;
init=false;
}

BufferStrategy* Table::getStrategy(){
    return this->strategy;
}
/**
    * warning:
    * if the strategy is initialize, it must be freed manually.
    * the class only freed the current strategy.
    * otherwise it will lead to the memory leak!
    * if the table is opened, it will not effect!
    *
    */
void Table::setStrategy(StrategyInBuffer _strategy){
    if(init)
    {
        #ifdef DEBUG
        printf("the strategy is already applied! and this setting is invalid.");
        #endif // DEBUG
        return ;
    }
        if(this->strategy!=0)
        {
            delete this->strategy;
            this->strategy =0;
        }
    if(_strategy==FIFO)
    {
        strategy=new FIFOStrategy();
    }else if(_strategy==ClOCK)
    {
        strategy = new ClockFIFOStrategy();
    }
    else
    {
                #ifdef DEBUG
        printf("the strategy is  not implemented yet!.");
        #endif // DEBUG
    }
}

bool Table::open(char* name,bool readonly){
    if(init)
    {
        #ifdef DEBUG
        printf(" the table is already open!");
        #endif // DEBUG
        return false;
    }
    this->dbfile = new DBFile();
    dbfile->open(name,readonly);
    this->fb = new FreeBuffer();
    this->util = new PageUtil(dbfile,fb);
    if(this->strategy==0)this->strategy = new ClockFIFOStrategy();
    this->mgr = new BufferManager(strategy,util);
    this->dirseg = new DirectorySegment(mgr);
    this->metaseg = new MetaDataSegment(mgr,dirseg);
    this->meta = metaseg->getMetaData();
    this->dataseg = new DataSegment(mgr,dirseg,meta);
    /**
    * TODO: the index segment should be created manually.
    * because it need meta segment.
    */
    this->indexseg = 0;
    init = true;
}

bool Table::isInit(){
    return init;
}

TableMeta* Table::getTableMeta(){
    return meta;
}

void Table::updateTableMeta(){
    metaseg->createOrUpdate();
    delete dataseg;
    this->dataseg = new DataSegment(mgr,dirseg,meta);
}
IndexSegment* Table::getIndexSegment()
{
    if(this->indexseg==0)
    {
        this->indexseg = new IndexSegment(this->mgr,this->dirseg,this->dataseg,this->metaseg);
    }
    return this->indexseg;
}
DataSegment*Table::getDataSegment(){
    return this->dataseg;
}
Tuple* Table::buildEmptyTuple(){
    return dataseg->buildEmptyTuple();
}
    void Table::findTupleAtPosition(Tuple* tuple,Addr addr)
    {
        dataseg->findTupleAtPosition(tuple,addr);
    }
void Table::releaseEmptyTuple(Tuple*& tuple){
    dataseg->releaseEmptyTuple(tuple);
}

void Table::findFirstTuple(Tuple* tuple){
    dataseg->findFirstTuple(tuple);
}

void Table::findNextTuple(Tuple* tuple,Tuple* tuple2){
    dataseg->findNextTuple(tuple,tuple2);
}

Addr Table::insertTuple(Tuple* tuple){
    return dataseg->insertTuple(tuple);
}

bool Table::deleteTuple(Tuple* tuple){
    return dataseg->deleteTuple(tuple);
}

void Table::close(){
    if(indexseg!=0)
    {
        delete this->indexseg;
        this->indexseg = 0;
    }
    if(dataseg!=0)
    {
        delete this->dataseg;
        this->dataseg=0;
    }
    if(metaseg!=0)
    {
        delete this->metaseg;
        this->metaseg = 0;
    }
    if(dirseg!=0)
    {
        delete this->dirseg;
        this->dirseg = 0;
    }
    if(dbfile!=0)dbfile->flush();
    if(this->mgr!=0){delete this->mgr;this->mgr=0;}
    if(this->strategy!=0){delete this->strategy;strategy=0;}
    if(this->util!=0){delete this->util;util = 0;}
    if(dbfile!=0)
    {   dbfile->close();
        delete dbfile;
        this->dbfile = 0;
    }
    if(fb!=0)
    {delete this->fb;
    fb = 0;
    }
    init = false;
}

Table::~Table(){
    if(init)this->close();
}

