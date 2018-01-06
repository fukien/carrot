#include "Join.h"

Join::Join(int type, int initial, Byte joinType)
{
    this->operatorType = type;
    this->initialType = initial;
    this->dataType = 0;
    this->spj = 0;
    this->table = 0;
    this->columnNum = 0;
    this->fieldList = 0;
    this->fieldflag = false;
    // this->currentTuple=0;
    this->tableLen = 0;
    this->spjLen = 0;
    this->joinType = joinType;
    this->currentTuple_A = 0;
    this->currentTuple_B = 0;
    this->currentSPJItem_A = 0;
    this->currentSPJItem_B = 0;
}
void Join::destroy()
{
}
SPJItem *Join::buildSPJItem()
{
    SPJItem *item = new SPJItem();
    if (this->columnNum != 0)
    {
        item->fieldNum = this->columnNum;
        item->fieldName = new string[this->columnNum];
        item->data = new void *[this->columnNum];
        for (int i = 0; i < this->columnNum; i++)
            item->data[i] = 0;
        item->len = new int[this->columnNum];
        item->dataType = new Byte[this->columnNum];
    }
    else
    {
        item->fieldNum = 0;
        item->fieldName = 0;
        item->data = 0;
        item->len = 0;
        item->dataType = 0;
    }
    return item;
}
void Join::releaseSPJItem(SPJItem *item)
{
}
void Join::initJoin(Table **table, int tableLen, SPJ **spj, int spjLen, Condition conditionList[], int conditionLen)
{
    this->table = table;
    this->spj = spj;
    this->tableLen = tableLen;
    this->spjLen = spjLen;
    this->condition = conditionList;
    this->conditionLen = conditionLen;
    if (this->joinType == JoinType::NESTLOOPJOIN)
    {
        initNestLoopJoin();
    }
    else if (this->joinType == JoinType::SORTJOIN)
    {
        initSortJoin();
    }
    else if (this->joinType == JoinType::HASHJOIN)
    {
        initHashJoin();
    }
    else
    {
        initIndexJoin();
    }
}

void Join::getFirst(SPJItem *item)
{
    if (this->joinType == JoinType::NESTLOOPJOIN)
    {
        NestLoopJoinGetFirst(item);
    }
    else if (this->joinType == JoinType::HASHJOIN)
    {
    }
    else if (this->joinType == JoinType::SORTJOIN)
    {
    }
    else
    {
    }
}
void Join::getNext(SPJItem *item)
{
    if (this->joinType == JoinType::NESTLOOPJOIN)
    {
        NestLoopJoinGetNext(item);
    }
    else if (this->joinType == JoinType::HASHJOIN)
    {
    }
    else if (this->joinType == JoinType::SORTJOIN)
    {
    }
    else
    {
    }
}
void Join::NestLoopJoinGetNext(SPJItem *item)
{
    item->use = 0;
    if (this->initialType == SPJ::TABLEINITIAL)
    {
        //Tuple *A_tuple=this->table[0]->buildEmptyTuple();
        Tuple *B_tuple = this->currentTuple_B;
        Tuple *A_tuple = this->currentTuple_A;
        Addr A_oldaddr = 0;
        // this->table[0]->findNextTuple(this->currentTuple_A,A_tuple);
        //this->table[0]->releaseEmptyTuple(this->currentTuple_A);
        //this->currentTuple_A=A_tuple;
        //this->currentTuple_B=B_tuple;
        Addr B_oldaddr = 0;
        while (A_tuple->tupleAddr != 0 && A_tuple->tupleAddr != A_oldaddr)
        {
            if (this->currentTuple_B == 0)
            {
                B_oldaddr = 0;
                B_tuple = this->table[1]->buildEmptyTuple();
                this->table[1]->findFirstTuple(B_tuple);
                this->currentTuple_B = B_tuple;
            }
            else
            {
                B_oldaddr = this->currentTuple_B->tupleAddr;
                this->table[1]->findNextTuple(this->currentTuple_B, B_tuple);
            }
            //this->table[1]->releaseEmptyTuple(this->currentTuple_B);// the tuple here isn't been free
            //this->currentTuple_B=B_tuple;
            if (B_tuple->tupleAddr != 0 && B_tuple->tupleAddr != B_oldaddr)
            {
                bool flag = true;
                while (checkItem(A_tuple, B_tuple) != true)
                {
                    B_oldaddr = B_tuple->tupleAddr;
                    this->table[1]->findNextTuple(this->currentTuple_B, B_tuple);
                    if (B_oldaddr == B_tuple->tupleAddr || B_tuple->tupleAddr == 0)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    fillItem(A_tuple, B_tuple, item);
                    break;
                }
            }
            A_oldaddr = A_tuple->tupleAddr;
            this->table[0]->findNextTuple(this->currentTuple_A, A_tuple);
            this->table[1]->releaseEmptyTuple(this->currentTuple_B);
            this->currentTuple_B = 0;
        }
        //this->table[0]->releaseEmptyTuple(this->currentTuple_A);
        //this->table[1]->releaseEmptyTuple(this->currentTuple_B);
    }
    else if (this->initialType == SPJ::ITERATORINITIAL)
    {
        SPJItem *A_item = this->currentSPJItem_A;
        SPJItem *B_item = this->currentSPJItem_B;
        while (A_item->use != 0)
        {
            if (B_item->use != 0)
            {
                this->spj[1]->getNext(B_item);
            }
            else
            {
                this->spj[1]->getFirst(B_item);
            }
            if (B_item->use != 0)
            {
                bool flag = true;
                while (checkItem(A_item, B_item) != true)
                {
                    this->spj[1]->getNext(B_item);
                    if (B_item->use == 0)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    fillItem(A_item, B_item, item);
                    break;
                }
            }
            this->spj[0]->getNext(A_item);
            //this->spj[1]->getFirst(B_item);
        }
        //this->spj[0]->releaseSPJItem(A_item);
        //this->spj[1]->releaseSPJItem(B_item);
    }
    else
    {
        Tuple *A_tuple = this->currentTuple_A;
        SPJItem *A_item = this->currentSPJItem_A;
        Addr oldAddr = 0;
        //this->table[0]->findNextTuple(this->currentTuple_A,A_tuple);
        //this->table[0]->releaseEmptyTuple(this->currentTuple_A);
        //this->currentTuple_A=A_tuple;
        while (A_tuple->tupleAddr != 0 && A_tuple->tupleAddr != oldAddr)
        {
            if (A_item->use != 0)
            {
                this->spj[0]->getNext(A_item);
            }
            else
            {
                this->spj[0]->getFirst(A_item);
            }
            if (A_item->use != 0)
            {
                bool flag = true;
                while (checkItem(A_tuple, A_item) != true)
                {
                    this->spj[0]->getNext(A_item);
                    if (A_item->use == 0)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    fillItem(A_tuple, A_item, item);
                    break;
                }
            }
            oldAddr = A_tuple->tupleAddr;
            this->table[0]->findNextTuple(this->currentTuple_A, A_tuple);
            //this->spj[0]->getFirst(A_item);
        }
        //this->spj[0]->releaseSPJItem(A_item);
    }
}
void Join::NestLoopJoinGetFirst(SPJItem *item)
{
    item->use = 0;
    if (this->initialType == SPJ::TABLEINITIAL)
    {
        Tuple *A_tuple = this->table[0]->buildEmptyTuple();
        Tuple *B_tuple = this->table[1]->buildEmptyTuple();
        this->table[0]->findFirstTuple(A_tuple);
        this->currentTuple_A = A_tuple;
        this->currentTuple_B = B_tuple;
        Addr A_oldaddr = 0;
        Addr B_oldaddr = 0;
        while (A_tuple->tupleAddr != 0 && A_tuple->tupleAddr != A_oldaddr)
        {
            this->table[1]->findFirstTuple(B_tuple);
            if (B_tuple->tupleAddr != 0 && B_tuple->tupleAddr != B_oldaddr)
            {
                bool flag = true;
                while (checkItem(A_tuple, B_tuple) != true)
                {
                    B_oldaddr = B_tuple->tupleAddr;
                    this->table[1]->findNextTuple(this->currentTuple_B, B_tuple);
                    if (B_oldaddr == B_tuple->tupleAddr || B_tuple->tupleAddr == 0)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    fillItem(A_tuple, B_tuple, item);
                    break;
                }
            }
            else
            {
                break;
            }
            A_oldaddr = A_tuple->tupleAddr;
            this->table[0]->findNextTuple(this->currentTuple_A, A_tuple);
        }
        //this->table[0]->releaseEmptyTuple(this->currentTuple_A);
        //this->table[1]->releaseEmptyTuple(this->currentTuple_B);
    }
    else if (this->initialType == SPJ::ITERATORINITIAL)
    {
        SPJItem *A_item = this->spj[0]->buildSPJItem();
        SPJItem *B_item = this->spj[1]->buildSPJItem();
        this->currentSPJItem_A = A_item;
        this->currentSPJItem_B = B_item;
        this->spj[0]->getFirst(A_item);
        while (A_item->use != 0)
        {
            this->spj[1]->getFirst(B_item);
            if (B_item->use != 0)
            {
                bool flag = true;
                while (checkItem(A_item, B_item) != true)
                {
                    this->spj[1]->getNext(B_item);
                    if (B_item->use == 0)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    fillItem(A_item, B_item, item);
                    break;
                }
            }
            else
            {
                break;
            }
            this->spj[0]->getNext(A_item);
        }
        // this->spj[0]->releaseSPJItem(A_item);
        //this->spj[1]->releaseSPJItem(B_item);
    }
    else
    {
        Tuple *A_tuple = this->table[0]->buildEmptyTuple();
        SPJItem *A_item = this->spj[0]->buildSPJItem();
        this->table[0]->findFirstTuple(A_tuple);
        this->currentTuple_A = A_tuple;
        this->currentSPJItem_A = A_item;
        Addr A_oldaddr = 0;
        while (A_tuple->tupleAddr != 0 && A_tuple->tupleAddr != A_oldaddr)
        {
            this->spj[0]->getFirst(A_item);
            if (A_item->use != 0)
            {
                bool flag = true;
                char *str = new char[1000];
                DataUtil::toString(str, A_item->data[0], A_item->dataType[0]);
                while (checkItem(A_tuple, A_item) != true)
                {
                    this->spj[0]->getNext(A_item);
                    char *str = new char[1000];
                    DataUtil::toString(str, A_item->data[0], A_item->dataType[0]);
                    if (A_item->use == 0)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    /*char *str =new char[1000];
                    DataUtil::toString(str,A_item->data[0],A_item->dataType[0]);
                    printf("%s\n",str);
                    DataUtil::toString(str,A_tuple->column[3].data,A_tuple->column[3].field->dataType);
                    printf("%s\n",str);*/
                    fillItem(A_tuple, A_item, item);
                    break;
                }
            }
            A_oldaddr = A_tuple->tupleAddr;
            this->table[0]->findNextTuple(this->currentTuple_A, A_tuple);
        }
        // this->spj[0]->releaseSPJItem(A_item);
    }
}
bool Join::checkItem(Tuple *A_tuple, Tuple *B_tuple)
{
    if (this->conditionLen == 0)
    {
        return true;
    }
    else
    {
        bool flag = true;
        bool exitFlag = false;
        for (int k = 0; k < this->conditionLen; k++)
        {
            string filedNameA = this->condition[k].filedName;
            char *str = new char[this->condition[k].len + 10];
            DataUtil::toString(str, this->condition[k].value, DataTypeFlag::CHAR);
            string filedNameB = str;
            for (int i = 0; i < A_tuple->meta->fieldNum; i++)
            {
                string colname = A_tuple->column[i].field->fname;
                if (colname.compare(filedNameA) == 0)
                {
                    for (int j = 0; j < B_tuple->meta->fieldNum; j++)
                    {
                        colname = B_tuple->column[j].field->fname;
                        if (colname.compare(filedNameB) == 0)
                        {
                            exitFlag = true;
                            flag = CompareType::Compare(A_tuple->column[i].data, B_tuple->column[j].data, this->condition[k].compare, A_tuple->column[i].field->dataType, A_tuple->column[i].field->len);
                            if (!flag)
                                break;
                        }
                    }
                }
                if (!flag)
                    break;
            }
            if (!flag)
                break;
        }
        return flag & exitFlag;
    }
}
bool Join::checkItem(Tuple *A_tuple, SPJItem *item)
{
    if (this->conditionLen == 0)
    {
        return true;
    }
    else
    {
        bool flag = true;
        bool exitFlag = false;
        for (int k = 0; k < this->conditionLen; k++)
        {
            string filedNameA = this->condition[k].filedName;
            char *str = new char[this->condition[k].len + 10];
            DataUtil::toString(str, this->condition[k].value, DataTypeFlag::CHAR);
            string filedNameB = str;
            for (int i = 0; i < A_tuple->meta->fieldNum; i++)
            {
                string colname = A_tuple->column[i].field->fname;
                if (colname.compare(filedNameA) == 0)
                {
                    for (int j = 0; j < item->fieldNum; j++)
                    {
                        colname = item->fieldName[j];
                        if (colname.compare(filedNameB) == 0)
                        {
                            exitFlag = true;
                            // char*str=new char[item->len[j]+10];
                            //DataUtil::toString(str,item->data[j],DataTypeFlag::CHAR);
                            flag = CompareType::Compare(A_tuple->column[i].data, item->data[j], this->condition[k].compare, A_tuple->column[i].field->dataType, A_tuple->column[i].field->len);
                            if (!flag)
                                break;
                        }
                    }
                }
                if (!flag)
                    break;
            }
            if (!flag)
                break;
        }
        return flag & exitFlag;
    }
}
bool Join::checkItem(SPJItem *A_item, SPJItem *B_item)
{
    if (this->conditionLen == 0)
    {
        return true;
    }
    else
    {
        bool flag = true;
        bool exitFlag = false;
        for (int k = 0; k < this->conditionLen; k++)
        {
            string filedNameA = this->condition[k].filedName;
            char *str = new char[this->condition[k].len + 10];
            DataUtil::toString(str, this->condition[k].value, DataTypeFlag::CHAR);
            string filedNameB = str;
            for (int i = 0; i < A_item->fieldNum; i++)
            {
                string colname = A_item->fieldName[i];
                if (colname.compare(filedNameA) == 0)
                {
                    for (int j = 0; j < B_item->fieldNum; j++)
                    {
                        colname = B_item->fieldName[j];
                        if (colname.compare(filedNameB) == 0)
                        {
                            exitFlag = true;
                            flag = CompareType::Compare(A_item->data[i], B_item->data[j], this->condition[k].compare, B_item->dataType[j], B_item->len[j]);
                            if (!flag)
                                break;
                        }
                    }
                }
                if (!flag)
                    break;
            }
            if (!flag)
                break;
        }
        return flag & exitFlag;
    }
}
void Join::fillItem(Tuple *A_tuple, Tuple *B_tuple, SPJItem *item)
{
    if (this->columnNum == 0)
    {
        //        if(this->conditionLen==0){
        this->columnNum = A_tuple->meta->fieldNum + B_tuple->meta->fieldNum;
        //        }else{
        //            int cnt=A_tuple->meta->fieldNum;
        //            for(int j=0;j<A_tuple->meta->fieldNum;j++){
        //                for(int i=0;i<this->conditionLen;i++){
        //                    string columnName=this->condition[i].filedName;
        //                    string ss=A_tuple->column[j].field->fname;
        //                    if(columnName.compare(ss)==0){
        //                        cnt--;
        //                        break;
        //                    }
        //                }
        //            }
        //            this->columnNum=cnt+B_tuple->meta->fieldNum;
        //        }
        delete item;
        item = buildSPJItem();
    }
    int cnt = 0;
    for (int j = 0; j < A_tuple->meta->fieldNum; j++)
    {
        item->fieldName[cnt] = A_tuple->column[j].field->fname;
        if (item->data[cnt] == 0)
            item->data[cnt] = new Byte[A_tuple->column[j].field->len];
        memcpy(item->data[cnt], A_tuple->column[j].data, A_tuple->column[j].field->len);
        item->dataType[cnt] = A_tuple->column[j].field->dataType;
        item->len[cnt++] = A_tuple->column[j].field->len;
    }
    for (int j = 0; j < B_tuple->meta->fieldNum; j++)
    {
        //            bool flag=false;
        //            for(int k=0;k<this->conditionLen;k++){
        //                string columnName=this->condition[k].filedName;
        //                string ss=B_tuple->column[j].field->fname;
        //                if(columnName.compare(ss)==0){
        //                    flag=true;
        //                    break;
        //                }
        //            }
        //            if(flag) continue;
        item->fieldName[cnt] = B_tuple->column[j].field->fname;
        if (item->data[cnt] == 0)
            item->data[cnt] = new Byte[B_tuple->column[j].field->len];
        memcpy(item->data[cnt], B_tuple->column[j].data, B_tuple->column[j].field->len);
        item->dataType[cnt] = B_tuple->column[j].field->dataType;
        item->len[cnt++] = B_tuple->column[j].field->len;
    }
    item->use = 1;
}
void Join::fillItem(SPJItem *A_item, SPJItem *B_item, SPJItem *item)
{
    if (this->columnNum == 0)
    {
        //  if(this->conditionLen==0){
        this->columnNum = A_item->fieldNum + B_item->fieldNum;
        //        }else{
        //            int cnt=A_item->fieldNum;
        //            for(int j=0;j<A_item->fieldNum;j++){
        //                for(int i=0;i<this->conditionLen;i++){
        //                    string columnName=this->condition[i].filedName;
        //                    string ss=A_item->fieldName[j];
        //                    if(columnName.compare(ss)==0){
        //                        cnt--;
        //                        break;
        //                    }
        //                }
        //            }
        //            this->columnNum=cnt+B_item->fieldNum;
        //        }
        delete item;
        item = buildSPJItem();
    }
    int cnt = 0;
    for (int j = 0; j < A_item->fieldNum; j++)
    {
        item->fieldName[cnt] = A_item->fieldName[j];
        if (item->data[cnt] == 0)
            item->data[cnt] = new Byte[A_item->len[j]];
        memcpy(item->data[cnt], A_item->data[j], A_item->len[j]);
        item->dataType[cnt] = A_item->dataType[j];
        item->len[cnt++] = A_item->len[j];
    }
    for (int j = 0; j < B_item->fieldNum; j++)
    {
        //            bool flag=false;
        //            for(int k=0;k<this->conditionLen;k++){
        //                string columnName=this->condition[k].filedName;
        //                string ss=B_item->fieldName[j];
        //                if(columnName.compare(ss)==0){
        //                    flag=true;
        //                    break;
        //                }
        //            }
        //            if(flag) continue;
        item->fieldName[cnt] = B_item->fieldName[j];
        if (item->data[cnt] == 0)
            item->data[cnt] = new Byte[B_item->len[j]];
        memcpy(item->data[cnt], B_item->data[j], B_item->len[j]);
        item->dataType[cnt] = B_item->dataType[j];
        item->len[cnt++] = B_item->len[j];
    }
    item->use = 1;
    //}
}
void Join::fillItem(Tuple *A_tuple, SPJItem *B_item, SPJItem *item)
{
    if (this->columnNum == 0)
    {
        //   if(this->conditionLen==0){
        this->columnNum = A_tuple->meta->fieldNum + B_item->fieldNum;
        //        }else{
        //            int cnt=B_item->fieldNum;
        //            for(int j=0;j<B_item->fieldNum;j++){
        //                for(int i=0;i<this->conditionLen;i++){
        //                    string columnName=this->condition[i].filedName;
        //                    string ss=B_item->fieldName[j];
        //                    if(columnName.compare(ss)==0){
        //                        cnt--;
        //                        break;
        //                    }
        //                }
        //            }
        //            this->columnNum=cnt+A_tuple->meta->fieldNum;
        //    }
        delete item;
        item = buildSPJItem();
    }
    int cnt = 0;
    //for(int i=0;i<item->fieldNum;i++){
    for (int j = 0; j < A_tuple->meta->fieldNum; j++)
    {
        item->fieldName[cnt] = A_tuple->column[j].field->fname;
        if (item->data[cnt] == 0)
            item->data[cnt] = new Byte[A_tuple->column[j].field->len];
        memcpy(item->data[cnt], A_tuple->column[j].data, A_tuple->column[j].field->len);
        item->dataType[cnt] = A_tuple->column[j].field->dataType;
        item->len[cnt++] = A_tuple->column[j].field->len;
    }
    for (int j = 0; j < B_item->fieldNum; j++)
    {
        //            bool flag=false;
        //            for(int k=0;k<this->conditionLen;k++){
        //                string columnName=this->condition[k].filedName;
        //                string ss=B_item->fieldName[j];
        //                if(columnName.compare(ss)==0){
        //                    flag=true;
        //                    break;
        //                }
        //            }
        //            if(flag) continue;
        item->fieldName[cnt] = B_item->fieldName[j];
        if (item->data[cnt] == 0)
            item->data[cnt] = new Byte[B_item->len[j]];
        memcpy(item->data[cnt], B_item->data[j], B_item->len[j]);
        //            char *ss =new char[1000];
        //            DataUtil::toString(ss,B_item->data[j],B_item->dataType[j]);
        item->dataType[cnt] = B_item->dataType[j];
        item->len[cnt++] = B_item->len[j];
    }
    item->use = 1;
    //  }
}
void Join::initNestLoopJoin()
{
    if (this->initialType == SPJ::TABLEINITIAL)
    {
    }
}
void Join::initHashJoin()
{
}
void Join::initSortJoin()
{
}
void Join::initIndexJoin()
{
}
