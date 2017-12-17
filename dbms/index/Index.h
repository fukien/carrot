#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED
#include "../common.h"
#include "../table/meta.h"
#include "../segment/DataSegment.h"
#include "../segment/MetaDataSegment.h"
class IndexSegment;
class IndexType
{
    public:
        static const Byte eptidx = 0xff;// for test
        static const  Byte bptidx=0x01;
        static const Byte hashidx = 0x02;
};

typedef struct IndexItem
{
    void* key;
    Addr addr;
} IndexItem;

class IndexIterator
{
public:
    virtual void findFirst(IndexItem* item)=0;
    virtual void findNext(IndexItem* item)=0;
    virtual bool hasNext()=0;
};

class Index
{
public:
    Index(IndexSegment* IndexSegment,Byte fid,Addr addr);
    //Create or load
    virtual void create();
    virtual void load();
    virtual void destroyMySelf();
    virtual IndexIterator* findByKey(void* key);
    virtual void destoryIterator(IndexIterator* iterator);
    virtual Addr insertElem(IndexItem* item);
    virtual Addr deleteElem(IndexItem* item);
    virtual IndexItem* buildItem();
    virtual void releaseIndexItem(IndexItem* item);
    virtual Byte getIndexType();
    virtual Byte getIndexLen();
    virtual Byte getFieldId();
    virtual Addr getRootAddr();
    virtual void releaseAll();
    virtual IndexIterator*findByRange(void*value1,void*value2);
    ~Index();
protected:
    DirectorySegment* drs;
    DataSegment* dts;
    MetaDataSegment* mts;
    IndexSegment* idxs;
    BufferManager* manager;
    Byte fieldId;//建索引的属性号
    Addr indexRootAddr;
    Byte indexLen;
    Byte indexType;
};
#endif // INDEX_H_INCLUDED
