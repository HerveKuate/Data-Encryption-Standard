#include "../include/ShiftKey.h"
#include "../bit_tables.h"
#include <iostream>

using namespace std;

char* ShiftKey(char *table5, int number)
{//To the left
    char temp ;
    int i;
    char *result = new char[28];
//    for(i=0;i<28;i++){
//        result[i] = table5[i];
//    }
    for(int j=0;j<28;j++)
    {
            result[j] = table5[j];
    }

    for(int counter=0;counter<number;counter++){
        temp = result[0];
        for(i=0;i<28-1;i++){
            result[i] = result[i+1];
        }
        result[i] = temp;
        //displayBitTable(result,28); cout << endl;
    }
    return result;
}
