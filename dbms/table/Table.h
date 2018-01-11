#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include "../common.h"
#include "../buffer/BufferManager.h"
#include "../buffer/ClockFIFOStrategy.h"
#include "../segment/Segment.h"
#include "../segment/DirectorySegment.h"
#include "../segment/MetaDataSegment.h"
#include "../segment/DataSegment.h"
#include "../segment/IndexSegment.h"
// TODO: create index segment.
class Table
{
public:
        Table();
        BufferStrategy* getStrategy();
    /**
    * warning:
    * if the strategy is initialize, it must be freed manually.
    * the class only freed the current strategy.
    * otherwise it will lead to the memory leak!
    * if the table is opened, it will not effect!
    *
    */
        void setStrategy(StrategyInBuffer s);
        bool open(char* name,bool readonly);
        bool isInit();
        TableMeta* getTableMeta();
        void updateTableMeta();
        Tuple* buildEmptyTuple();
        IndexSegment* getIndexSegment();
        DataSegment*getDataSegment();
        void releaseEmptyTuple(Tuple*& tuple);
        void findFirstTuple(Tuple* tuple);
        void findTupleAtPosition(Tuple* tuple,Addr addr);
        void findNextTuple(Tuple* tuple,Tuple* tuple2);
        Addr insertTuple(Tuple* tuple);
        bool deleteTuple(Tuple* tuple);
        void close();
        Addr flushTuple(Tuple *tuple);
        ~Table();
    private:
        BufferStrategy* strategy;
        DirectorySegment* dirseg;
        MetaDataSegment* metaseg;
        DataSegment* dataseg;
        IndexSegment* indexseg;
        BufferManager* mgr;
        PageUtil* util;
        DBFile* dbfile;
        FreeBuffer* fb;
        TableMeta* meta;
        bool init;
};


#endif // TABLE_H_INCLUDED
