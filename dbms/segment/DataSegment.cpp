#include "DataSegment.h"
#ifdef DEBUG
#include <cstdlib>
#include <cstdio>
#endif // DEBUG
#include <cstdlib>
#include <cstdio>
DataSegment::DataSegment(BufferManager* mgr,DirectorySegment* dir,TableMeta* mt):Segment(mgr),manager(mgr),directory(dir),meta(mt)
{
    tupleSize = TableUtil::estimateTupleSize(meta);
    freePageAddr=0;
    #ifdef DEBUG
    printf("\n one tuple size %d\n",tupleSize);
    #endif
}
DataSegment::~DataSegment()
{

}
Tuple* DataSegment::buildEmptyTuple()
{
    return TableUtil::buildTuple(meta);
}
void DataSegment::releaseEmptyTuple(Tuple*& tuple)
{
    TableUtil::releaseTuple(tuple,meta);
}
void DataSegment::findTupleAtPosition(Tuple* tuple,Addr addr)
{
    BufferFrame* frame = manager->requestPageForRead(addr);
    Page* page = frame->page;
    PageUtil* util = manager->getPageUtil();
    Byte* data = page->data;
    PageAddr offset = (PAGE_OFFSET(addr));
     while(data[offset]!=TUPLE_MAGIC)
    {
        offset++;
        if(offset==PAGE_SIZE-1)break;
    }
    if(offset==PAGE_SIZE-1)
    {
        #ifdef DEBUG
        printf("data segment found no tuple! addr=%lld\n",addr);
        #endif
    }
    else
    {
        TableUtil::readTuple(data+offset,tuple,meta);
        tuple->offset = offset;
        tuple->tupleAddr = addr+offset;
    }
    manager->finishRead(frame);
}
void DataSegment::findFirstTuple(Tuple* tuple)
{
    Addr addr = directory->findFirstBlock(SegmentType::DataSeg);
    if(addr<=0)
    {
        #ifdef DEBUG
            printf("no datasegment found!\n");
        #endif
            return ;
    }
    PageAddr offset = PAGE_HEAD_LEN+PAGE_ALIGN;
    BufferFrame* frame = manager->requestPageForRead(addr);
    Page* page = frame->page;
    PageUtil* util = manager->getPageUtil();
    Byte* data = page->data;
    //data+=offset;
    while(data[offset]!=TUPLE_MAGIC)
    {
        offset++;
        if(offset==PAGE_SIZE-1)break;
    }
    if(offset==PAGE_SIZE-1)
    {
        #ifdef DEBUG
        printf("data segment found no tuple! addr=%lld\n",addr);
        #endif
    }
    else
    {
    TableUtil::readTuple(data+offset,tuple,meta);
    tuple->offset = offset;
    tuple->tupleAddr = addr+offset;
    }
    manager->finishRead(frame);

}
void DataSegment::findNextTuple(Tuple* tuple,Tuple* tuple2)
{
    Addr tupleAddr = tuple->tupleAddr;
    Addr pageNo1 = PAGE_ID(tupleAddr);
    Addr pageNo2 = PAGE_ID(tupleAddr+tupleSize+tupleSize+3);
    if(pageNo1==pageNo2)
    {
        tupleAddr+=tupleSize;
        BufferFrame* frame = manager->requestPageForRead(tupleAddr);
        PageAddr offset = PAGE_OFFSET(tupleAddr);
        Page* page = frame->page;
        Byte*  data = page->data;
        PageAddr oldofst = offset;
        while(data[offset]!=TUPLE_MAGIC)
        {
            offset++;
            if(offset==PAGE_SIZE-1)break;
        }
         if(offset==PAGE_SIZE-1)
        {
            #ifdef DEBUG
            printf("data segment found no tuple! addr=%llx\n",tupleAddr);
            #endif
        }
        else
        {
        TableUtil::readTuple(data+offset,tuple2,meta);
        tuple2->offset = offset;
        tuple2->tupleAddr = PAGE_ADDR(pageNo1)+offset;
        }
        manager->finishRead(frame);
    }else
    {

        Addr addr = directory->findNextBlock(tupleAddr,SegmentType::DataSeg);
        #ifdef DEBUG
        printf("addr %llx next addr %llx\n",tupleAddr,addr);
        #endif
        if(addr>0)
        {
                PageAddr offset = PAGE_HEAD_LEN+PAGE_ALIGN;
                BufferFrame* frame = manager->requestPageForRead(addr);
                Page* page = frame->page;
                PageUtil* util = manager->getPageUtil();
                Byte* data = page->data;
    //data+=offset;
                while(data[offset]!=TUPLE_MAGIC)
                {
                    offset++;
                    if(offset==PAGE_SIZE-1)break;
                }
                if(offset==PAGE_SIZE-1)
                {
                    #ifdef DEBUG
                    printf("data segment found no tuples! addr=%llx\n",addr);
                    #endif
                }else
                {
                TableUtil::readTuple(data+offset,tuple2,meta);
                tuple2->offset = offset;
                tuple2->tupleAddr = addr+offset;
                }
                manager->finishRead(frame);
        }
    }

}
Addr DataSegment::insertTuple(Tuple* tuple)
{
    while(true)
    {
        Addr addr = 0;
        addr = freePageAddr;
        if(addr<=0)directory->findFreeSapceBlock(SegmentType::DataSeg);
        if(addr<=0)
        {
            addr = directory->allocateBlock(SegmentType::DataSeg,PageStatus::EmptyPage);
        }
        if(addr<=0)
        {
            #ifdef DEBUG
            printf("allocation error!");
            #endif // DEBUG
            return 0;
        }
        BufferFrame* frame = manager->requestPageForWrite(addr,false);
        Page* page = frame->page;
        PageUtil* util = manager->getPageUtil();
        PageAddr offset = util->allocSpace(*page,tupleSize);
        Byte seg = SegmentType::DataSeg;
        Byte status = PageStatus::HalfPage;
        if(offset<=0)
        {
            // no space left.
            status = PageStatus::FullPage;
            directory->updateSpaceMark(frame,seg,status);
            manager->finishWrite(frame);
        }
        else
        {
            tuple->offset= offset;
            tuple->tupleAddr = addr+offset;
            short written = TableUtil::writeTuple(page->data+offset,tuple,meta);
            if(written !=tupleSize)
            {
                printf("warning: written size is not equals to tupleSize! written size %d tuple size %d\n",written,tupleSize);
            }
            if((PAGE_BODY_LEN-frame->page->usedByte)<tupleSize)
            {
                status = PageStatus::FullPage;
                freePageAddr = 0;
            }else
            {
                freePageAddr = addr;
            }
            directory->updateSpaceMark(frame,seg,status);
            frame->edit = true;
            manager->finishWrite(frame);
            return addr+offset;
        }

    }
}
bool DataSegment::deleteTuple(Tuple* tuple)
{
    Addr addr = tuple->tupleAddr;
    if(addr>0)
    {
        PageAddr offset = PAGE_OFFSET(addr);
        BufferFrame* frame = manager->requestPageForWrite(addr,false);
        PageUtil* util = manager->getPageUtil();
        bool suc = util->freeSpace(*frame->page,offset,tupleSize);
        frame->edit = true;
        if(!suc)
        {
            #ifdef DEBUG
            printf("free the tuple size failure with addr = %lld \t %llx\n",addr,addr);
            #endif // DEBUG
        }
        manager->finishWrite(frame);
    }
    else
    {
        #ifdef DEBUG
        printf("missing addr when deleting");
        #endif // DEBUG
    }
}
void DataSegment::initRootPage()
{

}

