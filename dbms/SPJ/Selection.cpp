#include"Selection.h"
#include<cstdio>
#include<limits>
#include<iostream>

 Selection::Selection(int type,int initial):SPJ(){
    this->operatorType=type;
    this->table=0;
    this->currentTuple=0;
    this->initialType=initial;
    this->condition=0;
    this->dataType=0;
    this->spj=0;
    this->index=0;
 }
void Selection::destroy(){
    if(this->initialType==SPJ::TABLEINITIAL){
            if(this->currentTuple!=0)
            this->table->releaseEmptyTuple(this->currentTuple);
            delete(this->dataType);
    }else{
        delete(this->dataType);
    }
}
 void Selection::initSelection(Table*table,Condition*condition,int conditionLen){
            this->table=table;
            this->condition=condition;
            this->conditionLen=conditionLen;
            this->columnNum=table->getTableMeta()->fieldNum;
            this->columns=0;
            this->indexIterator=checkIndex();
 }

void Selection::releaseSPJItem(SPJItem*item){
            for(int i=0;i<item->fieldNum;i++){
                delete item->data[i];
            }
            delete item->data;
            delete(item->dataType);
            delete(item->len);
            delete(item);
}

SPJItem* Selection::buildSPJItem(){
        SPJItem* item=new SPJItem();
        item->fieldNum=this->columnNum;
        item->fieldName=new string[this->columnNum];
        item->data=new void*[this->columnNum];
        for(int i=0;i<this->columnNum;i++) item->data[i]=0;
        item->len=new int[this->columnNum];
        item->dataType=new Byte[this->columnNum];
        return item;
}
void Selection::getNext(SPJItem*item){
        item->use=0;
        if(this->initialType==SPJ::TABLEINITIAL){
                if(this->indexIterator!=0){
                     IndexItem*indexItem=this->index->buildItem();
                    Tuple *tuple=table->buildEmptyTuple();
                    if(indexIterator->hasNext()){
                        this->indexIterator->findNext(indexItem);
                    }
                    DataSegment*dataseg=this->table->getDataSegment();
                    dataseg->findTupleAtPosition(tuple,indexItem->addr);
                    bool flag=true;
                    while(checkItem(tuple)!=true){
                        if(indexIterator->hasNext()){
                            indexIterator->findNext(indexItem);
                            dataseg->findTupleAtPosition(tuple,indexItem->addr);
                        }else{
                            flag=false;
                            break;
                        }
                        char*str=new char[1000];
                         DataUtil::toString(str,tuple->column[0].data,tuple->column[0].field->dataType);
                         printf("%s\n",str);
                    }
                    if(flag) {
                            fillItem(item,tuple);
                            this->currentTuple=tuple;
                    }
                    //table->releaseEmptyTuple(tuple);
                    this->index->releaseIndexItem(indexItem);
                 }else{
                       Tuple *tuple=this->currentTuple;
                        Addr oldAddr=this->currentTuple->tupleAddr;
                        table->findNextTuple(this->currentTuple,tuple);
                        if(tuple->tupleAddr!=oldAddr&&tuple->tupleAddr!=0){
                            while(checkItem(tuple)!=true){
                                Addr oldaddr=this->currentTuple->tupleAddr;
                                table->findNextTuple(this->currentTuple,tuple);
                                if(tuple->tupleAddr==0||tuple->tupleAddr==oldaddr) break;
                                //table->releaseEmptyTuple()
                                //this->currentTuple=tuple;
                            }
                            if(checkItem(tuple)){
                                fillItem(item,tuple);
                                //this->currentTuple=tuple;
                            }
                        }
                    //table->releaseEmptyTuple(this->currentTuple);
            }
        }else if(this->initialType==SPJ::ITERATORINITIAL){
               SPJItem*sourceItem =this->spj->buildSPJItem();
               bool flag=true;
             while(checkItem(sourceItem)!=true){
                    spj->getNext(sourceItem);
                    if(sourceItem->use==0){
                        flag=false;
                        break;
                    }
             }
             if(flag) fillItem(item,sourceItem);
             this->spj->releaseSPJItem(sourceItem);
        }
}
void Selection::getFirst(SPJItem * item){
      item->use=0;
      if(this->initialType==SPJ::TABLEINITIAL){
        if(this->indexIterator!=0)
        {
            Tuple *tuple=table->buildEmptyTuple();
            IndexItem*indexItem=this->index->buildItem();
            this->indexIterator->findFirst(indexItem);
            if(indexItem->addr!=0){
                    DataSegment*dataseg=this->table->getDataSegment();
                    dataseg->findTupleAtPosition(tuple,indexItem->addr);
                    while(checkItem(tuple)!=true){
                        if(indexIterator->hasNext()){
                            indexIterator->findNext(indexItem);
                             dataseg->findTupleAtPosition(tuple,indexItem->addr);
                        }else{
                                break;
                        }
                    }
                    if(checkItem(tuple)==true){
                         fillItem(item,tuple);
                    //table->releaseEmptyTuple(tuple);
                        this->currentTuple=tuple;
                    }
            }
            this->index->releaseIndexItem(indexItem);
        }else{
            Tuple *tuple=this->table->buildEmptyTuple();
            table->findFirstTuple(tuple);
            this->currentTuple=tuple;
            if(tuple->tupleAddr!=0){
               while(checkItem(tuple)!=true){
                Addr oldaddr=this->currentTuple->tupleAddr;
                table->findNextTuple(this->currentTuple,tuple);
                if(oldaddr==tuple->tupleAddr||tuple->tupleAddr==0) break;
                //table->releaseEmptyTuple(this->currentTuple);
                }
                if(checkItem(tuple)==true){
                         fillItem(item,tuple);
                         //this->currentTuple=tuple;
                }
            }
            //table->releaseEmptyTuple(tuple);
        }
      }else if(this->initialType==SPJ::ITERATORINITIAL){
               SPJItem*sourceItem =this->spj->buildSPJItem();
               spj->getFirst(sourceItem);
               bool flag=true;
               while(checkItem(sourceItem)!=true){
                        spj->getNext(sourceItem);
                        if(sourceItem->use==0){
                                flag=false;
                                break;
                        }
                 }
                 if(flag) fillItem(item,sourceItem);
               this->spj->releaseSPJItem(sourceItem);
        }
}
bool Selection::checkItem(Tuple *tuple){
         int fieldNum=tuple->meta->fieldNum;
         map<string,vector<Condition> >mp;
         for(int i=0;i<this->conditionLen;i++){
            string str=this->condition[i].filedName;
            mp[str].push_back(condition[i]);
         }
         int cnt=0;
         bool flag=true;
        for(int i=0;i<fieldNum;i++){
               string ss=tuple->column[i].field->fname;
               if(mp.count(ss)>=1){
                     for(int j=0;j<mp[ss].size();j++){
                             flag=CompareType::Compare(tuple->column[i].data,mp[ss][j].value, mp[ss][j].compare,tuple->column[i].field->dataType,tuple->column[i].field->len);

                             if(!flag) break;
                     }
               }
               if(!flag) break;
        }
        return flag;
}
bool Selection::checkItem(SPJItem*sourceItem){
         int fieldNum=sourceItem->fieldNum;
         map<string,vector<Condition> >mp;
         for(int i=0;i<this->conditionLen;i++){
            string str=this->condition[i].filedName;
            mp[str].push_back(condition[i]);
         }
         int cnt=0;
         bool flag;
        for(int i=0;i<fieldNum;i++){
               string ss=sourceItem->fieldName[i];
               if(mp.count(ss)>=1){
                     for(int j=0;j<mp[ss].size();j++){
                             flag=CompareType::Compare(sourceItem->data[i],mp[ss][j].value, mp[ss][j].compare,sourceItem->dataType[i],sourceItem->len[i]);
                             if(flag==false) {
                                return false;
                             }
                     }
               }
        }
        return flag;
}

IndexIterator* Selection::checkIndex(){
       IndexIterator*indexIterator=0;
        Tuple *tuple=this->table->buildEmptyTuple();
        map<string,vector<Condition> >mp;
        IndexSegment* idxseg = this->table->getIndexSegment();
        for(int i=0;i<this->conditionLen;i++){
            string str=condition[i].filedName;
            mp[str].push_back(condition[i]);
        }
        bool flag=false;
        for(int i=0;i<tuple->meta->fieldNum;i++){
               string ss=tuple->column[i].field->fname;
               if(mp.count(ss)>0){
                    for(int j=0;j<idxseg->indexMeta->useLen;j++)
                    {
                        if(idxseg->indexMeta->indexList[j].fid==tuple->column[i].field->fid){
                                indexIterator=getIndexIterator(idxseg->indexMeta->indexList[j],mp[ss],idxseg);
                                if(indexIterator!=0){
                                        flag=true;
                                        break;
                                }
                        }

                    }
               }
               if(flag) break;
        }
        this->table->releaseEmptyTuple(tuple);
    return indexIterator;
}
IndexIterator* Selection::getIndexIterator(IndexMetaItem item,vector<Condition>conditionlist,IndexSegment*indexSegment){
        IndexIterator*indexIterator=0;
        if(item.indexType==IndexType::hashidx&&conditionlist.size()==1){//condition:range search,index::hash
              if(conditionlist[0].compare==CompareType::EQUAL){
                        this->index=indexSegment->findIndex(item.fid,IndexType::hashidx);
                        indexIterator=this->index->findByKey(conditionlist[0].value);
                }
        }else if(item.indexType==IndexType::bptidx){
        this->index=indexSegment->findIndex(item.fid,IndexType::bptidx);
            if(conditionlist.size()==1){
                if(conditionlist[0].compare==CompareType::EQUAL){
                        indexIterator=this->index->findByKey(conditionlist[0].value);
                }else if(conditionlist[0].compare==CompareType::LESSEQUAL){
                        void*data=0;
                       if(conditionlist[0].DataType==DataTypeFlag::DOUBLE){
                            data=new double((numeric_limits<double>::min)());
                       }else if(conditionlist[0].DataType==DataTypeFlag::FLOAT){
                               data=new float((numeric_limits<float>::min)());
                       }else if(conditionlist[0].DataType==DataTypeFlag::INTEGER){
                               data=new int((numeric_limits<int>::min)());
                               int*a=new int((numeric_limits<int>::min)());
                               printf("int min ::%d\n",*a);
                       }
                        indexIterator=this->index->findByRange(data,conditionlist[0].value);
                }else if(conditionlist[0].compare==CompareType::GREATEREQUAL){
                             void*data=0;
                       if(conditionlist[0].DataType==DataTypeFlag::DOUBLE){
                            data=new double((numeric_limits<double>::max)());
                       }else if(conditionlist[0].DataType==DataTypeFlag::FLOAT){
                               data=new float((numeric_limits<float>::max)());
                       }else if(conditionlist[0].DataType==DataTypeFlag::INTEGER){
                                   data=new int((numeric_limits<int>::max)());
                       }
                        indexIterator=this->index->findByRange(conditionlist[0].value,data);
                }else if(conditionlist[0].compare==CompareType::GREATER){
                      void*data=0;
                      void*value=0;
                       if(conditionlist[0].DataType==DataTypeFlag::DOUBLE){
                            double data1=0;
                            value=new Byte[sizeof(double)];
                            data=new double((numeric_limits<double>::max)());
                            memcpy(&data1,conditionlist[0].value,sizeof(double));
                            data1+=0.0001;
                            memcpy(value,&data1,sizeof(double));
                       }else if(conditionlist[0].DataType==DataTypeFlag::FLOAT){
                                float data1=0;
                                value=new Byte[sizeof(float)];
                                data=new float((numeric_limits<float>::max)());
                                //printf("%f",data)
                                memcpy(&data1,conditionlist[0].value,sizeof(float));
                                data1+=0.0001;
                                memcpy(value,&data1,sizeof(float));
                       }else if(conditionlist[0].DataType==DataTypeFlag::INTEGER){
                                int data1=0;
                                value=new Byte[sizeof(int)];
                               data=new int((numeric_limits<int>::max)());
                                memcpy(&data1,conditionlist[0].value,sizeof(int));
                                data1+=1;
                                 memcpy(value,&data1,sizeof(int));
                       }
                         indexIterator=this->index->findByRange(value,data);
                }else if(conditionlist[0].compare==CompareType::LESS){
                         void*data=0;
                         void*value=0;
                       if(conditionlist[0].DataType==DataTypeFlag::DOUBLE){
                            double data1=0;
                            value=new Byte[sizeof(double)];
                            data=new double((numeric_limits<double>::min)());
                            memcpy(&data1,conditionlist[0].value,sizeof(double));
                            data1-=0.00001;
                            memcpy(value,&data1,sizeof(double));
                       }else if(conditionlist[0].DataType==DataTypeFlag::FLOAT){
                           float data1=0;
                           value=new Byte[sizeof(float)];
                            data=new float((numeric_limits<float>::min)());
                            memcpy(&data1,conditionlist[0].value,sizeof(float));
                            data1-=0.00001;
                            memcpy(value,&data1,sizeof(float));
                       }else if(conditionlist[0].DataType==DataTypeFlag::INTEGER){
                            int data1=0;
                            value=new Byte[sizeof(int)];
                            data=new int((numeric_limits<int>::min)());
                            memcpy(&data1,conditionlist[0].value,sizeof(int));
                            data1-=1;
                            memcpy(value,&data1,sizeof(int));
                       }
                       indexIterator=this->index->findByRange(data,value);
                }
            }else if(conditionlist.size()==2){
                        void*value1=0;
                        void*value2=0;
                        void*value3=0;
                        void*value4=0;
                    if(conditionlist[0].DataType==DataTypeFlag::DOUBLE){
                        double data1=0;
                        value1=new Byte[sizeof(double)];
                        value2=new Byte[sizeof(double)];
                        memcpy(&data1,conditionlist[0].value,sizeof(double));
                        data1-=0.00001;
                        memcpy(value1,&data1,sizeof(double));
                        data1+=0.00002;
                        memcpy(value2,&data1,sizeof(double));
                    }else if(conditionlist[0].DataType==DataTypeFlag::FLOAT){
                        float data1=0;
                        value1=new Byte[sizeof(float)];
                        value2=new Byte[sizeof(float)];
                        memcpy(&data1,conditionlist[0].value,sizeof(float));
                        data1-=0.00001;
                        memcpy(value1,&data1,sizeof(float));
                        data1+=0.00002;
                        memcpy(value2,&data1,sizeof(float));
                    }else if(conditionlist[0].DataType==DataTypeFlag::INTEGER){
                        int data1=0;
                        value1=new Byte[sizeof(int)];
                        value2=new Byte[sizeof(int)];
                        memcpy(&data1,conditionlist[0].value,sizeof(int));
                        data1-=1;
                        memcpy(value1,&data1,sizeof(int));
                        data1+=2;
                        memcpy(value2,&data1,sizeof(int));
                    }
                    if(conditionlist[1].DataType==DataTypeFlag::DOUBLE){
                        double data1=0;
                        value3=new Byte[sizeof(double)];
                        value4=new Byte[sizeof(double)];
                        memcpy(&data1,conditionlist[1].value,sizeof(double));
                        data1-=0.00001;
                        memcpy(value3,&data1,sizeof(double));
                        data1+=0.00002;
                        memcpy(value4,&data1,sizeof(double));
                    }else if(conditionlist[1].DataType==DataTypeFlag::FLOAT){
                        float data1=0;
                        value3=new Byte[sizeof(float)];
                        value4=new Byte[sizeof(float)];
                        memcpy(&data1,conditionlist[1].value,sizeof(float));
                        data1-=0.00001;
                        memcpy(value3,&data1,sizeof(float));
                        data1+=0.00002;
                        memcpy(value4,&data1,sizeof(float));
                    }else if(conditionlist[1].DataType==DataTypeFlag::INTEGER){
                        int data1=0;
                        value3=new Byte[sizeof(int)];
                        value4=new Byte[sizeof(int)];
                        memcpy(&data1,conditionlist[1].value,sizeof(int));
                        data1-=1;
                        memcpy(value3,&data1,sizeof(int));
                        data1+=2;
                        memcpy(value4,&data1,sizeof(int));
                    }
                        if(conditionlist[0].compare==CompareType::LESS&&conditionlist[1].compare==CompareType::GREATER){
                                indexIterator=this->index->findByRange(value4,value1);
                        }else if(conditionlist[0].compare==CompareType::LESS&&conditionlist[1].compare==CompareType::GREATEREQUAL){
                                indexIterator=this->index->findByRange(conditionlist[1].value,value1);
                        }else if(conditionlist[0].compare=CompareType::LESSEQUAL&&conditionlist[1].compare==CompareType::GREATER){
                                indexIterator=this->index->findByRange(value4,conditionlist[0].value);
                        }else if(conditionlist[0].compare==CompareType::LESSEQUAL&&conditionlist[1].compare==CompareType::GREATEREQUAL){
                                indexIterator=this->index->findByRange(conditionlist[1].value,conditionlist[0].value);
                        }else if(conditionlist[0].compare==CompareType::GREATEREQUAL&&conditionlist[1].compare==CompareType::LESSEQUAL){
                                indexIterator=this->index->findByRange(conditionlist[0].value,conditionlist[1].value);
                        }else if(conditionlist[0].compare==CompareType::GREATEREQUAL&&conditionlist[1].compare==CompareType::LESS){
                                indexIterator=this->index->findByRange(conditionlist[0].value,value3);
                        }else if(conditionlist[0].compare==CompareType::GREATER&&conditionlist[1].compare==CompareType::LESS){
                                indexIterator=this->index->findByRange(value2,value3);
                        }else if(conditionlist[0].compare==CompareType::GREATER&&conditionlist[1].compare==CompareType::LESSEQUAL){
                                indexIterator=this->index->findByRange(value2,conditionlist[1].value);
                        }
            }
        }
        return indexIterator;
}
void Selection::fillItem(SPJItem*item,Tuple *tuple){
         for(int i=0;i<item->fieldNum;i++){
               item->fieldName[i]=tuple->column[i].field->fname;
                if(item->data[i]==0)
                        item->data[i]=new Byte[tuple->column[i].field->len];
                memcpy(item->data[i],tuple->column[i].data,tuple->column[i].field->len);
                item->len[i]=tuple->column[i].field->len;
                item->dataType[i]=tuple->column[i].field->dataType;
        }
        item->use=1;
}
void Selection::fillItem(SPJItem*item,SPJItem*sourceItem){
         int fieldNum=sourceItem->fieldNum;
         item->fieldNum=fieldNum;
         if(this->columnNum==0){
            this->columnNum=fieldNum;
            item->fieldName=new string[this->columnNum];
            item->data=new void*[this->columnNum];
            for(int i=0;i<this->columnNum;i++) item->data[i]=0;
            item->len=new int[this->columnNum];
            item->dataType=new Byte[this->columnNum];
         }
        for(int i=0;i<fieldNum;i++){
                item->fieldName[i]=sourceItem->fieldName[i];
                if(item->data[i]==0) item->data[i]=new Byte[sourceItem->len[i]];
                memcpy(item->data[i],sourceItem->data[i],sourceItem->len[i]);
                item->dataType[i]=sourceItem->dataType[i];
                item->len[i]=sourceItem->len[i];
        }
        item->use=sourceItem->use;
}
void Selection::initSelection(SPJ*spj,Condition condition[] ,int conditionLen){
            this->spj=spj;
            this->condition=condition;
            this->conditionLen=conditionLen;
}

void Selection::spjForUpdateOne(SPJItem * item, char * fieldName, int intValue, float floatValue, char* str, int flag)
{
            TableMeta *meta = table->getTableMeta();
            Tuple *tuple=this->table->buildEmptyTuple();
            //Tuple * toFill = this->table->buildEmptyTuple();
            table->findFirstTuple(tuple);
            this->currentTuple=tuple;
            Addr oldAddr=0u;
            //printf("%llx\t%llx\n", oldAddr, tuple->tupleAddr);
             while(oldAddr!=tuple->tupleAddr&&tuple->tupleAddr!=0)
                {
                     if(checkItem(tuple)==true)
                    {
                        //toFIll = tuple;
                        for(int i = 0; i < meta->fieldNum; i ++)
                            {
                                if(strcmp(fieldName, tuple->column[i].field->fname)==0)
                                {
                                    switch(flag)
                                    {
                                    case 0:// INTEGER
                                        TableUtil::writeColumn(&intValue,&tuple->column[i]);
                                        break;
                                    case 1:// FLOAT
                                        TableUtil::writeColumn(&floatValue,&tuple->column[i]);
                                        break;
                                    case 2:// STRING
                                        TableUtil::writeColumn(str,&tuple->column[i]);
                                        break;
                                    default:
                                        break;
                                    }
                                   break;
                                }
                            }
                            table->flushTuple(tuple);
                        /*******************************************
                        TODO
                    ******************************************/
                         this->currentTuple=tuple;
                    }
                    oldAddr=this->currentTuple->tupleAddr;
                    table->findNextTuple(this->currentTuple,tuple);
                }
            //table->releaseEmptyTuple(tuple);
}

void Selection::spjForDeleteOne(SPJItem * item)
{

            Tuple *tuple=this->table->buildEmptyTuple();
            table->findFirstTuple(tuple);
            this->currentTuple=tuple;
            Addr oldAddr=0u;
            //printf("%llx\t%llx\n", oldAddr, tuple->tupleAddr);
             while(oldAddr!=tuple->tupleAddr&&tuple->tupleAddr!=0)
                {
                     if(checkItem(tuple)==true)
                    {
                        //fillItem(item,tuple);
                         table->deleteTuple(tuple);
                         this->currentTuple=tuple;
                    }

                    oldAddr=this->currentTuple->tupleAddr;
                    table->findNextTuple(this->currentTuple,tuple);
                }
            //table->releaseEmptyTuple(tuple);
}
