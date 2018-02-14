#include "../include/expansion.h"

char* expans(char *table1, char *expan_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table1[(int)expan_table[i]-1];
    }

    return result;
}
