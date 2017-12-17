#include "PrimaryHashIndex.h"
#include "../segment/IndexSegment.h"
#include <cstdio>
#include <cstdlib>
#include<cmath>
#include<algorithm>

IndexIterator*PrimaryHashIndex::findByRange(void*value1,void*value2){}
    PrimaryHashIndex::~PrimaryHashIndex()
    {
        if(this->hashIndex!=0){
            BufferFrame* frame=manager->requestPageForWrite(this->indexRootAddr,false);
            transHashIndexToFrame(this->hashIndex,frame);
            frame->edit=true;
            manager->finishWrite(frame);
            delete this->hashIndex;
            this->hashIndex=0;
        }
    }
    PrimaryHashIndex::PrimaryHashIndex(IndexSegment* idx,Byte fid,Addr addr):Index(idx,fid,addr)
    {

       // printf("create index now %d %d\n",this->idxs,this->drs);
        this->hashIndex=0;
        this->indexRootAddr = addr;
        this->indexType = IndexType::hashidx;
        this->bucketSize=2;
        this->hashSize=1;
        this->recordSize=0;
        this->splitRate=PrimaryHashIndex::BUCKET_SPLIT_RATE;
        this->mergeRate=PrimaryHashIndex::BUCKET_MERGE_RATE;
        this->nextAddr=0;
        this->keySize=0;
        this->dataType=this->mts->getMetaData()->head->fieldList[fid].dataType;
        created=false;
        loaded=false;
        if(addr==0){
                this->indexRootAddr=this->drs->allocateBlock(SegmentType::IndexSeg,PageStatus::HalfPage);
                create();
        }else{
            load();
        }
    }
    //Create or load
void PrimaryHashIndex::create()
    {
        if(!created){
            BufferFrame* frame=this->manager->requestPageForWrite(this->indexRootAddr,false);
            HashIndex*hashIndex=new HashIndex();
            hashIndex->indexType=IndexType::hashidx;
            hashIndex->bucketSize=2;
            hashIndex->hashSize=1;
            hashIndex->recordSize=0;
            hashIndex->splitRate=PrimaryHashIndex::splitRate;
            hashIndex->nextAddr=0;
            hashIndex->keySize=0;
            transHashIndexToFrame(hashIndex,frame);
            this->hashIndex=hashIndex;
            frame->edit=true;
            this->manager->finishWrite(frame);
            Tuple* tuple = this->dts->buildEmptyTuple();
            IndexItem* item = this->buildItem();
            this->dts->findFirstTuple(tuple);
            int cnt = 0;
           // vector<IndexItem*>ve;
            while(tuple->tupleAddr>0)
            {
                cnt++;
                    Addr old = tuple->tupleAddr;
                    item->addr = old;
                    memcpy(item->key,tuple->column[this->fieldId].data,this->indexLen);
                    float hh=0;
                    memcpy(&hh,item->key,sizeof(float));
                   unsigned long long mykey;
                    memcpy(&mykey,&hh,sizeof(unsigned long long));
                    printf("values::%f     %lld\n",hh,mykey);
                    this->insertElem(item);
                   // ve.push_back(item);
                  //  item = this->buildItem();
                    this->dts->findNextTuple(tuple,tuple);
                    if(tuple->tupleAddr==old)
                    {
                            break;
                    }
                if(cnt==20)
                {
                    break;
                }
            }
//            for(int i=0;i<ve.size();i++){
//               //deleteElem(ve[i]);
//                this->releaseIndexItem(ve[i]);
//            }
            /*
            IndexIterator* myiterator=findByKey(item->key);
            IndexItem* myitem= this->buildItem();
            myiterator->findFirst(myitem);
            printf("item key ::%d %d\n",myitem->key,myitem->addr);
            if(myiterator->hasNext()){
                        myiterator->findNext(myitem);
                        printf("item key ::%d %d\n",myitem->key,myitem->addr);
                }*/
               // scanIndex(this->indexRootAddr);
                printf("record size::%lld  bucket size:: %lld",this->hashIndex->recordSize,this->hashIndex->bucketSize);
                this->releaseIndexItem(item);
                item = 0;
                this->dts->releaseEmptyTuple(tuple);
        }
    }
    Addr PrimaryHashIndex::create(long long bucketSize,long long recordSize,float splitRate){
            Addr addr=this->drs->allocateBlock(SegmentType::IndexSeg,PageStatus::HalfPage);
            BufferFrame* frame=this->manager->requestPageForWrite(addr,false);
            HashIndex*hashIndex=new HashIndex();
            hashIndex->indexType=IndexType::hashidx;
            hashIndex->bucketSize=bucketSize;
            hashIndex->hashSize=1;
            hashIndex->recordSize=recordSize;
            hashIndex->splitRate=splitRate;
            hashIndex->nextAddr=0;
            hashIndex->keySize=0;
            transHashIndexToFrame(hashIndex,frame);
            frame->edit=true;
            this->manager->finishWrite(frame);
            created=true;
           // this->hashIndex=hashIndex;
            return addr;
    }
  void PrimaryHashIndex::load()
    {
            if(!loaded){
                HashIndex*hashIndex=new HashIndex();
                BufferFrame * frame=manager->requestPageForRead(this->indexRootAddr);
                transFrameToHashIndex(frame,hashIndex);
                this->hashIndex=hashIndex;
                manager->finishRead(frame);
                loaded=true;
               printf("load now!%d",this->hashIndex);
            }
    }
 void PrimaryHashIndex::destroyMySelf()
    {

    }
  IndexIterator* PrimaryHashIndex::findByKey(void* key)
    {
        long long BucketValue=PrimaryHashIndex::getBucketValue(key,this->hashIndex->hashSize,this->hashIndex->bucketSize);
        Addr addr=findBucketByValue(BucketValue,this->hashIndex);
        float hh=0;
        memcpy(&hh,key,sizeof(float));

        unsigned long long data=0;
        memcpy(&data,&hh,sizeof(unsigned long long));
        printf("the value ::%f  %lld\n",hh,data);
        vector<Addr>addrlist;
        scanBucket(data,addr,addrlist);
        PrimaryHashIndex*self=this;
        IndexIterator *myIterator=new HashIndexIterator(self,key,addrlist);
       printf("the size of key:: %d\n",addrlist.size());
        return myIterator;
    }
    void PrimaryHashIndex::scanBucket(unsigned long long key,Addr addr,vector<Addr>&addrlist){
        BufferFrame*frame=this->manager->requestPageForRead(addr);
        HashIndexItem*item=new HashIndexItem();
        transFrameToHashIndexItem(item,frame);
        if(item->mp.count(key)>0){
            for(int i=0;i<item->mp[key].size();i++){
                addrlist.push_back(item->mp[key][i]);
            }
        }
        if(item->nextAddr!=0){
            manager->finishRead(frame);
            scanBucket(key,item->nextAddr,addrlist);
        }else{
            manager->finishRead(frame);
        }
    }
    void PrimaryHashIndex::scanIndex(Addr addr){
              BufferFrame*frame=this->manager->requestPageForRead(addr);
              HashIndex*hashIndex=new HashIndex();
              transFrameToHashIndex(frame,hashIndex);
              manager->finishRead(frame);
              printf("the index size::%d\n",hashIndex->keySize);
              map<long long,Addr>::iterator it=hashIndex->mp.begin();
              vector<Addr>ff;
              while(it!=hashIndex->mp.end()){
                    printf("key-value %lld %lld   ",it->first,it->second);
                    scanAllBucket(it->second,ff);
                    it++;
              }
              if(hashIndex->nextAddr!=0){
                    printf("next index");
                    scanIndex(hashIndex->nextAddr);
              }
    }
    void PrimaryHashIndex::scanAllBucket(Addr addr,vector<Addr>&addrlist){
            BufferFrame*frame=this->manager->requestPageForRead(addr);
            HashIndexItem*item=new HashIndexItem();
            transFrameToHashIndexItem(item,frame);
            manager->finishRead(frame);
            printf("keynum:%d\n",item->KeyNum);
            map< unsigned long long,vector<Addr> >::iterator it;
             it=item->mp.begin();
             while(it!=item->mp.end()){
                    printf("key %d :",it->first);
                 for(int i=0;i<it->second.size();i++){
                     printf("%lld ",it->second[i]);
                 }
                 it++;
            }
            if(item->nextAddr!=0){
                    printf("next bucket\n");
                scanAllBucket(item->nextAddr,addrlist);
            }

    }
    PrimaryHashIndex::HashIndexIterator::HashIndexIterator(PrimaryHashIndex* primaryHashIndex,void*key,vector<Addr>ve){
        this->primaryHashIndex=primaryHashIndex;
        this->key=key;
        this->cursor=0;
        this->indexList=ve;
    }
void PrimaryHashIndex::HashIndexIterator::findFirst(IndexItem*item){
        if(this->indexList.size()>0){
            memcpy(item->key,this->key,8);
            //memcpy(item->key,&num,8);
            //printf("456");
            memcpy(&item->addr,&this->indexList[0],sizeof(Addr));
            //printf("123");
        }
}
void PrimaryHashIndex::HashIndexIterator::findNext(IndexItem*item){
            this->cursor++;
            if(cursor<this->indexList.size()){
                memcpy(item->key,this->key,8);
                memcpy(&item->addr,&this->indexList[cursor],sizeof(Addr));
            }
}
bool PrimaryHashIndex::HashIndexIterator::hasNext(){
            if(this->cursor+1>=this->indexList.size()){
                return false;
            }else{
                return true;
            }
}
void PrimaryHashIndex::destoryIterator(IndexIterator* iterator)
    {
            delete iterator;
    }
Addr PrimaryHashIndex::insertElem(IndexItem* item)
    {
       BufferFrame * frame=manager->requestPageForRead(this->indexRootAddr);
       transFrameToHashIndex(frame,this->hashIndex);
       manager->finishRead(frame);
        Byte data[8];
        memcpy(data,item->key,8);
        long long  hashValue=0;
        int cnt=0;
        int factor[16];
        int round=3;
        for(int i=0;i<16;i++){
            if(i==0) factor[i]=1;
            else{
                factor[i]=round;
                round=round*3;
            }
        }
        for(int i=0;i<8;i++){//hashvalue the sum of bytes
            Byte myByte=data[i];
            hashValue+=(myByte&15)*factor[cnt++];
            myByte=data[i];
            hashValue+=(myByte>>4)*factor[cnt++];
        }
        long long hashBucket=(2<<(this->hashIndex->hashSize-1))-1;//the max 11..11

        //printf("hashBucket::%d\n",hashBucket);
        long long BucketValue=hashBucket&hashValue;
        //printf("the value of hashBucket %d %d",hashBucket,BucketValue);
        if(BucketValue>=this->hashIndex->bucketSize){
            BucketValue-=(long long)pow(2,this->hashIndex->hashSize-1);
          //  printf("\n the last bucket value: %lld\n",BucketValue);
        }
        Addr bucketAddr=findPageToWrite(BucketValue,this->indexRootAddr,this->hashIndex);
        //printf("insert the   fuck item\n");
        unsigned long long mykey=0;
        memcpy(&mykey,item->key,sizeof(unsigned long long));
        insertBucketItem(bucketAddr,item->addr,mykey);
         frame=manager->requestPageForWrite(this->indexRootAddr,false);
         transFrameToHashIndex(frame,this->hashIndex);
        this->hashIndex->recordSize++;
         //printf("finish  item\n");
        //printf("recordsize::%d bucketSize::%d\n splitRate::%f\n",this->hashIndex->recordSize,this->hashIndex->bucketSize,this->hashIndex->splitRate);
        if(this->hashIndex->recordSize/this->hashIndex->bucketSize>=this->hashIndex->splitRate){
            //printf("recordsize::%d bucketSize::%d\n hashSize::%d\n",this->hashIndex->recordSize,this->hashIndex->bucketSize,this->hashIndex->hashSize);
            this->hashIndex->bucketSize++;
            if(this->hashIndex->bucketSize>(2<<(this->hashIndex->hashSize-1))){
                this->hashIndex->hashSize++;
            }
            transHashIndexToFrame(this->hashIndex,frame);
             frame->edit=true;
            manager->finishWrite(frame);
            //printf("begin to indexsplit \n");
            HashIndexSplit();
        }else{
            transHashIndexToFrame(this->hashIndex,frame);
             frame->edit=true;
             manager->finishWrite(frame);
        }

    }
    long long PrimaryHashIndex::getBucketValue(void *key,int hashSize,long long bucketSize){
        Byte data[8];
        memcpy(data,key,8);
        long long  hashValue=0;
        int cnt=0;
        int factor[16];
        int round=3;
        for(int i=0;i<16;i++){
            if(i==0) factor[i]=1;
            else{
                factor[i]=round;
                round=round*3;
            }
        }
        for(int i=0;i<8;i++){//hashvalue the sum of bytes
            Byte myByte=data[i];
            hashValue+=(myByte&15)*factor[cnt++];
            //printf("%d\n",hashValue);
            myByte=data[i];
            hashValue+=(myByte>>4)*factor[cnt++];
            //printf("%d\n",hashValue);
        }
            long long hashBucket=(2<<(hashSize-1))-1;//the max 11..11
            long long BucketValue=hashBucket&hashValue;
            if(BucketValue>=bucketSize){
                BucketValue-=2<<(hashSize-1);
            }
            return BucketValue;
    }
//    void PrimaryHashIndex::writeBucket(IndexItem*item,Addr*bucketAddr){
//                short written=insertBucketItem(bucketAddr,item->addr,item->key);
//    }
    Addr PrimaryHashIndex::findPageToWrite(long long bucketValue,Addr indexaddr,HashIndex*indexHashIndex){
         if(indexHashIndex->mp.count(bucketValue)>0){//find and direct return
                return indexHashIndex->mp[bucketValue];
        }else{// not found then look for the overflow block
            if(indexHashIndex->nextAddr!=0){// if there is a overflow block
                BufferFrame*frame=manager->requestPageForRead(indexHashIndex->nextAddr);
               HashIndex * hashIndex=new HashIndex();
                transFrameToHashIndex(frame,hashIndex);
                this->manager->finishRead(frame);
                return findPageToWrite(bucketValue,indexHashIndex->nextAddr,hashIndex);//load the over flow block
            }else{// no overflow bock just judge if there is a space to write
                  if(indexHashIndex->keySize==PrimaryHashIndex::MAX_INDEX_SIZE){//no space the create a overflow block and write
                       Addr addr=create(indexHashIndex->bucketSize,indexHashIndex->recordSize,indexHashIndex->splitRate);
                       HashIndex*hashIndex=new HashIndex();
                       //flushHashIndex();
                      // printf("allote key value %lld %lld::",bucketValue,addr);
                       BufferFrame*frame=manager->requestPageForWrite(indexaddr,false);
                       transFrameToHashIndex(frame,hashIndex);
                       hashIndex->nextAddr=addr;
                       transHashIndexToFrame(hashIndex,frame);
                       frame->edit=true;
                       manager->finishWrite(frame);
                       frame=manager->requestPageForWrite(addr,false);
                       transFrameToHashIndex(frame,hashIndex);
                       hashIndex->mp[bucketValue]=createBucket();
                       hashIndex->keySize++;
                       transHashIndexToFrame(hashIndex,frame);
                       frame->edit=true;
                       manager->finishWrite(frame);
                       return hashIndex->mp[bucketValue];
                  }else{//if there is space just write
                    //  printf("keysize :%d %d",this->hashIndex->keySize,this->hashIndex->mp.size());
                       BufferFrame*frame=manager->requestPageForWrite(indexaddr,false);
                       transFrameToHashIndex(frame,indexHashIndex);
                       indexHashIndex->mp[bucketValue]=createBucket();
                       indexHashIndex->keySize++;
                        transHashIndexToFrame(indexHashIndex,frame);
                        frame->edit=true;
                        manager->finishWrite(frame);
                       return indexHashIndex->mp[bucketValue];
                  }
            }
        }
    }
     Addr PrimaryHashIndex::findBucketByValue(long long bucketValue,HashIndex*indexhashIndex){
        if(indexhashIndex->mp.count(bucketValue)>0){//find and direct return
                //printf("findbucketValue::%d",this->hashIndex->mp[bucketValue]);
                return indexhashIndex->mp[bucketValue];
        }else{// not found then look for the overflow block
            if(indexhashIndex->nextAddr!=0){// if there is a overflow block
                 BufferFrame*frame=manager->requestPageForRead(indexhashIndex->nextAddr);//只读
                 HashIndex*hashIndex=new HashIndex();
                transFrameToHashIndex(frame,hashIndex);
                manager->finishRead(frame);
                return findBucketByValue(bucketValue,hashIndex);//load the over flow block
            }
        }
     }
     Addr PrimaryHashIndex::updateHashIndexMeta(long long bucketSize,short hashSize,long long recordSize,Addr addr){
            if(addr!=0){// if there is a overflow block
                 BufferFrame*frame=manager->requestPageForWrite(addr,false);//
                 HashIndex*hashIndex=new HashIndex();
                transFrameToHashIndex(frame,hashIndex);
                hashIndex->bucketSize=bucketSize;
                hashIndex->hashSize=hashSize;
                hashIndex->recordSize=recordSize;
                //keySize=keySize;
                //printf("hashIndex:: %d",this->hashIndex->nextAddr);
                transHashIndexToFrame(hashIndex,frame);
                frame->edit=true;
                this->manager->finishWrite(frame);
                updateHashIndexMeta(bucketSize,hashSize,recordSize,hashIndex->nextAddr);//load the over flow block
            }
     }
    void PrimaryHashIndex::HashIndexSplit(){
        long long value=this->hashIndex->bucketSize-1;
        long long bucketValue=this->hashIndex->bucketSize-1;
        updateHashIndexMeta(this->hashIndex->bucketSize,this->hashIndex->hashSize,this->hashIndex->recordSize,this->indexRootAddr);
        value=value-(long long)pow(2,this->hashIndex->hashSize-1);
        // printf("value and bucketvalue ::%d %d",value,bucketValue);
         Addr addr=findBucketByValue(value,this->hashIndex);
        map<unsigned long long,vector<Addr> >mp;
        transBucketItem(addr,bucketValue,mp);//split the bucketItem
        addr=findPageToWrite(bucketValue,this->indexRootAddr,this->hashIndex);
        insertMultiBucketItems(addr,mp);
    }
//    void PrimaryHashIndex::splitBucket(uint bucketValue,Addr addr){
//
//    }
    void PrimaryHashIndex:: insertMultiBucketItems(Addr addr,map<unsigned long long,vector<Addr> >dataMap){
           //printf("begin insert multiBucket Items");
           BufferFrame*frame=manager->requestPageForWrite(addr,false);
           HashIndexItem*hashIndexItem=new HashIndexItem();
           transFrameToHashIndexItem(hashIndexItem,frame);
           map<unsigned long long,vector<Addr> >::iterator it=dataMap.begin();
           bool flag=false;
           int cnt=0;
           while(it!=dataMap.end()){
                if(hashIndexItem->KeyNum<PrimaryHashIndex::INDEX_ITEM_SIZE){
                        for(int i=0;i<it->second.size();i++){
                            hashIndexItem->mp[it->first].push_back(it->second[i]);
                            hashIndexItem->KeyNum++;
                            if(hashIndexItem->KeyNum==PrimaryHashIndex::INDEX_ITEM_SIZE){
                                cnt=i;
                                flag=true;
                                break;
                            }
                        }
                }
                if(flag) break;
                it++;
           }
           if(flag){
                bool tag=false;
                map<unsigned long long,vector<Addr> >mymap;
                 while(it!=dataMap.end()){
                        if(!tag){
                                for(int i=cnt+1;i<it->second.size();i++){
                                    mymap[it->first].push_back(it->second[i]);
                                }
                                tag=true;
                        }else{
                                for(int i=0;i<it->second.size();i++){
                                    mymap[it->first].push_back(it->second[i]);
                                }
                        }
                        it++;
                 }
                if(hashIndexItem->nextAddr==0){
                        hashIndexItem->nextAddr=createBucket();
                        transHashIndexItemToFrame(hashIndexItem,frame);
                        frame->edit=true;
                        manager->finishWrite(frame);
                        insertMultiBucketItems(hashIndexItem->nextAddr,mymap);
                }else{
                        transHashIndexItemToFrame(hashIndexItem,frame);
                        frame->edit=true;
                        manager->finishWrite(frame);
                        insertMultiBucketItems(hashIndexItem->nextAddr,mymap);
                }
           }
           transHashIndexItemToFrame(hashIndexItem,frame);
           frame->edit=true;
           manager->finishWrite(frame);
           /*
           Page*page=frame->page;
           Byte*data=page->data;
            data+=PAGE_HEAD_LEN;
            data+=PAGE_ALIGN;
            Byte*old=data;
            int keynum;
            Byte*keyNumPtr=data;
            memcpy(&keynum,data,sizeof(int));//num of item 4 Bytes
            data+=sizeof(int);
            Byte*addrPtr=data;
            memcpy(&addr,data,sizeof(long long));//second next addr 8 Bytes
            data+=sizeof(long long);
            data+=PrimaryHashIndex::BUCKET_ITEM_SIZE*keynum;
            map<void*,vector<Addr> >::iterator it=dataMap.begin();
            while(it!=dataMap.end()&&keynum<PrimaryHashIndex::INDEX_ITEM_SIZE){
                for(int i=0;i<it->second.size();i++){
                         memcpy(data,it->first,8);
                         data+=8;
                         memcpy(data,&it->second[i],sizeof(Addr));
                         data+=sizeof(Addr);
                         keynum++;
                }
               //printf("%d%d\n",it->first,it->second.size());
                it++;
            }
            memcpy(keyNumPtr,&keynum,sizeof(int));
            if(it!=dataMap.end()&&keynum==PrimaryHashIndex::INDEX_ITEM_SIZE){
                 if(addr==0){
                    addr=createBucket();
                    memcpy(data,&addr,sizeof(Addr));
                 }
                    map<void*,vector<Addr> >mp;
                     while(it!=dataMap.end()){
                         mp[it->first]=it->second;
                         it++;
                    }
                    frame->edit=true;
                    manager->finishWrite(frame);
                    insertMultiBucketItems(addr,mp);
            }
            frame->edit=true;
            this->manager->finishWrite(frame);*/
           // printf("finish insert item!");
    }
    static long long getHashValue(unsigned long long key){
        Byte data[8];
        memcpy(data,&key,8);
        long long  hashValue=0;
        int cnt=0;
        int factor[16];
        int round=3;
        for(int i=0;i<16;i++){
            if(i==0) factor[i]=1;
            else{
                factor[i]=round;
                round=round*3;
            }
        }
        for(int i=0;i<8;i++){//hashvalue the sum of bytes
            Byte myByte=data[i];
            hashValue+=(myByte&15)*factor[cnt++];
            //printf("%d\n",hashValue);
            myByte=data[i];
            hashValue+=(myByte>>4)*factor[cnt++];
            //printf("%d\n",hashValue);
        }
        return hashValue;
    }
    void PrimaryHashIndex::getAllBucketItem(Addr addr,map<unsigned long long,vector<Addr> >&mp){
            BufferFrame*frame=manager->requestPageForRead(addr);
            HashIndexItem* hashIndexItem=new HashIndexItem();
            transFrameToHashIndexItem(hashIndexItem,frame);
            map<unsigned long long,vector<Addr> >::iterator it;
            it=hashIndexItem->mp.begin();
            while(it!=hashIndexItem->mp.end()){
                for(int i=0;i<it->second.size();i++){
                    mp[it->first].push_back(it->second[i]);
                }
                it++;
            }
            manager->finishRead(frame);
            this->drs->freeBlock(addr);
            if(hashIndexItem->nextAddr!=0){
                getAllBucketItem(hashIndexItem->nextAddr,mp);
            }
    }
     void PrimaryHashIndex::transBucketItem(Addr addr,long long value,map<unsigned long long,vector<Addr> >&mp){
    BufferFrame*frame=manager->requestPageForWrite(addr,false);
    HashIndexItem* hashIndexItem=new HashIndexItem();
    transFrameToHashIndexItem(hashIndexItem,frame);
    map<unsigned long long,vector<Addr> >::iterator it;
    it=hashIndexItem->mp.begin();
    while(it!=hashIndexItem->mp.end()){
        long long hashValue=getHashValue(it->first);
        if(hashValue&value==value){
             for(int i=0;i<it->second.size();i++){
                  mp[it->first].push_back(it->second[i]);
             }
             hashIndexItem->KeyNum--;
            hashIndexItem->mp.erase(it);
        }
        it++;
    }
    transHashIndexItemToFrame(hashIndexItem,frame);
    frame->edit=true;
    manager->finishWrite(frame);
    if(hashIndexItem->nextAddr!=0){
        transBucketItem(hashIndexItem->nextAddr,value,mp);
    }
    /*
    Page*page=frame->page;
    Byte*data=page->data;
    ushort flag=page->flag;
    flag=flag&(~SegmentType::mask)|SegmentType::IndexSeg&(~PageStatus::mask)|PageStatus::FullPage;
    page->flag=flag;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
    Byte*old=data;
    memcpy(&hashIndexItem->KeyNum,data,sizeof(int));//num of item 4 Bytes
    data+=sizeof(int);
    memcpy(&hashIndexItem->nextAddr,data,sizeof(Addr));//second next addr 8 Bytes
    data+=sizeof(Addr);
    void*key;
    Addr addr;
    map<void*,vector<Addr> >mp;
    map<void*,vector<Addr> >mpstay;
    printf("begin trans item keynum %d\n",hashIndexItem->KeyNum);
     for(int i=0;i<hashIndexItem->KeyNum;i++){
         memcpy(key,data,8);
         data+=8;
         memcpy(&addr,data,sizeof(Addr));
         data+=sizeof(Addr);
        long long hashvalue=getHashValue(key);
        printf("hashvalue value::%d %d\n",hashvalue,value);
        if(hashvalue&value==value){
            mp[key].push_back(addr);
            hashIndexItem->KeyNum--;
            printf("%d %d\n",key,addr);
        }else{
            mpstay[key].push_back(addr);
        }
    }
    map<void*,vector<Addr> >::iterator it=mpstay.begin();
    data=old;
    data+=12;
    while(it!=mpstay.end()){
        for(int i=0;i<it->second.size();i++){
                memcpy(data,it->first,8);
                data+=8;
                memcpy(data,&it->second[i],sizeof(Addr));
                data+=sizeof(Addr);
        }
        it++;
    }*/
  //  printf("map size:: %d  %d\n",mp.size(),mpstay.size());
    //return mp;
}
Addr PrimaryHashIndex::deleteElem(IndexItem* item)
{
        BufferFrame*frame=this->manager->requestPageForWrite(this->indexRootAddr,false);
     //   hashIndex* hashIndex=new HashIndex();
        transFrameToHashIndex(frame,this->hashIndex);
        long long bucketValue=getBucketValue(item->key,this->hashIndex->hashSize,this->hashIndex->bucketSize);
        Addr addr=findPageToWrite(bucketValue,this->indexRootAddr,this->hashIndex);
        deleteBucketItem(addr,item);
        this->hashIndex->recordSize--;
         if(this->hashIndex->bucketSize>2&&this->hashIndex->recordSize/this->hashIndex->bucketSize<=this->mergeRate){
            //printf("recordsize::%d bucketSize::%d\n hashSize::%d\n",this->hashIndex->recordSize,this->hashIndex->bucketSize,this->hashIndex->hashSize);
            this->hashIndex->bucketSize--;
            if(this->hashIndex->bucketSize<(2<<(this->hashIndex->hashSize-1))){
                this->hashIndex->hashSize--;
            }
            transHashIndexToFrame(this->hashIndex,frame);
             frame->edit=true;
            manager->finishWrite(frame);
            printf("begin to index merge \n");
            HashIndexMerge();
            deleteIndexKey(this->hashIndex->bucketSize,this->indexRootAddr);
          /*  frame=this->manager->requestPageForWrite(this->indexRootAddr,false);
            transFrameToHashIndex(frame,this->hashIndex);
            map<long long ,Addr>::iterator it=this->hashIndex->mp.end();
            it--;
            printf("\ndelete the map item %lld %d %d\n",it->first,it->second,this->hashIndex->mp.size());
            this->hashIndex->mp.erase(it);//delete the bucket from the index directory
            transHashIndexToFrame(this->hashIndex,frame);
            frame->edit=true;
            manager->finishWrite(frame);*/
        }else{
            transHashIndexToFrame(this->hashIndex,frame);
             frame->edit=true;
             manager->finishWrite(frame);
        }

}
void PrimaryHashIndex::deleteIndexKey(long long value,Addr addr){
    BufferFrame* frame=this->manager->requestPageForWrite(addr,false);
    HashIndex*hashIndex=new HashIndex();
    transFrameToHashIndex(frame,hashIndex);
    if(hashIndex->mp.count(value)>=1){
        map<long long ,Addr>::iterator it=hashIndex->mp.find(value);
        if(it!=hashIndex->mp.end()){
            hashIndex->mp.erase(it);
            hashIndex->keySize--;
        }
        transHashIndexToFrame(hashIndex,frame);
        frame->edit=true;
        manager->finishWrite(frame);
    }else{
        frame->edit=false;
        manager->finishWrite(frame);
        if(hashIndex->nextAddr!=0){
            deleteIndexKey(value,hashIndex->nextAddr);
        }
    }

}
void PrimaryHashIndex::HashIndexMerge(){
        long long value=this->hashIndex->bucketSize;
        long long bucketValue=this->hashIndex->bucketSize;
        updateHashIndexMeta(this->hashIndex->bucketSize,this->hashIndex->hashSize,this->hashIndex->recordSize,this->indexRootAddr);
        value=value-(long long)pow(2,this->hashIndex->hashSize);
        // printf("value and bucketvalue ::%d %d",value,bucketValue);
         Addr addr=findBucketByValue(bucketValue,this->hashIndex);
         map<unsigned long long,vector<Addr> >mp;
        //transBucketItem(addr,bucketValue,mp);//split the bucketItem
        getAllBucketItem(addr,mp);
        addr=findPageToWrite(value,this->indexRootAddr,this->hashIndex);
        insertMultiBucketItems(addr,mp);
}
bool PrimaryHashIndex::deleteBucketItem(Addr addr,IndexItem* item){
    unsigned long long mykey=0;
    memcpy(&mykey,item->key,sizeof(unsigned long long));
    BufferFrame*frame=manager->requestPageForWrite(addr,false);
    HashIndexItem*hashIndexItem=new HashIndexItem();
    transFrameToHashIndexItem(hashIndexItem,frame);
    vector<Addr>::iterator it;
    if(hashIndexItem->mp.count(mykey)>0){
        it=(hashIndexItem->mp[mykey]).begin();
          while(it!=(hashIndexItem->mp[mykey]).end()){
                printf("\n*it ...%d  %d\n",*it,item->addr);
                if((*it)==item->addr){
                   (hashIndexItem->mp[mykey]).erase(it);
                   hashIndexItem->KeyNum--;
                   transHashIndexItemToFrame(hashIndexItem,frame);
                   frame->edit=true;
                   manager->finishWrite(frame);
                   break;
               }
               it++;
          }
    }else{
        frame->edit=false;
        manager->finishWrite(frame);
    }
    if(hashIndexItem->nextAddr!=0){
        deleteBucketItem(hashIndexItem->nextAddr,item);
    }
}
bool PrimaryHashIndex::deleteBucketItemByKey(Addr addr ,IndexItem*item){
        unsigned long long mykey=0;
        memcpy(&mykey,item->key,sizeof(unsigned long long));
        BufferFrame*frame=manager->requestPageForWrite(addr,false);
        HashIndexItem*hashIndexItem=new HashIndexItem();
        transFrameToHashIndexItem(hashIndexItem,frame);
        if(hashIndexItem->mp.count(mykey)>0){
              hashIndexItem->KeyNum-=hashIndexItem->mp[mykey].size();
              hashIndexItem->mp[mykey].clear();
              frame->edit=true;
              manager->finishWrite(frame);
        }else{
            frame->edit=false;
            manager->finishWrite(frame);
        }
        if(hashIndexItem->nextAddr!=0){
            addr=hashIndexItem->nextAddr;
            deleteBucketItemByKey(addr,item);
        }
}
IndexItem* PrimaryHashIndex::buildItem()
    {
         IndexItem* item = new IndexItem();
        item->key=new Byte[8];
        return item;

    }
void PrimaryHashIndex::releaseIndexItem(IndexItem* item)
    {
         if(item!=0)
            {
                delete[] item->key;
                item->key=0;
            }
            delete item;

    }
void PrimaryHashIndex::releaseAll()
    {
            BufferFrame * frame=manager->requestPageForWrite(this->indexRootAddr,false);
            transHashIndexToFrame(this->hashIndex,frame);
            frame->edit=true;
            manager->finishWrite(frame);
    }
      Addr PrimaryHashIndex::getRootAddr()
     {
        return this->indexRootAddr;
     }
     Addr PrimaryHashIndex::getNextAddr(){
        return this->nextAddr;
     }
void PrimaryHashIndex::flushHashIndex(){
    if(hashIndex==0){
        return ;
    }
    BufferFrame*frame=manager->requestPageForWrite(this->indexRootAddr,false);
    transHashIndexToFrame(this->hashIndex,frame);
    frame->edit=true;
    manager->finishWrite(frame);
}
short PrimaryHashIndex::transHashIndexToFrame(HashIndex*hashIndex,BufferFrame *frame)
{
    Page*page=frame->page;
    Byte*data=page->data;
    //page->usedByte=this->indexType;
    //page->usedLen=0;
    //page->usedByteList[0]
    //how to set usedByteList
    ushort flag=page->flag;
    flag=flag&(~SegmentType::mask)|SegmentType::IndexSeg&(~PageStatus::mask)|PageStatus::FullPage;
    page->flag=flag;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
    Byte* old=data;
    memcpy(data,&hashIndex->bucketSize,sizeof(long long));//first bucketsize 8 Bytes
    data+=sizeof(long long);
    memcpy(data,&hashIndex->hashSize,sizeof(short));//second hashsize 2Bytes
    data+=sizeof(short);
    memcpy(data,&hashIndex->recordSize,sizeof(long long));//third recordSize 8 Bytes
    data+=sizeof(long long);
    memcpy(data,&hashIndex->splitRate,sizeof( float));//fourth split rate
    //printf("the splitRate :: %d   \n",hashIndex->splitRate);
    data+=sizeof(float);
    memcpy(data,&hashIndex->keySize,sizeof(short));// fifth keySize 2Bytes
    data+=sizeof(short);
    memcpy(data,&hashIndex->nextAddr,sizeof(Addr));//sixth  overflow block addr 8Bytes
    data+=sizeof(Addr);
    //printf("%d",data-old);
    map<long long,Addr>::iterator it;
    it=hashIndex->mp.begin();
    while(it!=hashIndex->mp.end()){
        memcpy(data,&it->first,sizeof(long long));
        data+=sizeof(long long);
        memcpy(data,&it->second,sizeof(Addr));
        data+=sizeof(Addr);
        it++;
    }
    return data-old;
}
short PrimaryHashIndex::transFrameToHashIndex(BufferFrame*frame,HashIndex*hashIndex){
    Page*page=frame->page;
    ushort flag=page->flag&SegmentType::mask;
    if(flag!=SegmentType::IndexSeg){
        #ifdef DEBUG_INDEX
        printf("warning: this page is not a index segment page");
        #endif // DEBUG_INDEX
    }
    Byte*data=page->data;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
    Byte*old=data;
    memcpy(&hashIndex->bucketSize,data,sizeof(long long));//first bucketsize 8 Bytes
    data+=sizeof(long long);
    memcpy(&hashIndex->hashSize,data,sizeof(short));//second hashsize 2 Bytes
    data+=sizeof(short);
    memcpy(&hashIndex->recordSize,data,sizeof(long long));//third recordSize 8 Bytes
    data+=sizeof(long long);
    memcpy(&hashIndex->splitRate,data,sizeof( float));//fourth split rate 4byte
    data+=sizeof(float);
    memcpy(&hashIndex->keySize,data,sizeof(short));// fifth keySize 2Bytes
    data+=sizeof(short);
    memcpy(&hashIndex->nextAddr,data,sizeof(long long));//sixth  overflow block addr 8Bytes
    data+=sizeof(long long);
    long long key=0;
   Addr addr=0;
   hashIndex->mp.clear();
    for(short i=0;i<hashIndex->keySize;i++){
        memcpy(&key,data,sizeof(long long));
        data+=sizeof(long long);
        memcpy(&addr,data,sizeof(Addr));
        //printf("segement::%d %d %d\n",addr,old,data-old);
        data+=sizeof(Addr);
        hashIndex->mp[key]=addr;
    }
    return data-old;
}
Byte PrimaryHashIndex::getIndexType()
{
    return IndexType::hashidx;
}
short PrimaryHashIndex::insertBucketItem(Addr pageAddres, Addr address, unsigned long long key){
        //printf("begin to insert the item keySize\n");
        if(key==31205930107) printf("find the key ..........\n");
         BufferFrame* frame=this->manager->requestPageForWrite(pageAddres,false);
         HashIndexItem* hashIndexItem=new HashIndexItem();
         transFrameToHashIndexItem(hashIndexItem,frame);
         if(hashIndexItem->KeyNum==PrimaryHashIndex::INDEX_ITEM_SIZE){
               if(hashIndexItem->nextAddr==0){
                  // printf("begin to create a new bucket!");
                    hashIndexItem->nextAddr=createBucket();
                    transHashIndexItemToFrame(hashIndexItem,frame);
                    frame->edit=true;
                    manager->finishWrite(frame);
                    insertBucketItem(hashIndexItem->nextAddr,address,key);
               }else{
                      frame->edit=false;
                      manager->finishWrite(frame);
                      insertBucketItem(hashIndexItem->nextAddr,address,key);
               }
         }else{
                //printf("fuck the item %lld !\n",pageAddres);
                hashIndexItem->KeyNum++;
                hashIndexItem->mp[key].push_back(address);
                transHashIndexItemToFrame(hashIndexItem,frame);
                frame->edit=true;
                manager->finishWrite(frame);
         }
         //for(int i=0;i<10;i++)putchar('k');
         /*Page*page=frame->page;
         Byte*data=page->data;
         data+=PAGE_HEAD_LEN;
         data+=PAGE_ALIGN;
         int keyNum;
         memcpy(&keyNum,data,sizeof(int));
for(int i=0;i<10;i++)putchar('b');
         if(keyNum==PrimaryHashIndex::INDEX_ITEM_SIZE){
                for(int i=0;i<10;i++)putchar('c');
                Addr addr=createBucket();
                data+=sizeof(int);//skip the keyNum
                memcpy(data,&addr,sizeof(Addr));
                frame->edit=true;
                manager->finishWrite(frame);
                insertBucketItem(addr,address,key);
         for(int i=0;i<10;i++)putchar('d');
        }else{
            for(int i=0;i<10;i++)putchar('e');
//            frame->edit=true;
//            this->manager->finishWrite(frame);
            //frame=this->manager->requestPageForWrite(pageAddres,false);
            HashIndexItem*hashIndexItem=new HashIndexItem();
            transFrameToHashIndexItem(hashIndexItem,frame);
            hashIndexItem->mp[key].push_back(address);
            hashIndex
            transHashIndexItemToFrame(hashIndexItem,frame);
            frame->edit=true;
            this->manager->finishWrite(frame);
            for(int i=0;i<10;i++)putchar('f');
        }*/
        return 1;
}
Addr PrimaryHashIndex::createBucket(){
            Addr root=this->drs->allocateBlock(SegmentType::IndexSeg,PageStatus::HalfPage);
            BufferFrame* frame=this->manager->requestPageForWrite(root,false);
            HashIndexItem *hashIndexItem=new HashIndexItem();
            hashIndexItem->nextAddr=0;
            hashIndexItem->KeyNum=0;
            transHashIndexItemToFrame(hashIndexItem,frame);
            frame->edit=true;
            this->manager->finishWrite(frame);
            return root;
}
short PrimaryHashIndex::transHashIndexItemToFrame(HashIndexItem*hashIndexItem,BufferFrame*frame){
    Page*page=frame->page;
    Byte*data=page->data;
    ushort flag=page->flag;
    flag=flag&(~SegmentType::mask)|SegmentType::IndexSeg&(~PageStatus::mask)|PageStatus::FullPage;
    page->flag=flag;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
     Byte*old=data;
     memcpy(data,&hashIndexItem->KeyNum,sizeof(int));//num of item 4 Bytes
      data+=sizeof(int);
      memcpy(data,&hashIndexItem->nextAddr,sizeof(Addr));//second next addr 8 Bytes
     data+=sizeof(Addr);
      map<unsigned long long,vector<Addr> >::iterator it;
     it=hashIndexItem->mp.begin();
     while(it!=hashIndexItem->mp.end()){
         for(int i=0;i<it->second.size();i++){
             memcpy(data,&it->first,8);
             data+=8;
             memcpy(data,&it->second[i],sizeof(Addr));
            data+=sizeof(Addr);
         }
         it++;
    }
    return data-old;
}
short PrimaryHashIndex::transFrameToHashIndexItem(HashIndexItem*hashIndexItem,BufferFrame*frame){
    Page*page=frame->page;
    Byte*data=page->data;
    ushort flag=page->flag;
    flag=flag&(~SegmentType::mask)|SegmentType::IndexSeg&(~PageStatus::mask)|PageStatus::FullPage;
    page->flag=flag;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
     Byte*old=data;
     memcpy(&hashIndexItem->KeyNum,data,sizeof(int));//num of item 4 Bytes
      data+=sizeof(int);
      memcpy(&hashIndexItem->nextAddr,data,sizeof(Addr));//second next addr 8 Bytes
     data+=sizeof(Addr);
     unsigned long long key;
    Addr addr;
    hashIndexItem->mp.clear();
    for(int i=0;i<hashIndexItem->KeyNum;i++){
        memcpy(&key,data,8);
        data+=8;
        memcpy(&addr,data,sizeof(Addr));
        data+=sizeof(Addr);
        hashIndexItem->mp[key].push_back(addr);
    }
    return data-old;
}
