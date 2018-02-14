#include "XORFunction.h"
#include <iostream>

using namespace std;

char* XOR(char *RiTable, char *KeyiTable, long tabsize)
{
    char *result = new char[tabsize];

    for(long i=0; i <tabsize;i++)
    {
        if((int)RiTable[i] == (int)KeyiTable[i])
            result[i]=0;
        else result[i]=1;
    }

    return result;
}
