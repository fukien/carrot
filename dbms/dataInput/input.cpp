#include "inputer.h"
    bool DataInput::open(char* name)
    {
        fd =fopen(name,"r");
    }
    int DataInput::findNext(char** matrix)
    {
        int cln = 0;
        int pos = 0;
        char ch = 0;
        while((ch =fgetc(fd)) != '\n') {
            if(ch=='|'){
                    matrix[cln][pos]='\0';
                    cln++;
                    pos=0;
                    continue;
            }else if(ch==EOF)
            {
                matrix[cln][pos]='\0';
                cln++;
                break;
            }else
            {
                matrix[cln][pos]=ch;
                pos++;
            }
        }
        return cln;
    }
    void DataInput::close()
    {
        fclose(fd);
    }
