#include <iostream>
#include <string>
 #include <fstream>

using namespace std;

void displayBitTable(char *table, long tabsize)
{

    for(long i=0; i < tabsize;i++)
    {
        cout << (int)table[i];
        if(((i+1)%4)==0)
        {
            cout << " ";
        }
    }
}

void displayToSBox(char *table, long tabsize)
{
    ofstream SBoxDumpFile;
    SBoxDumpFile.open ("SboxDump.txt", std::ios::app);

    for(long i=0; i < tabsize;i++)
    {
        SBoxDumpFile << (int)table[i];
        if(((i+1)%4)==0)
        {
            SBoxDumpFile << " ";
        }
    }

    SBoxDumpFile << " / ";

    long hexsize = tabsize/4;
   char hexcodes[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

   for (long i=0; i < hexsize;i++)
   {
       long value=0;

       for(long j=0; j <4; j++)
       {
            value = (2*value)+table[4*i+j];
       }

       SBoxDumpFile << hexcodes[value];

        if(((i+1)%4)==0)
        {
            SBoxDumpFile << " ";
        }
   }
   SBoxDumpFile<<endl;
      SBoxDumpFile.close();
}

void displayToDES(char *table, long tabsize)
{
    ofstream DESDumpFile;
    DESDumpFile.open ("DES - dump.txt", std::ios::app);

    for(long i=0; i < tabsize;i++)
    {
        DESDumpFile << (int)table[i];
        if(((i+1)%4)==0)
        {
            DESDumpFile << " ";
        }
    }

    DESDumpFile << " / ";

    long hexsize = tabsize/4;
   char hexcodes[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

   for (long i=0; i < hexsize;i++)
   {
       long value=0;

       for(long j=0; j <4; j++)
       {
            value = (2*value)+table[4*i+j];
       }

       DESDumpFile << hexcodes[value];

        if(((i+1)%4)==0)
        {
            DESDumpFile << " ";
        }
   }
   DESDumpFile<<endl;
      DESDumpFile.close();
}


void  displayAsHex(char *table, long tabsize)
{
   long hexsize = tabsize/4;
   char hexcodes[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

   for (long i=0; i < hexsize;i++)
   {
       long value=0;

       for(long j=0; j <4; j++)
       {
            value = (2*value)+table[4*i+j];
       }

       cout << hexcodes[value];

        if(((i+1)%4)==0)
        {
            cout << " ";
        }
   }
}
