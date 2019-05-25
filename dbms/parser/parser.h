#ifndef PARSER
#define PARSER
#include "../common.h"
#define MAX_MFC_LIST 10
#define MAX_MF_LIST 10
#define MAX_FROM_LIST 10
#define MAX_TABLE_LIST 20
#define MAX_FIELD_NAME_LEN 64
#define MAX_TABLE_NAME_LEN_PARSER 64
#define MAX_TYPE_FILED_NUM 64
#define MAX_CHAR_VARCHAR_LENGTH 64
#define MAX_WHERE_ITEM_NUM 64
#define MAX_WHERE_ITEM_LENGTH 64
#include<stdio.h>
/*
typedef struct create_drop_select{
    int status;
} create_drop_select;

typedef struct delete_insert_update{
    int status;
    int chd_num;
} delete_insert_update;
*/
typedef struct meta_field{
    Byte dataTypeFlag;
    char fieldName[MAX_FIELD_NAME_LEN];
}meta_field;

typedef struct meta_field_char{
    Byte dataTypeFlag;
    char fieldName[MAX_FIELD_NAME_LEN];
    int len;
} meta_field_char;

typedef struct fromList{
    char name[MAX_TABLE_NAME_LEN_PARSER];
    int fieldNum;
    meta_field_char mfc_list[MAX_MFC_LIST];
    meta_field  mf_list[MAX_MF_LIST];
} fromList;

    /************************************************
    query_type:
     0  default
     1  create
     2  drop
     3  insert
     4  update
     5  delete
     6  select
     7  join
    ***********************************************/
typedef struct query_tree{
    int query_type;
    int fromListNum;
    fromList  tableList[MAX_FROM_LIST];
} query_tree;

typedef struct currentTableFp{
    FILE * currentFp;
    char name[MAX_TABLE_NAME_LEN_PARSER];
} currentTableFp; //DROP, SELECT,UPDATE

typedef struct tempTuple{
    int fieldNum;
    int intNum;
    int floatNum;
    int stringNum;
    int intField[MAX_TYPE_FILED_NUM];
    float floatField[MAX_TYPE_FILED_NUM];
    char stringField[MAX_TYPE_FILED_NUM][MAX_CHAR_VARCHAR_LENGTH];
    char tableName[MAX_TABLE_NAME_LEN_PARSER];
} tempTuple;


typedef struct deleteWhere{
    /*
    char field[MAX_TYPE_FILED_NUM][MAX_FIELD_NAME_LEN];
    //运算符: 0DEFAULT, 1ADD, 2SUB, 3MUL, 4DIV 5MOD
    int optType[MAX_TYPE_FILED_NUM];
    //比较符： 0 DEFAULT, 1<, 2>, 3 !=, 4=
    int cmpType[MAX_TYPE_FILED_NUM];
    //逻辑符: 0 DEFAULT,1AND, 2OR
    int logicType[MAX_TYPE_FILED_NUM];
 */
    char tableName[MAX_TABLE_NAME_LEN_PARSER];
    char where[MAX_WHERE_ITEM_NUM][MAX_WHERE_ITEM_LENGTH];//where子句

    /***********************************************************
    记录数据类型.
    0-COLUMN, 1-INT, 2-FLOAT, 3-STRING,
    4-ADD, 5-SUB, 6-MUL, 7-DIV, 8-MOD,
    9-AND, 10-OR, 11- WHERE(END), 12-SMALLERTHAN,
    13- GREATERTHAN, 14-NOTEQUAL, 15-EQUAL, 16-NEG,
    17-XOR, 18-NOT, 19-LIKE, 20-EXISTS,
    21-IN_SELECT, 22-BETWEEN, 23-IS_NULL, 24-SMALLER_OR_EQUAL,
    25_GREATER_OR_EQUAL
    ********************************************************/
    int type[MAX_WHERE_ITEM_LENGTH];
    int whereCursor;//where子句的游标
}deleteWhere;

typedef struct updateWhere{
    char tableName[MAX_TABLE_NAME_LEN_PARSER];
    char where[MAX_WHERE_ITEM_NUM][MAX_WHERE_ITEM_LENGTH];//where子句

    /***********************************************************
    记录数据类型.
    0-COLUMN, 1-INT, 2-FLOAT, 3-STRING,
    4-ADD, 5-SUB, 6-MUL, 7-DIV, 8-MOD,
    9-AND, 10-OR, 11- WHERE(END), 12-SMALLERTHAN,
    13- GREATERTHAN, 14-NOTEQUAL, 15-EQUAL, 16-NEG,
    17-XOR, 18-NOT, 19-LIKE, 20-EXISTS,
    21-IN_SELECT, 22-BETWEEN, 23-IS_NULL, 24-SMALLER_OR_EQUAL,
    25_GREATER_OR_EQUAL, 26- ASSIGN
    ********************************************************/
    int type[MAX_WHERE_ITEM_LENGTH];
    int whereCursor;//where子句的游标
    int ass;//ASSIGNED 1, NOT ASSIGNED 0
    char assWhere[MAX_WHERE_ITEM_NUM][MAX_WHERE_ITEM_LENGTH];// FOR ASSIGN
    int assType[MAX_WHERE_ITEM_NUM];
    int assCursor;
}updateWhere;

typedef struct selectWhere{
    char tableName[MAX_TABLE_NAME_LEN_PARSER];
    char where[MAX_WHERE_ITEM_NUM][MAX_WHERE_ITEM_LENGTH];
    int type[MAX_WHERE_ITEM_LENGTH];
    int whereCursor;//where子句的游标
    int isAll; //0 not, 1 -all, if projects all columns

    int isCount; // 0 not count, 1 count

    char fieldList[MAX_WHERE_ITEM_NUM][MAX_WHERE_ITEM_LENGTH];
    int fieldNum;
    int isProj; // 0-not finished projection, 1-finished projection

    //int endWhereFlag; // this flag is used for limit or sort ; 0  where not ended; 1 where ended
    int isLimit; // 0 not limit, 1 limit
    int limit;
}selectWhere;

typedef struct joinWhere{
    char tableList[MAX_TABLE_LIST][MAX_TABLE_NAME_LEN_PARSER];//记录join的表格
    int tableCursor;//记录table的数量

    char fieldList[MAX_WHERE_ITEM_NUM][MAX_WHERE_ITEM_LENGTH];//记录投影的属性
    int fieldNum;//记录投影属性数目

    char where[MAX_WHERE_ITEM_NUM][MAX_WHERE_ITEM_LENGTH];
    int type[MAX_WHERE_ITEM_LENGTH];
    int whereCursor;

    int isCount; // 0 not count, 1 count

    int isAll; //0 not, 1 -all, if projects all columns
    int isProj; // 0-not finished projection, 1-finished projection

    //int endWhereFlag; //this flag is used for limitor sort; 0 where not ended; 1 where ended
    int isLimit; // 0 not limit, 1 limit
    int limit;
}joinWhere;
#endif // PARSER



