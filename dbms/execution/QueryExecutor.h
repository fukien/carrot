#ifndef QUERYEXECUTOR_H_INCLUDED
#define QUERYEXECUTOR_H_INCLUDED
#include <map>
#include "../common.h"
#include "../parser/parser.h"
#include "../table/Table.h"
#include "../table/meta.h"
#include "../util/DataUtil.h"
#include "../SPJ/SPJ.h"
#include "../SPJ/Selection.h"
#include "../SPJ/Join.h"
#include "../SPJ/Projection.h"

#define MAX_CONDITION_LEN 64

 using namespace std;
 extern query_tree queryTree;// 全局查询树
 extern meta_field mfList[MAX_MF_LIST]; // 全局MF属性列
 extern meta_field_char mfcList[MAX_MFC_LIST]; //全局MFC属性列
 extern int mfListCursor; // 当创建一个表时，当前mf属性的游标
 extern int mfcListCursor;// 当创建一个表时，当前mfc属性的游标
// extern int currentTableCursor; // 当DROP,SELECT,UPDATE一个表时，用来查找已有的表的游标
// extern FILE *currentFp; // 当DROP,UPDATE,SELECT一个表时，用来记录当前表的文件指针。
 extern currentTableFp ctfp; //当DROP,UPDATE,SELECT一个表时，用来记录当前表的文件指针。
 extern int currentTableListNum;// 已有表的数量
 extern fromList currentTableList[MAX_TABLE_LIST]; // 当前所有表的列表
 extern tempTuple ttit;// temp tuple to insert, 临时元组，即将插入
 extern deleteWhere dw;// 记录delete语句的where
extern updateWhere uw;// 记录update语句的where
extern selectWhere sw;// 记录select语句的where

class QueryExecutor
{
public:
    QueryExecutor();
    ~QueryExecutor();
     int execute();
     void setStatus(int a);
     int getStatus();
     char workDir[64];
private:
     int status;
};

#endif //  QUERYEXECUTOR_H_INCLUDED
