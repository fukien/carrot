#ifndef FREEBUFFER_H_INCLUDED
#define FREEBUFFER_H_INCLUDED
#include "../common.h"
/**
 * 空闲空间管理类。当数据库的页load进内存时，需要在内存中开辟一块空间。
 * 但频繁地new与delete不利于系统性能的提升。
 * 这个类负责向内存申请页面空间，并提交给页面利用；
 * 当页面被释放后，空闲区域并不delete，而是以链表的形式缓存在该类中，
 * 下次页面申请空间空间时，先返回链表中的项目，链表中项没有时，再向内存申请空间。
 */
typedef struct Buffer
{
    Byte data[PAGE_SIZE];
    void *page;
    int state;
    Buffer *next;
} Buffer;

class FreeBuffer
{
  public:
    FreeBuffer();
    Buffer *allocBuffer();
    void freeBuffer(Buffer *buffer);
    ~FreeBuffer();

  private:
    Buffer *head;
    Buffer *newBuffer();
};

#endif // FREEBUFFER_H_INCLUDED
