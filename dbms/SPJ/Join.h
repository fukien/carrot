#ifndef  JOIN_H_INCLUDED
#define JOIN_H_INCLUDED
#include"SPJ.h"
#include"Selection.h"
#include <string>
#include<map>

class JoinType{
public:
    static const Byte NESTLOOPJOIN=0x01;
    static const Byte SORTJOIN=0x01;
    static const Byte HASHJOIN=0x01;
    static const Byte INDEXJOIN=0x01;
};
class Join :public SPJ{
public:
    void getNext(SPJItem*item);
    void getFirst(SPJItem * item);
    Join(int type,int inital,Byte joinType);
    void initJoin(Table**table,int tableLen,SPJ**spj,int spjLen,Condition conditionList[],int conditionLen);//given the columns, if select* just set columnNum as -1
    //void initJoin(SPJ*spj,string columnName[],int columnNum);
    void initNestLoopJoin();
    void initHashJoin();
    void initSortJoin();
    void initIndexJoin();
    void releaseSPJItem(SPJItem*item);
    SPJItem* buildSPJItem();
    Join(int type,int initial);//type: operator type; initial : get from the table or the SPJItem
    void fillItem(Tuple*A_tuple,Tuple*B_tuple,SPJItem*item);
    void fillItem(SPJItem*A_item,SPJItem* B_item,SPJItem*item);
    void fillItem(Tuple*A_tuple,SPJItem*B_item,SPJItem*item);
    bool checkItem(Tuple*A_tuple,Tuple*B_tuple);
    bool checkItem(SPJItem*A_item,SPJItem* B_item);
    bool checkItem(Tuple*A_tuple,SPJItem*A_item);
    void NestLoopJoinGetFirst(SPJItem*item);
    void NestLoopJoinGetNext(SPJItem*item);
    void HashJoinGetFirst(SPJItem*item);
    void HashJoinGetNext(SPJItem*item);
    void SortJoinGetFirst(SPJItem*item);
    void SortJoinGetNext(SPJItem*item);
    void IndexJoinGetFirst(SPJItem*item);
    void IndexJoinGetNext(SPJItem*item);
    void destroy();
private:
        Byte initialType;//only table ,only iterator, table and iterator
        Byte operatorType;
        Byte*dataType;
        Byte joinType;
        SPJ**spj;
        Table**table;
        Condition*condition;
        int columnNum;
        int conditionLen;
        int *fieldList;
        bool fieldflag;//label if get the projection fid
        Byte tableLen;
        Byte spjLen;
        SPJItem*currentSPJItem_A;
        SPJItem*currentSPJItem_B;
        Tuple*currentTuple_A;
        Tuple*currentTuple_B;
};
#endif // JOIN_H_INCLUDED
