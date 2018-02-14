#include "../include/LKeyFunction.h"

char* LKeyFunction(char *table2, char *pc1left_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table2[(int)pc1left_table[i]-1];
    }

    return result;
}
