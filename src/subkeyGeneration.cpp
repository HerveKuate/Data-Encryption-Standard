#include "../include/subkeyGeneration.h"

char* subkey(char *table6, char *expan_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table6[(int)expan_table[i]-1];
    }

    return result;
}
