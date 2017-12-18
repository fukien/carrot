#ifndef DATASEGMENT_H_INCLUDED
#define DATASEGMENT_H_INCLUDED
#include "../common.h"
#include "../buffer/BufferManager.h"
#include "../table/meta.h"
#include "DirectorySegment.h"
#include "../table/TableUtil.h"

class  DataSegment:public Segment
{
public:
    DataSegment(BufferManager* mgr,DirectorySegment* dir,TableMeta* mt);
    ~DataSegment();
    Tuple* buildEmptyTuple();
    void releaseEmptyTuple(Tuple*& tuple);
    void findFirstTuple(Tuple* tuple);
    void findTupleAtPosition(Tuple* tuple,Addr addr);
    void findNextTuple(Tuple* tuple,Tuple* tuple2);
    Addr insertTuple(Tuple* tuple);
    bool deleteTuple(Tuple* tuple);
    Addr flushTuple(Tuple* tuple);
protected:
    void initRootPage();
private:
    BufferManager* manager;
    DirectorySegment* directory;
    TableMeta* meta;
    Addr freePageAddr;
    /**
    * a tuple size should contains two part:
    * One for the tuple header(12Byte),
    *  1. tuple magic (Byte)
    *  2. from which table(Byte)
    *  3. offset in the block.(unsigned short)
    *  4. timestamp
    * One for the tuple body.
    *
    */
    short tupleSize;

};
#endif // DATASEGMENT_H_INCLUDEDT
