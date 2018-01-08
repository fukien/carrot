#include "BPTree.h"
#include "../segment/IndexSegment.h"
#include "../util/DataUtil.h"
void BPTree::BPTIterator::findFirst(IndexItem* item)
{
    //假定第一个地址都是有效的
    if(knownEmpty)return ;
    if(this->currentNode==0)this->currentNode = new BPTNode();
    this->cursor  = head;
    tree->getBPTNode(currentNode ,this->begin);
    if(this->cursor>=currentNode->keyNum)
    {
        if(this->currentNode->next!=0)
         {
             tree->getBPTNode(this->currentNode,this->currentNode->next);
             this->cursor=0;
         }
         else
         {
             return ;
         }
    }
    memcpy(item->key,currentNode->keys[this->cursor],8);
    item->addr = currentNode->children[this->cursor++];
    printf("reached here! addr = %llx\n",item->addr);
}
void BPTree::BPTIterator::findNext(IndexItem* item)
{
        if(knownEmpty)return ;
    if(currentNode->pageNo==PAGE_ID(this->end)&&this->cursor>=tail)
    {
        return ;
    }
    if(this->cursor>=this->currentNode->keyNum)
    {
         if(this->currentNode->next!=0)
         {
             tree->getBPTNode(this->currentNode,this->currentNode->next);
             this->cursor=0;
         }
         else
         {
             return ;
         }
    }
    memcpy(item->key,currentNode->keys[this->cursor],8);
    item->addr = currentNode->children[this->cursor++];
}
bool BPTree::BPTIterator::hasNext()
{
    // not fully implement!
    if(knownEmpty)return false;
    if(currentNode->pageNo==PAGE_ID(this->end)&&this->cursor>=tail)
    {
        return false;
    }
    if(this->cursor>=this->currentNode->keyNum&&this->currentNode->next<=0)return false;
    return true;
}
BPTree::BPTIterator::BPTIterator(Addr addr1,int offset1,Addr addr2,int offset2,BPTree* bptree)
{
    knownEmpty = false;
    this->begin = addr1;
    this->cursor=0;
    this->head = offset1;
    this->end = addr2;
    this->tail = offset2;
    this->currentNode = 0;
    this->cursor=offset1;
    #ifdef DEBUG_INDEX
        printf("construct an iterator with begin %llx offset %d end %llx offset %d\n",begin,head,end,tail);
    #endif // DEBUG_INDEX
    this->tree = bptree;
    if(this->tree->indexRootAddr==end&&tail<=0)
    {
        knownEmpty = true;
    }
}
BPTree::BPTIterator::~BPTIterator()
{
    if(this->currentNode!=0)
    {
        delete currentNode;
        currentNode = 0;
    }
}
BPTree::BPTree(IndexSegment* idx,Byte fid,Addr addr,IndexMetaItem* itm):Index(idx,fid,addr),item(itm)
{
    cnt= 0;
    splitTime = 0;
    created= false;loaded=false;
    this->root = 0;
    this->dataType = this->mts->getMetaData()->head->fieldList[fid].dataType;
    if(this->indexRootAddr==0)
    {
        this->indexRootAddr = this->drs->allocateBlock(SegmentType::IndexSeg,PageStatus::FullPage);
        this->root = 0;
        create();

    }else
    {
        load();
    }
}
void BPTree::create()
{
    if(!created)
    {
        BufferFrame* frame = this->manager->requestPageForWrite(this->indexRootAddr,false);
        if(this->root!=0)delete root;
        this->root = new BPTNode();
        root->fid = this->fieldId;
        root->nodeType=BPTNodeType::hasData|BPTNodeType::isRoot;
        root->keyNum=0;
        root->parentAddr=0;
        root->previous=0;
        root->next=0;
        root->pageNo = frame->pageNo;
        transNodeToFrame(root,frame);
        frame->edit = true;
        this->manager->finishWrite(frame);
        Tuple* tuple = this->dts->buildEmptyTuple();
        IndexItem* item = this->buildItem();
        this->dts->findFirstTuple(tuple);
       // int cnt = 0;
        while(tuple->tupleAddr>0)
        {
            cnt++;
                Addr old = tuple->tupleAddr;
                item->addr = old;
                memcpy(item->key,tuple->column[this->fieldId].data,this->indexLen);
                this->insertElem(item,false);
                this->dts->findNextTuple(tuple,tuple);
                if(tuple->tupleAddr==old)
                {
                        break;
                }
            if(cnt==300)
            {
                //this->printNode(root);
                //this->printTreeBFS();
                //getchar();
            }
        }
                       this->printTreeBFS();
                  //  getchar();
        this->releaseIndexItem(item);
        item = 0;
        this->dts->releaseEmptyTuple(tuple);
        created = true;
        loaded = true;
    }
}
void BPTree::load()
{
    if(!loaded)
    {
        if(this->root!=0)delete root;
        this->root = new BPTNode();
        BufferFrame* frame = manager->requestPageForRead(this->indexRootAddr);
        int read = transFrameToNode(frame,root);
        manager->finishRead(frame);
        if(read<=32)
        {
            delete this->root;
            this->root=0;
            create();
        }
        created = true;
        loaded = true;
    }
}
void BPTree::destroyMySelf()
{

}
IndexIterator* BPTree::findByKey(void* key)
{
    Byte data[8];
    char chr[255];
    memcpy(data,key,this->indexLen);

    BPTNode* node = new BPTNode();
    searchBPTNode(node,data);
    int pos2 = findUpBound(data,node);
    pos2++;
    Addr addr2 = PAGE_ADDR(node->pageNo);
    searchBPTNode2(node,data);
    int pos1 = findLowBound(data,node);
    Addr addr1 = PAGE_ADDR(node->pageNo);
    delete node;node = 0;
    return new BPTree::BPTIterator(addr1,pos1,addr2,pos2,this);
}
IndexIterator* BPTree::findByRange(void* key1,void* key2){

    int jd = DataUtil::cmpData(reinterpret_cast<Byte*>(key1),reinterpret_cast<Byte*>(key2),this->dataType,this->indexLen);
    if(jd>0)
    {
        void* b = key1;
        key1 = key2;
        key2 = b;
    }
    Byte data[8];
    memcpy(data,key2,this->indexLen);
    BPTNode* node = new BPTNode();
    searchBPTNode(node,data);
    int pos2 = findUpBound(data,node);
    pos2++;
    if(this->dataType==DataTypeFlag::FLOAT)
    {
       // printf("pos2 offset = %d\n",pos2);
    }
    Addr addr2 = PAGE_ADDR(node->pageNo);
    memcpy(data,key1,this->indexLen);
    searchBPTNode2(node,data);
    int pos1 = findLowBound(data,node);
    Addr addr1 = PAGE_ADDR(node->pageNo);
    delete node;
    return new BPTree::BPTIterator(addr1,pos1,addr2,pos2,this);
}
void BPTree::destoryIterator(IndexIterator* iterator){
    delete iterator;
}
int BPTree::insertNonLeafAtPos(IndexItem* item,BPTNode* node,int pos)
{
    int keyNum = node->keyNum;
    if(keyNum>=MAX_KEY_SIZE)keyNum=MAX_KEY_SIZE-1;
    for(int i=keyNum;i>pos;i--)
    {
        memcpy(node->keys[i],node->keys[i-1],8);
        node->children[i+1]=node->children[i];
    }
    memcpy(node->keys[pos],item->key,8);
    node->children[pos+1]=item->addr;
    node->keyNum++;
}
int BPTree::insertElemAtPos(IndexItem* item,BPTNode* node,int pos)
{
    int keyNum = node->keyNum;
    if(keyNum>=MAX_KEY_SIZE)keyNum=MAX_KEY_SIZE-1;
    for(int i=keyNum;i>pos;i--)
    {
        memcpy(node->keys[i],node->keys[i-1],8);
        node->children[i]=node->children[i-1];
    }
    memcpy(node->keys[pos],item->key,8);
    node->children[pos]=item->addr;
    node->keyNum++;
}
Addr BPTree::getNewBPTNode(BPTNode* node,Byte nodeType)
{
        Addr addr = drs->allocateBlock(SegmentType::IndexSeg,PageStatus::FullPage);
        BufferFrame* frame = this->manager->requestPageForWrite(addr,false);
//        BPTNode* node = new BPTNode();
        node->fid = this->fieldId;
        node->nodeType=nodeType;
        node->keyNum=0;
        node->parentAddr=0;
        node->previous=0;
        node->next=0;
        node->pageNo = frame->pageNo;
        transNodeToFrame(root,frame);
        frame->edit = true;
        this->manager->finishWrite(frame);
        return addr;
}
 void BPTree::getBPTNode(BPTNode* node,Addr addr)
 {
    BufferFrame* frame = this->manager->requestPageForRead(addr);
    if(frame->pageNo==0||addr==0)
    {
        printf("either one is zero %llx %llx\n",frame->pageNo,addr);
    }
    transFrameToNode(frame,node);
    manager->finishRead(frame);
 }
void BPTree::flushNode(BPTNode* node)
{
    if(node->pageNo==0)return;
    BufferFrame* frame = manager->requestPageForWrite(PAGE_ADDR(node->pageNo),false);
    transNodeToFrame(node,frame);
    frame->edit = true;
    manager->finishWrite(frame);
}
void BPTree::nonleafcpy(BPTNode* dest,BPTNode* src,int dest_offset,int src_offset,int len)
{
        for(int i=0;i<len;i++)
    {
        memcpy(dest->keys[dest_offset+i],src->keys[src_offset+i],8);
        dest->children[dest_offset+i]=src->children[src_offset+i];
    }
    dest->children[dest_offset+len]=src->children[src_offset+len];
}
void BPTree::leafcpy(BPTNode* dest,BPTNode* src,int dest_offset,int src_offset,int len)
{
    for(int i=0;i<len;i++)
    {
        memcpy(dest->keys[dest_offset+i],src->keys[src_offset+i],8);
        dest->children[dest_offset+i]=src->children[src_offset+i];
    }
}
Addr BPTree::searchBPTNode(BPTNode* node,Byte* data)
{
    int pos = findUpBound(data,root);
    if((root->nodeType&BPTNodeType::hasData)!=0){
                            #ifdef DEBUG_INDEX
               // printf("visit root1 %llx\n",PAGE_ADDR(root->pageNo));
            #endif // DEBUG_INDEX
         //   printf("1____________________\n");
            getBPTNode(node,PAGE_ADDR(root->pageNo));
            return root->pageNo;
    }
        #ifdef DEBUG_INDEX
        //if(pos+1==root->keyNum)
           //     printf("overflow!!!!!!!!!!!!!!!!!!!!!!!\n");
        #endif // DEBUG_INDEX
    Addr addr = root->children[pos+1];
   // printf("2____________________\n");

    getBPTNode(node,addr);
    node->parentAddr = PAGE_ADDR(root->pageNo);
    flushNode(node);
    Addr parent = PAGE_ADDR(node->pageNo);
    #ifdef DEBUG_INDEX
                //printf("visit node1 %llx\n",PAGE_ADDR(node->pageNo));
            #endif
    while((node->nodeType&BPTNodeType::hasData)==0)
    {

                                #ifdef DEBUG_INDEX
               // printf("visit node1 %llx\n",PAGE_ADDR(node->pageNo));
            #endif // DEBUG_INDEX
            int pos = findUpBound(data,node);
            //寻找大于该值v的前一个元素k, v>=k
            // c[index]<k,c[index+1]>=k
            // 当v>k时，取index+1
            //当v=k时，取index+1
                    #ifdef DEBUG_INDEX
//    if(pos+1==root->keyNum)
   //             printf("overflow2!!!!!!!!!!!!!!!!!!!!!!!\n");
        if(node->children[pos+1]<PAGE_SIZE)
        {
            printNode(node);
        }
        #endif // DEBUG_INDEX
            Addr addr = node->children[pos+1];
     //       printf("3____________________\n");
            getBPTNode(node,addr);
            node->parentAddr = parent;
            flushNode(node);
            parent = PAGE_ADDR(node->pageNo);
    }

    if((node->nodeType&BPTNodeType::hasData)!=0)
    {
                                        #ifdef DEBUG_INDEX
              //  printf(" node type1 %llx\n",node->nodeType);
            #endif // DEBUG_INDEX
    }
    return node->pageNo;
}//todo
Addr BPTree::searchBPTNode2(BPTNode* node,Byte* data)
{
    int pos = findLowBound(data,root);
                #ifdef DEBUG_INDEX
          //      printf("visit root %llx\n",PAGE_ADDR(root->pageNo));
            #endif // DEBUG_INDEX
    //pos 位置的元素k, k>data或k=data
    if((root->nodeType&BPTNodeType::hasData)!=0){
            #ifdef DEBUG_INDEX
                printf("root has Data\n");;
            #endif // DEBUG_INDEX
       //     printf("4____________________\n");
            getBPTNode(node,PAGE_ADDR(root->pageNo));
            return root->pageNo;
    }
    if(DataUtil::cmpData(data,root->keys[pos],this->dataType,this->indexLen)==0)pos++;
    Addr addr = root->children[pos];
   // printf("5____________________\n");
    getBPTNode(node,addr);
    node->parentAddr = PAGE_ADDR(root->pageNo);
    flushNode(node);
    Addr parent = PAGE_ADDR(node->pageNo);

    while((node->nodeType&BPTNodeType::hasData)==0)
    {
                        #ifdef DEBUG_INDEX
               // printf("visit node %llx\n",PAGE_ADDR(node->pageNo));
            #endif // DEBUG_INDEX
            int pos = findLowBound(data,node);
            if(DataUtil::cmpData(data,node->keys[pos],this->dataType,this->indexLen)==0)pos++;
            //寻找不小于该值v的后一个元素k, k>=v
            // c[index]<k,c[index+1]>=k
            // 当v<k时，取index
            //当v=k时，取index+1
            Addr addr = node->children[pos];
      //      printf("6____________________\n");
            getBPTNode(node,addr);
            node->parentAddr = parent;
            flushNode(node);
            parent = PAGE_ADDR(node->pageNo);
    }
        if((node->nodeType&BPTNodeType::hasData)!=0)
    {
                                        #ifdef DEBUG_INDEX
              //  printf(" node type %llx\n",node->nodeType);
            #endif // DEBUG_INDEX
    }
    return node->pageNo;
}
void BPTree::insertNodeRecursively(Addr addr,IndexItem* item)
{
    BPTNode* node = new BPTNode();
        //    printf("7____________________\n");
    getBPTNode(node,addr);
    if((node->nodeType&BPTNodeType::hasData)!=0)
    {
                    //分裂
            BPTNode* smaller = node;
            BPTNode* bigger = new BPTNode();
            this->getNewBPTNode(bigger,BPTNodeType::hasData);
            int mid = smaller->keyNum/2;
            int cmpk = DataUtil::cmpData(smaller->keys[mid],reinterpret_cast<Byte*>(item->key),this->dataType,this->indexLen);
            if(cmpk>0)
            {
                //中间项较大，待插入元素较小,[MID-RIGHT]移动到bigger
                int mlen =  smaller->keyNum-mid;
                leafcpy(bigger,smaller,0,mid,mlen);
                smaller->keyNum = mid;
                bigger->keyNum=mlen;
                int pos = findUpBound(reinterpret_cast<Byte*>(item->key),smaller);
                insertElemAtPos(item,smaller,pos+1);
            }else
            {
                //中间项较小，待插入元素较大,[MID+1-RIGHT]移动到bigger
                int mlen = smaller->keyNum-mid-1;
                leafcpy(bigger,smaller,0,mid+1,mlen);
                smaller->keyNum=mid+1;
                bigger->keyNum=mlen;
                int pos = findUpBound(reinterpret_cast<Byte*>(item->key),bigger);
                insertElemAtPos(item,bigger,pos+1);
            }
            bigger->next=smaller->next;
            smaller->next = PAGE_ADDR(bigger->pageNo);
            bigger->previous= PAGE_ADDR(smaller->pageNo);
            bigger->parentAddr=smaller->parentAddr;
            if(bigger->next!=0)
            {
                BPTNode* tmp = new BPTNode();
        //        printf("8____________________\n");
                getBPTNode(tmp,bigger->next);
                tmp->previous=PAGE_ADDR(bigger->pageNo);
                flushNode(tmp);
                delete tmp;
            }
            flushNode(bigger);
            flushNode(smaller);

            IndexItem* newItem = this->buildItem();
            #ifdef DEBUG_INDEX
                        char chr[255];
        DataUtil::toString(chr,bigger->keys[0],this->dataType);
            //printf("insert upward %s\n",chr);
            #endif // DEBUG_INDEX
            memcpy(newItem->key,bigger->keys[0],8);
            newItem->addr=smaller->next;
                        delete bigger;
            insertNodeRecursively(smaller->parentAddr,newItem);
            this->releaseIndexItem(newItem);
            delete node;
    }else
    {
        BPTNode* tmpNode = node;
        if(this->indexRootAddr==PAGE_ADDR(node->pageNo))tmpNode = root;
        if(tmpNode->keyNum<MAX_KEY_SIZE)
        {
            int pos = findUpBound(reinterpret_cast<Byte*>(item->key),tmpNode);
            insertNonLeafAtPos(item,tmpNode,pos+1);
            flushNode(tmpNode);
        }else
        {
         //   printf("before split\n");
           // this->printNode(tmpNode);
            BPTNode* smaller = tmpNode;
            BPTNode* bigger = new BPTNode();
            this->getNewBPTNode(bigger,0);
            int pos = findUpBound(reinterpret_cast<Byte*>(item->key),smaller);
            //先插入 后分裂
            Byte bigKey[8];
            Addr bigAddr;
            memcpy(bigKey,smaller->keys[smaller->keyNum-1],8);
            bigAddr = smaller->children[smaller->keyNum];
            Addr a0 = smaller->children[0];
            insertNonLeafAtPos(item,tmpNode,pos+1);
            smaller->children[0]=a0;
         //       printf("after insert pos %d addr %llx\n",pos,item->addr);
            //this->printNode(tmpNode);
            int num = (smaller->keyNum+1)/2;
            int mlen = smaller->keyNum-num-1;
            nonleafcpy(bigger,smaller,0,num+1,mlen);
            smaller->keyNum= num;
            bigger->keyNum=num-1;
            memcpy(bigger->keys[bigger->keyNum-1],bigKey,8);
            bigger->children[bigger->keyNum]=bigAddr;
            IndexItem* newItem = this->buildItem();
            memcpy(newItem->key,smaller->keys[num],8);
            newItem->addr=PAGE_ADDR(bigger->pageNo);
            bigger->parentAddr =smaller->parentAddr;
            flushNode(smaller);
            flushNode(bigger);
            printf("after split %d\n",splitTime++);
        //    this->printNode(smaller);
          //  this->printNode(bigger);
            if(smaller->parentAddr!=0)
            {
                           delete bigger;
                insertNodeRecursively(smaller->parentAddr,newItem);
            }else
            {
                                                    //   this->printTreeBFS();
                    //getchar();
                BPTNode* oldrt = root;
                 BPTNode* rt = new BPTNode();
                this->getNewBPTNode(rt,BPTNodeType::isRoot);
                smaller->parentAddr=PAGE_ADDR(rt->pageNo);
                bigger->parentAddr=smaller->parentAddr;
                smaller->nodeType=0;
                flushNode(smaller);
                flushNode(bigger);
                rt->keyNum=1;
                memcpy(rt->keys[0],smaller->keys[num-1],8);
                rt->children[0]=PAGE_ADDR(smaller->pageNo);
                rt->children[1]=PAGE_ADDR(bigger->pageNo);

                flushNode(rt);
                changeRoot(rt);
                                     //  this->printTreeBFS();
                   // getchar();
               // printf("rec change!\n");
                delete oldrt;
                delete bigger;
            }
        }
        delete node;
    }
}
void BPTree::printNode(BPTNode* node)
{
    for(int i=0;i<50;i++)
    {
        printf("_");
    }
    printf("\n");
    printf("%llx node info: nodeType:%x parent %llx previous %llx next %llx keyNum %d\n",PAGE_ADDR(node->pageNo),node->nodeType,node->parentAddr,node->previous,node->next,node->keyNum);
    for(int i=0;i<50;i++)
    {
        printf("_");
    }
    char chr[255];
    printf("\n");
    printf("[%llx] ",node->children[0]);
    for(int i=0;i<node->keyNum;i++)
    {
        DataUtil::toString(chr,node->keys[i],this->dataType);
        printf("(%s) ",chr);
        printf("[%llx] ",node->children[i+1]);
        if((i+1)%20==0)printf("\n");
    }
    printf("\n\n\n");
}
void BPTree::printTreeBFS()
{
        std::queue<Addr> que;
        Addr tmp=PAGE_ADDR(root->pageNo);

        que.push(tmp);
        printf("in queue %llx pageNo %llx\n",tmp,root->pageNo);
                    BPTNode* node = new BPTNode();

        while(!que.empty())
        {
            tmp = que.front();
        printf("out queue %llx\n",tmp);
          //  printf("9____________________\n");
            getBPTNode(node,tmp);
            que.pop();
            if((node->nodeType&BPTNodeType::hasData)==0)
            {
                for(int i=0;i<node->keyNum+1;i++)
                {
                    que.push(node->children[i]);
                    printf("in queue %llx parent %llx\n",node->children[i],tmp);
                }
            }
            else
            {
                #ifdef DEBUG_INDEX
                printf("node %llx has data\n",PAGE_ADDR(node->pageNo));
                #endif // DEBUG_INDEX
            }
            printNode(node);
        }
        delete node;
}
void BPTree::changeRoot(BPTNode* node)
{
    this->root = node;
    this->indexRootAddr=PAGE_ADDR(node->pageNo);
    this->item->indexAddr=this->indexRootAddr;
                    #ifdef DEBUG_INDEX
                printf("allocate new root addr %llx\n",PAGE_ADDR(node->pageNo));
                #endif // DEBUG_INDEX
}
Addr BPTree::insertElem(IndexItem* item,bool check){
    if(check)
    {
        // 检查有无重复元素
    }
    if((root->nodeType&BPTNodeType::hasData)!=0)
    {
        if(root->keyNum<MAX_KEY_SIZE)
        {
          // 可以直接插入
          Byte  bkey[8];
          memcpy(bkey,item->key,8);
            int pos = findUpBound(bkey,root);
            #ifdef DEBUG_INDEX
           //char chr[255];
           // DataUtil::toString(chr,bkey,this->dataType);
          //  printf("%s position is %d\n",chr,pos+1);
            #endif // DEBUG_INDEX
            insertElemAtPos(item,root,pos+1);
        }
        else
        {
            //分裂,并产生新根
            BPTNode* smaller = root;
            BPTNode* bigger = new BPTNode();
            this->getNewBPTNode(bigger,BPTNodeType::hasData);
            BPTNode* rt = new BPTNode();
            this->getNewBPTNode(rt,BPTNodeType::isRoot);
            int mid = smaller->keyNum/2;
            int cmpk = DataUtil::cmpData(smaller->keys[mid],reinterpret_cast<Byte*>(item->key),this->dataType,this->indexLen);
            if(cmpk>0)
            {
                //中间项较大，待插入元素较小,[MID-RIGHT]移动到bigger
                int mlen =  smaller->keyNum-mid;
                leafcpy(bigger,smaller,0,mid,mlen);
                smaller->keyNum = mid;
                bigger->keyNum=mlen;
                int pos = findUpBound(reinterpret_cast<Byte*>(item->key),smaller);
                insertElemAtPos(item,smaller,pos+1);
            }else
            {
                //中间项较小，待插入元素较大,[MID+1-RIGHT]移动到bigger
                int mlen = smaller->keyNum-mid-1;
                leafcpy(bigger,smaller,0,mid+1,mlen);
                smaller->keyNum=mid+1;
                bigger->keyNum=mlen;
                int pos = findUpBound(reinterpret_cast<Byte*>(item->key),bigger);
                insertElemAtPos(item,bigger,pos+1);
            }
            rt->keyNum=1;
                        #ifdef DEBUG_INDEX
                        char chr[255];
        DataUtil::toString(chr,bigger->keys[0],this->dataType);
            //printf("insert upward %s\n",chr);
            #endif // DEBUG_INDEX
            memcpy(rt->keys[0],bigger->keys[0],8);
            rt->children[0]=PAGE_ADDR(smaller->pageNo);
            rt->children[1]=PAGE_ADDR(bigger->pageNo);
            smaller->next = PAGE_ADDR(bigger->pageNo);
            bigger->previous= PAGE_ADDR(smaller->pageNo);
            smaller->parentAddr = PAGE_ADDR(rt->pageNo);
            bigger->parentAddr =PAGE_ADDR(rt->pageNo);
            smaller->nodeType=BPTNodeType::hasData;
            changeRoot(rt);
            flushNode(smaller);
            flushNode(bigger);
            flushNode(root);
            delete smaller;
            #ifdef DEBUG_INDEX
            printf("\nbigger %llx\n\n",bigger);
           // this->printTreeBFS();
            #endif // DEBUG_INDEX
            delete bigger;
                        #ifdef DEBUG_INDEX
            printf("\nbigger2 %llx\n\n",bigger);
            #endif // DEBUG_INDEX
        }
    }
    else
    {
        //root非根结点 找到叶子结点，然后插入
        BPTNode* node = new BPTNode();
        searchBPTNode(node,reinterpret_cast<Byte*>(item->key));
        if(node->keyNum<MAX_KEY_SIZE)
        {
            int pos = findUpBound(reinterpret_cast<Byte*>(item->key),node);
            insertElemAtPos(item,node,pos+1);
            flushNode(node);
        }
        else
        {
            insertNodeRecursively(PAGE_ADDR(node->pageNo),item);
            // DIRTY Node:getBPTNode(node,PAGE_ADDR(node->pageNo));
        }

        delete node;
    }
}
// 返回不小于它的第一个元素的index
int  BPTree::findLowBound(Byte* data,BPTNode* node)
{
    /*
        for(int i=0;i<node->keyNum;i++)
       {
           int jd = DataUtil::cmpData(node->keys[i],data,this->dataType,this->indexLen);
           if(jd>=0)return i;
       }
       return node->keyNum;
        */
    int left = 0;
    int right = node->keyNum-1;
    if(right<0)return 0;
    int jd = DataUtil::cmpData(node->keys[left],data,this->dataType,this->indexLen);
    //最小的元素也比它大，返回第一个元素
    if(jd>=0)return left;
    jd = DataUtil::cmpData(node->keys[right],data,this->dataType,this->indexLen);
    //最大的元素也比他小，返回right+1
    if(jd<0)return right+1;
    while(left<=right)
    {
        int mid = (left+right)/2;
        int k = DataUtil::cmpData(node->keys[mid],data,this->dataType,this->indexLen);
        //中间位置小于data
        if(k<0)
        {
            left = mid +1;
        }else
        {
            //中间位置大于等于data
            right = mid-1;
        }
    }
    // 当right<left时，跳出循环
    //  此时:keys[left]>=data,keys[right]<data
    while(left>0)
    {
        int k = DataUtil::cmpData(node->keys[left-1],data,this->dataType,this->indexLen);
        if(k<0)return left;
        left--;
    }
    return left;

}
// 返回大于它的前一个元素的index,也就是当前元素是小于等于它的元素中标号最大者
   int BPTree::findUpBound(Byte* data,BPTNode* node)
   {
        /*
       for(int i=0;i<node->keyNum;i++)
       {
           int jd = DataUtil::cmpData(node->keys[i],data,this->dataType,this->indexLen);
           if(jd>0)return i-1;
       }
       return node->keyNum-1;
       */
          int left = 0;
        int right = node->keyNum-1;
        if(right<0)return right;
        int jd = DataUtil::cmpData(node->keys[left],data,this->dataType,this->indexLen);
        //最小的元素也比它大，返回-1
        if(jd>0)return -1;
        jd = DataUtil::cmpData(node->keys[right],data,this->dataType,this->indexLen);
        //最大的元素也比他小或相等，返回right
        if(jd<=0)return right;
        while(left<=right)
        {
            int mid = (left+right)/2;
            int k = DataUtil::cmpData(node->keys[mid],data,this->dataType,this->indexLen);
            //中间位置小于等于data
            if(k<=0)
            {
                left = mid +1;
            }else
            {
                //中间位置大于data
                right = mid-1;
            }
        }
        //当right<left时，跳出循环，此时key[right]<data
        while(right<node->keyNum-1)
        {
            int k = DataUtil::cmpData(node->keys[right+1],data,this->dataType,this->indexLen);
            if(k>0)return right;
            right++;
        }
        return right;

   }
void BPTree::editItem(Addr addr,IndexItem* item,IndexItem* item2)
{
    BPTNode* node = new BPTNode();
    getBPTNode(node,addr);
    for(int i=0;i<node->keyNum;i++)
    {
        if(node->children[i]==item->addr)
        {
            if(item2!=0)memcpy(item2->key,node->keys[i],this->indexLen);
            memcpy(node->keys[i],item->key,this->indexLen);
        }
    }
    flushNode(node);
    delete node;node = 0;
}

void BPTree::deleteElementFromNode(Addr addr,IndexItem* item)
{
    BPTNode* node = new BPTNode();
    getBPTNode(node,addr);
    int pos = searchBPTNode(node,reinterpret_cast<Byte*>(item->key));
    while(DataUtil::cmpData(node->keys[pos],reinterpret_cast<Byte*>(node,item->key),this->dataType,this->indexLen)==0)
    {
        if(node->children[pos]==item->addr)break;
        pos--;
        if(pos<0)break;
    }
    if(node->children[pos]==item->addr)
    {
        for(int i = pos;i<node->keyNum;i++)
        {
            memcpy(node->keys[i],node->keys[i+1],this->indexLen);
            node->children[i]=node->children[i+1];
        }
        node->keyNum--;
        // if node needn't borrow element, we need flush node.
        // otherwise borrow element and flush.
        //flushNode(node);
        if(node->keyNum<(MAX_KEY_SIZE+1)/2)
        {
            Addr leftAddr = node->previous;
            Addr rightAddr = node->next;
            BPTNode* nodepre = new BPTNode();
            bool leftAvailable = false;
            bool rightAvailable = false;
            if(leftAddr!=0){
                    getBPTNode(nodepre,node->previous);
                    if(nodepre->parentAddr==node->parentAddr)leftAvailable= true;
            }
            if(leftAvailable&&nodepre->keyNum>(MAX_KEY_SIZE+1)/2)
            {
                for(int i = node->keyNum;i>0;i--)
                {
                    memcpy(node->keys[i],node->keys[i-1],this->indexLen);
                    node->children[i]=node->children[i-1];
                }
                memcpy(node->keys[0],nodepre->keys[nodepre->keyNum-1],this->indexLen);
                node->children[0]=nodepre->children[nodepre->keyNum-1];
                node->keyNum++;
                nodepre->keyNum--;
                flushNode(node);
                flushNode(nodepre);
                //TODO: edit parent
                IndexItem* editItem = this->buildItem();
                IndexItem* kitem = this->buildItem();
                memcpy(editItem->key,node->keys[0],this->indexLen);
                editItem->addr = PAGE_ADDR(nodepre->pageNo);
                this->editItem(node->parentAddr,editItem,0);
                this->releaseIndexItem(editItem);
                this->releaseIndexItem(kitem);
            }else
            {
                BPTNode* nodenext = nodepre;
                if(rightAddr!=0){
                        getBPTNode(nodenext,node->next);
                        if(nodenext->parentAddr==node->parentAddr)rightAvailable = true;
                }
                if(rightAvailable&&nodenext->keyNum>(MAX_KEY_SIZE+1)/2)
                {
                    memcpy(node->keys[node->keyNum],nodenext->keys[0],this->indexLen);
                    node->children[node->keyNum] = nodenext->children[0];
                    node->keyNum++;
                    for(int i = 0;i<node->keyNum-1;i++)
                    {
                        memcpy(nodenext->keys[i],nodenext->keys[i+1],this->indexLen);
                        nodenext->children[i]=nodenext->children[i+1];
                    }
                    nodenext->keyNum--;
                    flushNode(node);
                    flushNode(nodenext);
                    // TODO edit parent
                    IndexItem* editItem = this->buildItem();
                    memcpy(editItem->key,nodenext->keys[0],this->indexLen);
                    editItem->addr = PAGE_ADDR(node->pageNo);
                    this->editItem(node->parentAddr,editItem,0);
                    this->releaseIndexItem(editItem);
                }else
                {
                    if(leftAvailable)
                    {
                        mergeTwo(node->previous,PAGE_ADDR(node->pageNo));
                    }
                    else if(rightAvailable)
                    {
                        mergeTwo(PAGE_ADDR(node->pageNo),node->next);
                    }
                    // leftAvailable|rightAvailable = true
                    //  merge two node
                    // leftAvailable|rightAvailable = false => currentNode is root; we do nothing
                    // Attention! We should not use flush node here!
                }
            }
            delete nodepre;nodepre=0;
        }else
        {
            flushNode(node);
        }
    }
    delete node;node = 0;
}
void BPTree::freeNode(Addr pageAddr)
{
    BufferFrame* frame = new BufferFrame();
    frame->pageNo = PAGE_ID(pageAddr);
    this->drs->updateSpaceMark(frame,SegmentType::EmptySeg,PageStatus::EmptyPage);
    delete frame;
}
int BPTree::findAddressPosition(BPTNode* node,Addr addr)
{
    int pos = node->keyNum;
    for(;pos>=0;pos--)
    {
        if(node->children[pos]==addr)
        {
            break;
        }
    }
    return pos;
}
// 问题：
// 本质是指针混写问题。
// 1. bptnode 的parentAddr域不一定是有效的
// 我们在分裂时没有修改字节点的parent域，由于子节点有(m-1)/2个，修改子节点需要载入大量页面
// FIX思路：
// a.我们的parentAddr域采取延迟修改的策略
// 由于所有的子节点搜索都通过SearchBPTNode进行，我们在该函数中部分修改子节点parentAddr，搜索邻居V时通过上层节点进行。
// 然后定期fixParentAddr的错误
// b.由于刚刚分裂完成的节点不一定马上被用到，磁盘IO也需要一定时间，可以设置一个线程，专门负责parentAddr的修改
// c 思路：
// 为BPTNode单独建立缓冲区，分裂时在内存进行，减少BPTNode到Frame的时间,node在flush时同时check磁盘地址
//
void BPTree::getSiblingAddress(BPTNode* node,Addr& leftAddr,Addr& rightAddr)
{
    BPTNode* parent = new BPTNode();
    getBPTNode(parent,node->parentAddr);
    int pos = findAddressPosition(parent,PAGE_ADDR(node->pageNo));
    if(pos<0||pos>parent->keyNum)
    {
        #ifdef DEBUG_INDEX
        printf("we cannot get the addr in current node,sibling addr\n");
        #endif // DEBUG_INDEX
    }
    if(pos>0)leftAddr = parent->children[pos-1];
    if(pos<parent->keyNum)rightAddr=parent->children[pos+1];
    delete parent;
}
// item.addr return pos [k], the keys[k-1] will be eliminate and addr[k] invoke dir->updatePageMask(0,0);
// and then move element.
// and then judge wehter the block keyNum is less than (m-1)/2, and began to fit(look two sides and merge).
void BPTree::deleteElementFromNonLeafNodeByAddress(Addr addr,IndexItem* items)
{
    BPTNode *node=new BPTNode();
    getBPTNode(node,addr);
    int pos = findAddressPosition(node,items->addr);
    if(pos<=0)
    {
        #ifdef DEBUG_INDEX
            printf("warning: delete the leftest element.\n");
        #endif // DEBUG_INDEX
    }else
    {
        memcpy(items->key,node->keys[pos-1],this->indexLen);
        freeNode(items->addr);
        for(int i = pos-1;i<node->keyNum-1;i++)
        {
            memcpy(node->keys[i],node->keys[i+1],this->indexLen);
            node->children[i+1]=node->children[i+2];
        }
        node->keyNum--;
        if(node->keyNum<(MAX_KEY_SIZE-1)/2)
        {
            if((node->nodeType&BPTNodeType::isRoot)!=0)
            {
                if(node->keyNum==0)
                {
                    BPTNode* newNode = node;
                    node = root;
                    getBPTNode(newNode,root->children[0]);
                    newNode->nodeType|=BPTNodeType::isRoot;
                    changeRoot(newNode);
                    flushNode(newNode);
                    root = newNode;
                    freeNode(PAGE_ADDR(node->pageNo));
                }
            }else
            {
                Addr leftAddr = 0, rightAddr = 0;
                getSiblingAddress(node,leftAddr,rightAddr);
                BPTNode* nodepre = new BPTNode();
                bool leftAvailable = false;
                bool rightAvailable = false;
                if(leftAddr>0){
                    getBPTNode(nodepre,leftAddr);
                    leftAvailable= true;
                    nodepre->parentAddr = node->parentAddr;
                }
                if(leftAvailable&&nodepre->keyNum>(MAX_KEY_SIZE-1)/2)
                {
                    node->children[node->keyNum+1]=node->children[node->keyNum];
                    for(int i = node->keyNum;i>0;i--)
                    {
                        memcpy(node->keys[i],node->keys[i-1],this->indexLen);
                        node->children[i]=node->children[i-1];
                    }
                    memcpy(node->keys[0],nodepre->keys[nodepre->keyNum-1],this->indexLen);
                    node->children[0]=nodepre->children[nodepre->keyNum-1];
                    node->keyNum++;
                    nodepre->keyNum--;
                                        //TODO: edit parent
                    IndexItem* editItem = this->buildItem();
                    IndexItem* kitem = this->buildItem();
                    memcpy(editItem->key,node->keys[0],this->indexLen);
                    editItem->addr = PAGE_ADDR(nodepre->pageNo);
                    this->editItem(node->parentAddr,editItem,kitem);
                    memcpy(node->keys[0],kitem->key,this->indexLen);
                    flushNode(node);
                    flushNode(nodepre);
                    this->releaseIndexItem(editItem);
                    this->releaseIndexItem(kitem);
                }else
                {
                    BPTNode* nodenext = nodepre;
                    if(rightAddr>0){
                        getBPTNode(nodenext,rightAddr);
                        rightAvailable = true;
                        // edit right node parent
                        nodenext->parentAddr = node->parentAddr;
                    }
                    if(rightAvailable&&nodenext->keyNum>(MAX_KEY_SIZE-1)/2)
                    {
                        memcpy(node->keys[node->keyNum],nodenext->keys[0],this->indexLen);
                        node->children[node->keyNum+1] = nodenext->children[0];
                        node->keyNum++;
                        for(int i = 0;i<node->keyNum-1;i++)
                        {
                            memcpy(nodenext->keys[i],nodenext->keys[i+1],this->indexLen);
                            nodenext->children[i]=nodenext->children[i+1];
                        }
                        nodenext->children[node->keyNum-1]=nodenext->children[node->keyNum];
                        nodenext->keyNum--;
                        // modify before
                        IndexItem* editItem = this->buildItem();
                        memcpy(editItem->key,nodenext->keys[0],this->indexLen);
                        IndexItem* kitem = this->buildItem();
                        editItem->addr = PAGE_ADDR(node->pageNo);
                        this->editItem(node->parentAddr,editItem,kitem);
                        memcpy(node->keys[node->keyNum-1],kitem->key,this->indexLen);
                        flushNode(node);
                        flushNode(nodenext);
                        this->releaseIndexItem(editItem);
                        this->releaseIndexItem(kitem);
                    }else
                    {
                        if(leftAvailable)
                        {
                            mergeTwo(leftAddr,PAGE_ADDR(node->pageNo));
                        }
                        else if(rightAvailable)
                        {
                            mergeTwo(PAGE_ADDR(node->pageNo),rightAddr);
                        }
                        // leftAvailable|rightAvailable = true
                        //  merge two node
                        // leftAvailable|rightAvailable = false => currentNode is root; we do nothing
                        // Attention! We should not use flush node here!
                    }
                }
                delete nodepre;nodepre=0;
            }

        }else
        {
            flushNode(node);
        }

    }
    delete node;node = 0;

}
// you need to tell from whether the node is leaf.
// LEFT AND NONLEAF differences:
// offset diffenrece is 1
// non-leaf need copy retKey returned from deleteElementFromNonLeafNode
// both need call deleteElementFromNonLeafNode
void BPTree::mergeTwo(Addr leftAddr,Addr rightAddr)
{
    BPTNode* lnode = new BPTNode();
    BPTNode* rnode = new BPTNode();
    this->getBPTNode(lnode,leftAddr);
    this->getBPTNode(rnode,rightAddr);
    bool isLeaf = ((lnode->nodeType&BPTNodeType::hasData)!=0);
    bool canMerge = true;
    if(lnode->parentAddr!=rnode->parentAddr)
    {
        canMerge = false;
        #ifdef DEBUG_INDEX
            printf("error: two node has different parent addr!\n");
        #endif // DEBUG_INDEX
    }
    if(isLeaf&&lnode->next!=PAGE_ADDR(rnode->pageNo))
    {
        canMerge = false;
        #ifdef DEBUG_INDEX
            printf("error: two nodes are not siblings!\n");
        #endif
    }
    if(canMerge)
    {
        int keyOffset = 0;
        if(!isLeaf)keyOffset = 1;
        for(int i=0;i<rnode->keyNum;i++)
        {
            memcpy(lnode->keys[lnode->keyNum+i+keyOffset],rnode->keys[i],this->indexLen);
            lnode->children[lnode->keyNum+i]=rnode->children[i];
        }

        IndexItem* items = this->buildItem();
            //IndexItem* ret = this->buildItem();
        items->addr = PAGE_ADDR(rnode->pageNo);
        this->deleteElementFromNonLeafNodeByAddress(lnode->parentAddr,items);
        if(!isLeaf)
        {
            memcpy(lnode->keys[lnode->keyNum],items->key,this->indexLen);
        }
        this->releaseIndexItem(items);
        if(!isLeaf)
        {
            lnode->children[lnode->keyNum+rnode->keyNum]=rnode->children[rnode->keyNum];
        }
        lnode->keyNum+=rnode->keyNum;
        flushNode(lnode);
    }
    delete lnode;
    delete rnode;
}
Addr BPTree::deleteElem(IndexItem* item){
        IndexItem *it = this->buildItem();
        BPTIterator *iterator = 0;
        Addr currentnodeaddr = 0;
        BPTNode* cnode = new BPTNode();
        iterator=dynamic_cast<BPTIterator*>(findByKey(item->key));
        Addr old = 0;
        for(iterator->findFirst(it);true;iterator->findNext(it))
        {
            if(old==it->addr)break;
            old = it->addr;
            if(it->addr==item->addr)
                {
                    currentnodeaddr=PAGE_ADDR(iterator->currentNode->pageNo);
                    getBPTNode(cnode,currentnodeaddr);
                }

        }
        this->destoryIterator(iterator);
        delete cnode;cnode = 0;
        if(currentnodeaddr!=0)
        {
            deleteElementFromNode(currentnodeaddr,item);
        }else
        {

        }

}
IndexItem* BPTree::buildItem(){
    IndexItem* item = new IndexItem();
    item->key=new Byte[8];
    return item;
}
void BPTree::releaseIndexItem(IndexItem* item){
    if(item!=0)
    {
        delete[] item->key;
        item->key=0;
    }
    delete item;
}
void BPTree::releaseAll(){
    flushNode(root);
}
BPTree::~BPTree(){
    if(root!=0)
    {
        flushNode(root);
        delete root;
        root = 0;
    }
}

short BPTree::transNodeToFrame(BPTNode* node,BufferFrame* frame)
{
        Page* page = frame->page;
        Byte* data = page->data;
        page->usedByte = PAGE_BODY_LEN;
        page->usedLen=0;
        page->usedByteList[0].addr=0;
        page->usedByteList[0].len=0;
        ushort flag = page->flag;
        flag = flag&(~SegmentType::mask)|SegmentType::IndexSeg&(~PageStatus::mask)|PageStatus::FullPage;
        page->flag = flag;
        data+=PAGE_HEAD_LEN;
        data+=PAGE_ALIGN;
        Byte* old = data;
        int pos = 0;
        data[pos++]=BPTNODE_MAGIC;
        data[pos++]=node->fid;
        data[pos++]=node->nodeType;
        data[pos++]=BPTNODE_MAGIC;
        data+=pos;
        memcpy(data,&node->keyNum,sizeof(int));
        data+=sizeof(int);
        memcpy(data,&node->parentAddr,sizeof(Addr));
        data+=sizeof(Addr);
        memcpy(data,&node->previous,sizeof(Addr));
        data+=sizeof(Addr);
        memcpy(data,&node->next,sizeof(Addr));
        data+=sizeof(Addr);
        // 考虑到空间分配问题，keys和addr交替写入，先写addr[0],然后写入key[0]与addr[1],写keyNum次
        memcpy(data,&node->children[0],sizeof(Addr));
        data+=sizeof(Addr);
        for(int i=0;i<node->keyNum;i++)
        {
            memcpy(data,node->keys[i],8);
            data+=8;
            memcpy(data,&node->children[i+1],sizeof(Addr));
            data+=sizeof(Addr);
        }
        return data-old;
}
    short BPTree::transFrameToNode(BufferFrame* frame,BPTNode* node)
    {
            Page* page = frame->page;
            ushort flag = page->flag&SegmentType::mask;
            if(flag!=SegmentType::IndexSeg)
            {
                #ifdef DEBUG_INDEX
                printf("warning: this page is not a index segment page! pageAddr %llx\n",frame->pageNo);
                printf("flag %d\n",flag);

                #endif // DEBUG_INDEX
            }
            Byte* data = page->data;

            data+=PAGE_HEAD_LEN;
            data+=PAGE_ALIGN;
                        Byte* old = data;
            int pos = 0;
            if(data[pos++]!=BPTNODE_MAGIC)
            {
                #ifdef DEBUG_INDEX
                    printf("warning: this position is not a BPTNODE index! cnt = %d\n",cnt);
                    for(int i=0;i<64;i++)
                    {
                        printf("%x ",data[i]);
                        if((i+1)%16==0)printf("\n");
                    }
                exit(0);
                #endif // DEBUG_INDEX
                return data-old;
            }
            node->fid=data[pos++];
            node->nodeType=data[pos++];
            if(data[pos++]!=BPTNODE_MAGIC)
            {
                #ifdef DEBUG_INDEX
                    printf("warning: this position is not a BPTNODE index2!\n");
                #endif // DEBUG_INDEX
                                return data-old;
            }
            //node->keyNum=data[pos++];
            data+=pos;
            memcpy(&node->keyNum,data,sizeof(int));
            data+=sizeof(int);
            memcpy(&node->parentAddr,data,sizeof(Addr));
            data+=sizeof(Addr);
            memcpy(&node->previous,data,sizeof(Addr));
            data+=sizeof(Addr);
            memcpy(&node->next,data,sizeof(Addr));
            data+=sizeof(Addr);
            memcpy(&node->children[0],data,sizeof(Addr));
            data+=sizeof(Addr);
            for(int i=0;i<node->keyNum;i++)
            {
                memcpy(node->keys[i],data,8);
                data+=8;
                memcpy(&node->children[i+1],data,sizeof(Addr));
                data+=sizeof(Addr);
            }
            node->pageNo = frame->pageNo;
            return data-old;
    }

    void BPTree::deletefromnoleaf(BPTNode* node)
    {

    }
    /*
    bool BPTree::deleteElem(IndexItem* item)
    {

        IndexItem *it = this->buildItem();
        BPTIterator *iterator;
        Addr currentnodeaddr;
        iterator=dynamic_cast<BPTIterator*>findByKey(item->key);
        int flag=0;
        for(iterator->findFirst(it);iterator.hasNext();iterator.findNext(it))
        {
            if(it.addr==item.addr)
                {
                    flag=1;
                    currentnodeaddr=PAGE_ADDR(iterator->currentNode->pageNo);
                    break;
                }
        }
        if(flag!=1)
        {
            printf("error:please choose an reality item to delete");
        }
        BufferFrame *bfm;
        BPTNode *node=new BPTNode();
        getBPTNode(node,currentnodeaddr);
        if(node1->keyNum>MAX_KEY_SIZE/2)
        {
            int num;
            num=findUpBound(data,node);
        }
        else
        {
            //BufferFrame *bfm1;
            //bfm1=this->manager->requestPageForWrite(node1->previous);
            BPTNode *nodepre=new BPTNode();
            getBPTNode(nodepre,node1->previous);
            BPTNode *nodenew=new BPTNode();
            this->getNewBPTNode(nodenew,BPTNodeType::hasData);
            leafcpy(nodepre,node,0,node->keyNum,);
            //flushNode(nodepre);


            delete nodepre;nodepre=0;
            delete nodenew;nodenew=0;

        }
        delete node;node=0;
    }*/
