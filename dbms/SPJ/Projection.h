#ifndef  PROJECTION_H_INCLUDED
#define PROJECTION_H_INCLUDED
#include"SPJ.h"
#include <string>
#include<map>

class Projection :public SPJ{
public:
    void getNext(SPJItem*item);
    void getFirst(SPJItem * item);
    void initProjection(Table*table,string columnName[],int columnNum);//given the columns, if select* just set columnNum as -1
    void initProjection(SPJ*spj,string columnName[],int columnNum);
    void releaseSPJItem(SPJItem*item);
    SPJItem* buildSPJItem();
    Projection(int type,int initial);//type: operator type; initial : get from the table or the SPJItem
    void fillItem(SPJItem*item,Tuple *tuple);
    void fillItem(SPJItem*item,SPJItem* sourceItem);
    void destroy();
private:
        Byte initialType;//
        Tuple*currentTuple;//now the tuple
        Byte operatorType;
         string*columns;
        int columnNum;
        Byte*dataType;
        SPJ*spj;
        int *fieldList;
        bool fieldflag;//label if get the projection fid
};
#endif // PROJECTION_H_INCLUDED
