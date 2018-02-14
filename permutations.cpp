#include "permutations.h"

char* permute(char *table, char *perm_table, long tabsize)
{
    char *result = new char[tabsize];

    for(int i=0; i <tabsize;i++)
    {
        result[i]=table[(int)perm_table[i]-1];
    }

    return result;
}
