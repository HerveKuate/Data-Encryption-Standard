#include "../include/RKeyFunction.h"

char* RKeyFunction(char *table4, char *pc1right_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table4[(int)pc1right_table[i]-1];
    }

    return result;
}
