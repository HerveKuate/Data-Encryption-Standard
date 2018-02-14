#include "../include/pc2.h"

char* pc2(char *table3, char *pc2_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table3[(int)pc2_table[i]-1];
    }

    return result;
}
