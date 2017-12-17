#ifndef INPUTER_H_INCLUDED
#define INPUTER_H_INCLUDED
#include <cstdio>
#include "../common.h"
class DataInput
{
public:
    bool open(char* name);
    int findNext(char** matrix);
    void close();
private:
    FILE* fd;
};


#endif // INPUTER_H_INCLUDED
