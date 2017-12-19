#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <dirent.h>
#include "parser/parser.h"
#include "execution/QueryExecutor.h"
#include "execution/CreateExecutor.h"
#include "execution/DropExecutor.h"
#include "execution/InsertExecutor.h"
#include "execution/UpdateExecutor.h"
#include "execution/DeleteExecutor.h"
#include "execution/SelectExecutor.h"

using namespace std;
extern "C"
{
#include "parser/sql.tab.h"
#include "parser/sql-parser.h"
    //extern int yydebug;
    extern int yylex_init_extra (void* user_defined,yyscan_t* scanner);
    extern void yyset_in  (FILE * in_str ,yyscan_t yyscanner );
}

 extern query_tree queryTree;// 全局查询树
 extern meta_field mfList[MAX_MF_LIST]; // 全局MF属性列
 extern meta_field_char mfcList[MAX_MFC_LIST]; //全局MFC属性列
 extern int mfListCursor; // 当创建一个表时，当前mf属性的游标
 extern int mfcListCursor;// 当创建一个表时，当前mfc属性的游标
// extern int currentTableCursor; // 当DROP,SELECT,UPDATE一个表时，用来查找已有的表的游标
//extern FILE * currentFp; // 当DROP,UPDATE,SELECT一个表时，用来记录当前表的文件指针。
extern currentTableFp ctfp; //当DROP,UPDATE,SELECT一个表时，用来记录当前表的文件指针。
extern int currentTableListNum;// 现有表的数量
extern fromList currentTableList[MAX_TABLE_LIST]; // 当前所有表的列表
extern tempTuple ttit;// temp tuple to insert, 临时元组，即将插入
extern deleteWhere dw;// 记录delete语句的where
extern updateWhere uw;// 记录update语句的where
extern selectWhere sw;// 记录select语句的where

map<int, char*> err_reason;// 全局错误号信息反馈
/**********************************************************
error id 1: SUCCESS, whatever the query is.
error id 0: DEFAULT, whatever the query is.
if an error id is less than 0, it means there is an error.

error id: -5~-1,    error reasons for CREATE
error id: -10~-6,    error reasons for DROP
error id: -15~-11,    error reasons for SELECT
error id: -20~-16,    error reasons for INSERT
error id: -25~-21,    error reasons for UPDATE
error id: -30~-26,    error reasons for DELETEexec INT/NUMBER

error id        error reason
-1                  CREATE FAILED
-6                  DROP FAILED
-11                SELECT FAILED
-12                SELECTION FAILED
-13                PROJECTION FAILED
-14                JOIN FAILED
-16                INSERT FAILED
-21                UPDATE FAILED
-26                DELETE FAILED
**********************************************************/
static void err_id_initialize()
{
    err_reason[1] = "SUCCESS!";
    err_reason[0] = "DEFAULT!";
    err_reason[-1]  = "CREATE TABLE FAILED!";
    err_reason[-6] = "DROP TABLE FAILED!\t TABLE NOT FOUND!!!";
    err_reason[-7] = "DROP TABLE FAILED!\t TABLE FOUND BUT CAN NOT DROP!!!";
    err_reason[-11] = "SELECT FAILED!\t TABLE NOT FOUND!!!";
    err_reason[-12]="SELECTION FAILED!";
    err_reason[-13] = "PROJECTION FAILED!";
    err_reason[-14] = "JOIN FAILED!";
    err_reason[-16] = "INSERT FAILED!\t THE TUPLE FIELD NUMBER DOESN'T MATCH THE FIELD NUMBER OF THE TABLE!!!";
    err_reason[-17] = "INSERT FAILED!\t SOME STRING LENGTH DON'T MATCH THE FIELD LENGTH!!!";
    err_reason[-18] = "INSERT FAILED!\t TABLE NOT FOUND!!!";
    err_reason[-21] = "UPDATE FAILED!\t TABLE NOT FOUND!!!  ";
    err_reason[-26] = "DELETE FAILED!\t TABLE NOT FOUND!!!";
    err_reason[-27] = "DELETE FAILED!\t TABLE FOUND BUT NOT EVEN A SINGLE TUPLE!!!";
    err_reason[-28] = "DELETE FAILED!\t COLUMN TYPE DOESN'T MATCH!!!";
}
int currentTableCount() //获取当前工作路径下的表的数量
 {
     struct dirent *ptr;
     DIR * dir;
     string PATH = "workspace/";
     dir = opendir(PATH.c_str());
     vector<string> files;
     while((ptr=readdir(dir))!=NULL)
     {
         if(ptr->d_name[0] == '.')
         {
             continue;
         }
         files.push_back(ptr->d_name);
     }
     closedir(dir);
     return files.size();
 }
void iniQuery()
{
    /*
    currentTableList[0].name = "haha";
    currentTableList[1].name = "xixi";
    currentTableList[2].name = "xxoo";
    */
    currentTableListNum = currentTableCount(); //得到当前工作目录下的表的数量
    memset(&queryTree,0,sizeof(queryTree)); // 清空查询树
    memset(&ctfp,0,sizeof(ctfp));//清空当前表的指针
    memset(&ttit,0,sizeof(ttit));//清空当前临时元组，为下一次插入作准备
    memset(&dw,0,sizeof(dw));// 清空delete的where
    memset(&uw,0,sizeof(uw));//清空update的where
    memset(&sw,0,sizeof(sw));//清空select的where
    mfListCursor = 0; //置0当前MF属性的游标
    mfcListCursor = 0;//置0当前MFC属性的游标
//    currentTableCursor = 0;
    //currentFp = NULL;// 当DROP,UPDATE,SELECT一个表时，用来记录当前表的文件指针。现对其置空。
  }
void doQuery()
{
    //cout<<currentTableListNum<<endl;
    switch (queryTree.query_type)
    {
        case 1://create
            {
                CreateExecutor * ce = new CreateExecutor();
                ce->execute(queryTree);
                cout<<err_reason[ce->getStatus()]<<endl;
                delete ce;
            }
            break;
        case 2://drop
            {
               DropExecutor*de = new DropExecutor();
                de->execute(queryTree);
                cout<<err_reason[de->getStatus()]<<endl;
                delete de;
            }
            break;
        case 3://insert
            {
                InsertExecutor* ie = new InsertExecutor();
                ie->execute(queryTree);
                if(ie->getStatus() == 1)
                {
                    cout<<"successfully insert " << ie->getChdNum() << " tuple"<<endl;
                }
                    cout<<err_reason[ie->getStatus()]<<endl;
                delete ie;
            }
            break;
        case 4://update
            {
                UpdateExecutor *ue = new UpdateExecutor();
                ue->execute(queryTree);
                if(ue->getStatus() == 1)
                    {
                        cout<<"successfully update " << ue->getChdNum() << "tuple" <<endl;
                    }
                    cout<<err_reason[ue->getStatus()] <<endl;
                    delete ue;
            }
            break;
        case 5://delete
            {
                DeleteExecutor*de = new DeleteExecutor();
                de->execute(queryTree);
                cout<<err_reason[de->getStatus()]<<endl;
                delete de;
            }
            break;
        case 6://select
            {
                SelectExecutor*se = new SelectExecutor();
                se->execute(queryTree);
                cout<<err_reason[se->getStatus()]<<endl;
                delete se;
            }
            break;

        default: // what the hell
            break;
    }
}

int yydebug;
int main(int ac,char** av)
{
  cout<< "WELCOME TO OUR DATABASE: CARROTS !!!"<<endl;
  err_id_initialize();
  FILE *in_f;
  struct psql_state pstate;

  if(ac > 1 && !strcmp(av[1], "-d")) {
    yydebug = 1; ac--; av++;
  }

  memset(&pstate, 0, sizeof(pstate));
  if (yylex_init_extra(&pstate, &pstate.scanner))
  	return 1;

  if(ac > 1) {
    if((in_f = fopen(av[1], "r")) == NULL) {
      perror(av[1]);
      exit(1);
    }
    filename = av[1];
  } else {
    filename = "(stdin)";
    in_f = stdin;
  }

  yyset_in(in_f, pstate.scanner);

  /*
  if(!yyparse(pstate.scanner, &pstate)) {
    printf("SQL parse worked\n");
    return 0;
  } else {
    printf("SQL parse failed\n");
    return 1;
  }
  */
  while (true)
{
    iniQuery();
    cout<<"\nCARROTS >>\t" ;
    if(!yyparse(pstate.scanner, &pstate)) {
    printf("SQL parse worked\n");
    //return 0;
  } else {
    printf("SQL parse failed\n");
    //return 1;
  }
  cout<<endl;
  doQuery();
}
    return 0;
}


