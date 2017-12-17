#ifndef INDEXSEGMENT_H_INCLUDED
#define INDEXSEGMENT_H_INCLUDED
#define DEBUG_INDEX
#include <map>
#include "../common.h"
#include "../buffer/BufferManager.h"
#include "../table/meta.h"
#include "Segment.h"
#include "DirectorySegment.h"
#include "MetaDataSegment.h"
#include "DataSegment.h"
#include "../index/Index.h"
#define IndexItemMagic  0x61
#define IndexMetaMagic 0x62
#define MAX_INDEX_NUM 700
// len = 4+8 =12
typedef struct IndexMetaItem
{
    // magic 0x61
    Byte fid;// j建有索引的属性编号
    Byte indexType;
    Byte indexLen;
    Addr indexAddr;
    Index* index;

} IndexMetaItem;
// array size = (7272-20)/12 >700
typedef struct IndexMeta// 存放一张表上的所有索引
{
    //magic 0x62
    Byte tid;  // 表的id
    Byte fieldNum;//属性的个数
    Byte blockNum;
    Addr pageNo;//page的地址
    Addr nextAddr; //当某页存不完索引是需要另加的一个页
    int useLen;
    IndexMetaItem indexList[MAX_INDEX_NUM];
}IndexMeta;

class IndexSegment: public Segment
{
public:
        IndexMeta* indexMeta;
    IndexSegment(BufferManager* mgr,DirectorySegment* dir,DataSegment* dataseg,MetaDataSegment* metaseg);
    ~IndexSegment();
    Index* createIndex(Byte fid,Byte indexType);
    Index* loadIndex(IndexMetaItem* item);
    Index* findIndex(Byte fid,Byte indexType);
    void dropIndex(Byte fid,Byte IndexType);
    friend class Index;
protected:
     void initRootPage();
private:
    //BufferManager* manager;
    DirectorySegment* drs;
    DataSegment* dts;
    MetaDataSegment* mts;

    Addr indexMetaAddr;
    short transFrameToMeta(BufferFrame*  frame,IndexMeta* meta);
    short transMetaToFrame(IndexMeta* meta,BufferFrame* frame);
    short writeIndexMetaItem(IndexMetaItem* item,Byte* data);
    short readIndexMetaItem(IndexMetaItem* item,Byte* data);
    void flush();
};
#endif // INDEXSEGMENT_H_INCLUDED
