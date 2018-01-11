#ifndef BPTREE_H_INCLUDED
#define BPTREE_H_INCLUDED
#include <queue>
#include "../common.h"
#include "Index.h"
#define MAX_KEY_SIZE 451 //31//451
#define MAX_ADDR_SIZE 452 //32//452
#define BPTNODE_MAGIC 0x63
typedef struct IndexMetaItem IndexMetaItem;
class BPTNodeType
{
public:
    static const Byte hasData = 0x01;
    static const Byte isRoot = 0x02;
};
/**
 * We only consider the tree built by add element one by one,
 * and will consider build by sort-merge in future.
 */
 typedef struct BPTNode
 {
    //Byte magic
    Byte fid;//在域id为fid的属性上建立索引
    Byte nodeType;//该节点的类型即索引节点类型编号
    //Byte magic
    int keyNum;//该节点中关键字的个数
    // ushort
    Addr parentAddr;//指向的父节点的地址
    Addr previous;//叶子节点中指向前一个节点的地址
    Addr next;//叶子节点中指向下一个节点的地址
    Byte keys[MAX_KEY_SIZE][8];//一个节点中的关键字
    // keys[k] left addr is children[k], right addr is children[k+1] if node is a non-leaf node
    // keys[k]'s tuple address is children[k], if node is a leaf node.
    Addr children[MAX_ADDR_SIZE];//一个结点中地址

    BPTNode* parent;//指向该节点的父亲节点指针
    BPTNode* child;//指向该节点的孩子节点的指针
    Addr pageNo;//该页的地址
 } BPTNode;//别名

class BPTree:public Index//BPT索引的一个页
{
public:
    BPTree(IndexSegment* IndexSegment,Byte fid,Addr addr,IndexMetaItem* itm);
    void create();
    void load();
    void destroyMySelf();
    IndexIterator* findByKey(void* key);
    IndexIterator* findByRange(void* key1,void* key2);
    void destoryIterator(IndexIterator* iterator);
    Addr insertElem(IndexItem* item,bool check = true);
    Addr deleteElem(IndexItem* item);
    IndexItem* buildItem();
   void releaseIndexItem(IndexItem* item);
   void releaseAll();
   void deletefromnoleaf(BPTNode* node);
   void printNode(BPTNode* node);
   void printTreeBFS();
   int insertElemAtPos(IndexItem* item,BPTNode* node,int pos);
   int insertNonLeafAtPos(IndexItem* item,BPTNode* node,int pos);
    Addr searchBPTNode(BPTNode* node,Byte* data);//在node节点中找到数据为data的地址从前往后找
    Addr searchBPTNode2(BPTNode* node,Byte* data);//在node节点中找到数据为data的地址从后往前找
    int  findLowBound(Byte* data,BPTNode* node);//找到node节点中数据为data的值的编号从前往后朝
    int findUpBound(Byte* data,BPTNode* node);//找到node节点中数据为data的值的编号从后往前找
    ~BPTree();



    class BPTIterator:public IndexIterator//定义的一个BPT的迭代器
    {
    public:
        void findFirst(IndexItem* item);
        void findNext(IndexItem* item);
        bool hasNext();
        friend class BPTree;
    private:
        BPTIterator(Addr addr1,int offset1,Addr addr2,int offset2,BPTree* bptree);
        ~BPTIterator();
        Addr begin;//开始的地址
        Addr end;//结束的地址
        int head;//头编号
        int tail;//尾编号
        BPTNode* currentNode;//当前节点
        int cursor;
        BPTree* tree;  //b树的节点地址
        bool knownEmpty;//判断其是否为空
    };

protected:
    IndexMetaItem* item; //索引元组
    BPTNode* root;//b树根节点
    Byte dataType;//节点类型
private:
    short transNodeToFrame(BPTNode* node,BufferFrame* frame);//将一个头节点为node的BPT写到一个页中
    short transFrameToNode(BufferFrame* frame,BPTNode* node);//将一个存着一棵BPT的页面转化成为一棵树，并将该树的头节点存入node节点中。
    void freeNode(Addr pageAddr);
    Addr getNewBPTNode(BPTNode* node,Byte nodeType);//得到一个新的BPT节点的地址
    void getBPTNode(BPTNode* node,Addr addr);//得到一个地址为addr的节点，并将节点存在node里。
    void leafcpy(BPTNode* dest,BPTNode* src,int dest_offset,int src_offset,int len);//
    void nonleafcpy(BPTNode* dest,BPTNode* src,int dest_offset,int src_offset,int len);
    void insertNodeRecursively(Addr addr,IndexItem* item);
    void deleteElementFromNode(Addr addr,IndexItem* item);
    void deleteElementFromNonLeafNodeByAddress(Addr addr,IndexItem* item);
    void mergeTwo(Addr leftAddr,Addr rightAddr);
    void editItem(Addr addr,IndexItem* item,IndexItem* item2);
    int findAddressPosition(BPTNode* node,Addr addr);
    void getSiblingAddress(BPTNode* node,Addr& leftAddr,Addr& rightAddr);
 //   void insertNonLeafRecursively(Addr addr,IndexItem* item);
   void flushNode(BPTNode* node);
   void changeRoot(BPTNode* node);
    bool created;//是否被创建
    bool loaded;//是否被载入内存
    int cnt;
    Addr splitTime;
};


#endif // BPTREE_H_INCLUDED
