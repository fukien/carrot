#ifndef PINDEX_H_INCLUDED
#define PINDEX_H_INCLUDED
#include "../common.h"
#include "../table/meta.h"
#include "../segment/DataSegment.h"
#include "../segment/MetaDataSegment.h"
#include"../segment/IndexSegment.h"
#include"../segment/DirectorySegment.h"
#include<map>
#include "Index.h"

using namespace std;
//class IndexSegment;
//class IndexType
//{
//    public:
//    static const Byte eptidx = 0xff;// for test
//     static const  Byte bptidx=0x01;
//     static const Byte hashidx = 0x02;
//};
typedef struct HashIndex{
    short indexType;
    long long bucketSize;//the number of bucket
    long long  recordSize;//the number of record
    Addr nextAddr;//overflow block size
    short hashSize;//the value of i
    float splitRate;//the condition for block to split
    short keySize;// the num of key value;
    map<long long,Addr>mp;
}HashIndex;

typedef struct HashIndexItem{
    Addr nextAddr;
    int KeyNum;
    map<unsigned long long,vector<Addr> >mp;
}HashIndexItem;

class PrimaryHashIndex : public Index
{
public:
    PrimaryHashIndex(IndexSegment* IndexSegment,Byte fid,Addr addr);
    //Create or load

   void create();
    Addr create(long long bucketSize,long long recordSize,float splitRate);
   void load();
    void destroyMySelf();
    IndexIterator* findByKey(void* key);
    void destoryIterator(IndexIterator* iterator);
    Addr insertElem(IndexItem* item);
    Addr deleteElem(IndexItem* item);
    void deleteIndexKey(long long value,Addr addr);
    bool deleteBucketItem(Addr addr ,IndexItem*item);
    bool deleteBucketItemByKey(Addr addr ,IndexItem*item);
    IndexItem* buildItem();
    void releaseIndexItem(IndexItem* item);
    Byte getIndexType();
    Addr createBucket();
    void HashIndexSplit();
    void HashIndexMerge();
   Addr findBucketByValue(long long bucketValue,HashIndex*hashIndex);
     Addr updateHashIndexMeta(long long bucketSize,short hashSize,long long recordSize,Addr addr);
    long long getBucketValue(void*key,int hashSize,long long bucketSize);
    //virtual Byte getIndexLen();
    //virtual Byte getFieldId();
    virtual void transBucketItem(Addr addr,long long value, map<unsigned long long,vector<Addr> >&mp);
    virtual void getAllBucketItem(Addr addr,map<unsigned long long,vector<Addr> >&mp);
    //virtual void splitBucket(uint value,Addr addr);
    void flushHashIndex();
    Addr findPageToWrite(long long bucketValue,Addr indexAddr,HashIndex*indexHashIndex);
    short transHashIndexToFrame(HashIndex* index,BufferFrame* frame);
   short transFrameToHashIndex(BufferFrame*frame,HashIndex*Index);
    short transHashIndexItemToFrame(HashIndexItem*hashIndexItem,BufferFrame*frame);
   short transFrameToHashIndexItem(HashIndexItem*hashIndexItem,BufferFrame*frame);
    short insertBucketItem(Addr pageAddres,Addr address,unsigned long long);
    void insertMultiBucketItems(Addr add,map<unsigned long long,vector<Addr> >mp);
    void scanBucket(unsigned long long key,Addr addr,vector<Addr>&addrlist);
    void scanAllBucket(Addr addr,vector<Addr>&addrlist);
    void scanIndex(Addr addr);
    IndexIterator*findByRange(void*value1,void*value2);
//    virtual void writeBucket(IndexItem*item,Addr*bucketAddr);
    Addr getRootAddr();
   Addr getNextAddr();
    void releaseAll();
    ~PrimaryHashIndex();
    class HashIndexIterator:public IndexIterator{
        public :
            void findFirst(IndexItem*item);
            void findNext(IndexItem*item);
            bool hasNext();
            HashIndexIterator(PrimaryHashIndex*primaryHashIndex,void * key,vector<Addr>ve);
            friend class PrimaryHashIndex;
        private:
            vector<Addr>indexList;
            int cursor;
            PrimaryHashIndex*primaryHashIndex;
            void*key;
    };
protected:
    /*
    DirectorySegment* drs;
    DataSegment* dts;
    MetaDataSegment* mts;
    IndexSegment* idxs;
    //Byte fieldId;
    Addr indexRootAddr;
    */
    HashIndex *hashIndex;
    Byte dataType;
   // Byte indexLen;
   // short indexType;
    long long bucketSize;//the number of bucket
    long long  recordSize;//the number of record
    Addr nextAddr;//overflow block size
    short hashSize;//the value of i
    float splitRate;//the condition for block to split
    float mergeRate;
    short keySize;// the number of key
    bool created;
    bool loaded;

   static const int MAX_INDEX_SIZE=603;//MAX NUM of <key,addr> per page
    static const int INDEX_ITEM_HEAD=12;//the size of bucket head
    static const int INDEX_ITEM_SIZE=454;//the size of bucket items
    static const int BUCKET_ITEM_SIZE=16;//the size of bucket key-value
    static  const int BUCKET_SPLIT_RATE=385;//the size is 385
    static const int BUCKET_MERGE_RATE=68;

 /*static const int MAX_INDEX_SIZE=1;//MAX NUM of <key,addr> per page
  static const int INDEX_ITEM_HEAD=12;//the size of bucket head
   static const int INDEX_ITEM_SIZE=3;//the size of bucket items
   static const int BUCKET_ITEM_SIZE=16;//the size of bucket key-value
  static  const int BUCKET_SPLIT_RATE=2;//the size is 385
  static const int BUCKET_MERGE_RATE=1;*/
};

#endif // INDEX_H_INCLUDED

