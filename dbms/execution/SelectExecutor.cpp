#include "SelectExecutor.h"
using namespace std;

SelectExecutor::SelectExecutor()
{
     chdNum = 0;
     condCursor = 0;
     fieldNum = 0;
    QueryExecutor::setStatus(0);
    strcpy(QueryExecutor::workDir,"workspace/");
}

SelectExecutor::~SelectExecutor()
{
    chdNum = 0;
    condCursor = 0;
    fieldNum = 0;
    QueryExecutor::setStatus(0);
    memset(QueryExecutor::workDir,'\0',strlen(workDir));
}

void SelectExecutor::setStatus(int a)
{
    QueryExecutor::setStatus(a);
}

int SelectExecutor::getStatus()
{
    return QueryExecutor::getStatus();
}

void SelectExecutor::setChdNum(int a)
{
    chdNum = a;
}

int SelectExecutor::getChdNum()
{
    return chdNum;
}

void SelectExecutor::selectAll()
{
    Table* table = new Table();
    table->open(ctfp.name,false);
    TableMeta * meta = table->getTableMeta();
    FieldPart * fp =  meta->head;
    Tuple*tuple = table->buildEmptyTuple();
    string* column = new string[fp->partNum];
    for(int i =0; i < fp->partNum; i ++)
        {
            column[i] = tuple->column[i].field->fname;
        }

    Projection *proj = new Projection(OperatorType::PROJECTION, SPJ::TABLEINITIAL);
    proj->initProjection(table, column, fp->partNum);

    int cnt = 0;
    SPJItem * item = proj->buildSPJItem();
    proj->getFirst(item);
    while(item->use!=0)
        {
            char *str = new char[1000];
            for(int i =0; i< item->fieldNum &&  item->use != 0; i ++)
                {
                    DataUtil::toString(str,item->data[i],  item->dataType[i]);
                    printf("%s|\t", str);
                }
                printf("\n");
            cnt ++;
            proj->getNext(item);
        }
    if(cnt == 0)
        {
                setStatus(-12);
        }
    setChdNum(cnt);
    setStatus(1);
}


int SelectExecutor::execute(query_tree qt)
{

     if(sw.isAll == 1)//全选
        {
                if(ctfp.currentFp == NULL)
            {
                setStatus(-11);
                return getStatus();
            }
           selectAll();
           return getStatus();
        }


    return getStatus();
}
