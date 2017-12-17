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
     6  selectfromListNum
    ***********************************************/
typedef struct query_tree{
    int query_type;
    int fromListNum;
    fromList  tableList[MAX_FROM_LIST];
} query_tree;

typedef struct currentTableFp{
    FILE * currentFp;
    char name[MAX_TABLE_NAME_LEN_PARSER];
} currentTableFp;

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


typedef struct whereCondition{
    fromList tabelList[MAX_FROM_LIST];
}whereCondition;

typedef struct deleteFromTable{
    fromList table;
    meta_field_char cmp_mfc_list[MAX_MFC_LIST];
    meta_field  cmp_mf_list[MAX_MF_LIST];
}deleteFromTable;

#endif // PARSER



