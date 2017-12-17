#include "Index.h"
#include "../segment/IndexSegment.h"
    Index::~Index()
    {

    }
    Index::Index(IndexSegment* idx,Byte fid,Addr addr)
    {
        this->fieldId = fid;
                this->idxs = idx;
        this->drs = idxs->drs;
        this->dts = idxs->dts;
        this->mts = idxs->mts;
        this->manager = this->idxs->manager;
        this->indexLen = mts->getMetaData()->head->fieldList[fid].len;
        this->indexRootAddr = addr;
        this->indexType = 0;
    }
    //Create or load
void Index::create()
    {

    }
  void Index::load()
    {

    }
 void Index::destroyMySelf()
    {

    }
  IndexIterator* Index::findByKey(void* key)
    {

    }
void Index::destoryIterator(IndexIterator* iterator)
    {

    }
Addr Index::insertElem(IndexItem* item)
    {

    }
Addr Index::deleteElem(IndexItem* item)
    {

    }
IndexItem* Index::buildItem()
    {

    }
void Index::releaseIndexItem(IndexItem* item)
    {

    }
Byte Index::getIndexType()
    {
        return this->indexType;
    }
Byte Index::getIndexLen()
    {
        return this->indexLen;
    }
Byte Index::getFieldId()
    {
        return this->fieldId;
    }
void Index::releaseAll()
    {

    }
      Addr Index::getRootAddr()
     {
        return this->indexRootAddr;
     }
     IndexIterator*Index::findByRange(void*value1,void*value2){}
