#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include <stdio.h>
#include "parser/parser.h"

 query_tree queryTree; // 全局查询树
 meta_field mfList[MAX_MF_LIST]; // 全局MF属性列
 meta_field_char mfcList[MAX_MFC_LIST]; //全局MFC属性列

 int mfListCursor; // 当创建一个表时，当前mf属性的游标
 int mfcListCursor;// 当创建一个表时，当前mfc属性的游标
 //int currentTableCursor; // 当DROP,SELECT,UPDATE一个表时，用来查找已有的表的游标
 int currentTableListNum;// 现有表的数量
// FILE * currentFp; // 当DROP,UPDATE,SELECT一个表时，用来记录当前表的文件指针。
currentTableFp ctfp;//当DROP,UPDATE,SELECT一个表时，用来记录当前表的文件指针。
fromList currentTableList[MAX_TABLE_LIST]; // 当前所有表的列表
tempTuple ttit; // temp tuple to insert, 临时元组，即将插入
deleteWhere dw;// 记录delete语句的where
#endif // GLOBAL_H_INCLUDED
