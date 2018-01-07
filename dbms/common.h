#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
/**
 * 公共头文件
 * 进行一系列宏定义，类型定义
 */
//#define PAGESIZE
//#define DEBUG
#define DEBUG_INDEX
/**
 * 定义页面大小为8KB(Byte)
 */
#define PAGE_SIZE 1024*8
/**
 * 该页面大小在二进制下需要13位地址表示
 */
#define PAGE_ADDR_LEN 13
/**
 * 页面掩码，用于PAGE_ID、PAGE_ADDR和PAGE_ID两个宏函数，分别可以：
 * 根据地址取出页号、根据页号取出页地址，以及根据地址取出该地址的页内偏移
 */
#define PAGE_MASK (PAGE_SIZE-1)
#define PAGE_ID(addr)  ((addr&(~PAGE_MASK))>>PAGE_ADDR_LEN)
#define PAGE_ADDR(pageNo) (pageNo<<PAGE_ADDR_LEN)
#define PAGE_OFFSET(addr) (addr&PAGE_MASK)
/**
 * 页头大小，一个short（2byte）表示页面使用字节数，一个Flag表示标记。目前标记了块类型。
 */
#define PAGE_USED 2u
#define PAGE_FLAG 2u
/**
 * 页首部bitmap长度，909Byte控制7272Byte，1Byte（8bit）控制8个Byte
 */
#define PAGE_HEAD_BODY 909u
#define PAGE_META_HEAD (PAGE_USED+PAGE_FLAG)
/**
 * 为了使页首部对齐，增加3个空位
 */
#define PAGE_ALIGN 3u
#define PAGE_HEAD_LEN (PAGE_HEAD_BODY+PAGE_META_HEAD)
#define PAGE_BODY_LEN (PAGE_SIZE-PAGE_HEAD_LEN)

/**
 * 用于数据库地址表示
 */
typedef long long Addr;  // printf lld
/**
 * 用于页内偏移地址表示
 */
typedef short PageAddr;  // printf d
typedef unsigned long long uint64; // %llu
typedef unsigned int uint; // %u
typedef unsigned short ushort; // %u
/**
 * 用于构成数据字节
 */
typedef unsigned char Byte; // %u
/**
 * 枚举类，表示BufferManager的缓冲策略。
 */
 enum StrategyInBuffer
 {
     NONE, FIFO, ClOCK, LRU, LFU
 };

#endif // COMMON_H_INCLUDED
