#ifndef TEMPSEGMENT_H_INCLUDED
#define TEMPSEGMENT_H_INCLUDED
//8+8=16
typedef struct tempitem
{
    void* value;
    Addr keyaddr;
}tempitem;
//16+16x=7272
typedef struct tempnode
{
    //Byte magic;
    Addr nextAddr;
    int length;
    int type;
   // int fid;
    tempitem arr[452];

    Addr nodeaddr;
}tempnode;

class tempSegment
{
public:
    tempnode *node;
    tempSegment(BufferManager* mgr,DirectorySegment* dir,DataSegment* dataseg);
    bool WriteIntoTemp(tempnode *node,tempitem *item);
    Addr creatTemp(BufferManager* mgr,DirectorySegment* dir);
    void transTemptoFrame(BufferFrame* frame,tempnode *item);
    void transFrametoTemp(BufferFrame* frame,tempnode *item);
    short readtempItem(tempitem* item,Byte* data);
    short writetempItem(tempitem* item,Byte* data);
    short findfristItem(BufferFrame* frame,tempnode* node);
    short findnextItem(BufferFrame* frame,short offset,tempnode *node);
};
#endif // TEMPSEGMENT_H_INCLUDED
