#include "sbox_helper.h"
#include "bit_tables.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

char *sbox(char *table, char s_boxes[8][64])
{

    ofstream SBoxDumpFile;
  SBoxDumpFile.open ("SboxDump.txt");



    char **Sliced = new char*[8];
    char *result = new char[32];
    char OutputBlock1;
    char **OutputBlock2 = new char*[8];

    for(int i= 0; i < 8; i++){
        Sliced[i] = new char[6];
    }

    int counter = 0;
    for(int i= 0; i < 8; i++){
        for(int j= 0; j < 6; j++){
            //cout << "sliced: "<<table[counter] << endl;
            Sliced[i][j] = table[counter++];
        }
        SBoxDumpFile<<"Sliced["<< i <<"] = ";
        SBoxDumpFile.close();
        displayToSBox(Sliced[i],6);
        SBoxDumpFile.open ("SboxDump.txt", std::ios::app);
    }
    SBoxDumpFile << "Writing this to a file.\n";
      int row;
      int col;
        for(int i= 0; i < 8; i++){
      if((int)Sliced[i][0] == 0 && (int)Sliced[i][5] == 0 ) row = 1;
      else if((int)Sliced[i][0] == 0 && (int)Sliced[i][5] == 1 ) row = 2;
      else if((int)Sliced[i][0] == 1 && (int)Sliced[i][5] == 0 ) row = 3;
      else if((int)Sliced[i][0] == 1 && (int)Sliced[i][5] == 1 ) row = 4;

      if((int)Sliced[i][1] == 0 && (int)Sliced[i][2] == 0 && (int)Sliced[i][3] == 0 && (int)Sliced[i][4] == 0 ) col = 1;
     else if((int)Sliced[i][1] == 0 && (int)Sliced[i][2] == 0 && (int)Sliced[i][3] == 0 && (int)Sliced[i][4] == 1 ) col = 2;
     else if((int)Sliced[i][1] == 0 && (int)Sliced[i][2] == 0 && (int)Sliced[i][3] == 1 && (int)Sliced[i][4] == 0 ) col = 3;
     else if((int)Sliced[i][1] == 0 && (int)Sliced[i][2] == 0 && (int)Sliced[i][3] == 1 && (int)Sliced[i][4] == 1 ) col = 4;
     else if((int)Sliced[i][1] == 0 && (int)Sliced[i][2] == 1 && (int)Sliced[i][3] == 0 && (int)Sliced[i][4] == 0 ) col = 5;
     else if((int)Sliced[i][1] == 0 && (int)Sliced[i][2] == 1 && (int)Sliced[i][3] == 0 && (int)Sliced[i][4] == 1 ) col = 6;
     else if((int)Sliced[i][1] == 0 && (int)Sliced[i][2] == 1 && (int)Sliced[i][3] == 1 && (int)Sliced[i][4] == 0 ) col = 7;
     else if((int)Sliced[i][1] == 0 && (int)Sliced[i][2] == 1 && (int)Sliced[i][3] == 1 && (int)Sliced[i][4] == 1 ) col = 8;
     else if((int)Sliced[i][1] == 1 && (int)Sliced[i][2] == 0 && (int)Sliced[i][3] == 0 && (int)Sliced[i][4] == 0 ) col = 9;
     else if((int)Sliced[i][1] == 1 && (int)Sliced[i][2] == 0 && (int)Sliced[i][3] == 0 && (int)Sliced[i][4] == 1 ) col = 10;
     else if((int)Sliced[i][1] == 1 && (int)Sliced[i][2] == 0 && (int)Sliced[i][3] == 1 && (int)Sliced[i][4] == 0 ) col = 11;
     else if((int)Sliced[i][1] == 1 && (int)Sliced[i][2] == 0 && (int)Sliced[i][3] == 1 && (int)Sliced[i][4] == 1 ) col = 12;
     else if((int)Sliced[i][1] == 1 && (int)Sliced[i][2] == 1 && (int)Sliced[i][3] == 0 && (int)Sliced[i][4] == 0 ) col = 13;
     else if((int)Sliced[i][1] == 1 && (int)Sliced[i][2] == 1 && (int)Sliced[i][3] == 0 && (int)Sliced[i][4] == 1 ) col = 14;
     else if((int)Sliced[i][1] == 1 && (int)Sliced[i][2] == 1 && (int)Sliced[i][3] == 1 && (int)Sliced[i][4] == 0 ) col = 15;
     else col = 16;



     OutputBlock1 = s_boxes[i][((row-1)*16+ col-1)];
     SBoxDumpFile<<"Row = "<<row<<" and col = "<<col<<" "<<endl;
     SBoxDumpFile<<"Block Output "<<i<<" = "<<(int)OutputBlock1<<endl;
     SBoxDumpFile<<"Converting to bit block : ";
     SBoxDumpFile.close();
     OutputBlock2[i] = generateBitBlockFromInt(OutputBlock1);
     displayToSBox(OutputBlock2[i],4);
     SBoxDumpFile.open ("SboxDump.txt", std::ios::app);




        }
        for(int i= 0; i < 8; i++){
                for(int j= 0; j < 4; j++){
        result[i*4+j]=OutputBlock2[i][j];
                }
        }
        SBoxDumpFile<<"Sbox Final Output = ";
        SBoxDumpFile.close();
        displayToSBox(result,32);
        SBoxDumpFile.open ("SboxDump.txt", std::ios::app);
//    for(int i= 0; i < 8; ++i
//    ){
//       generateBitBlockFromInt(generateBitBlockFromInt(Sliced, 6));
//    }
 SBoxDumpFile.close();
 return result;
}


char *generateBitBlockFromInt(int outputvalue)
{
    char *result = new char[4];

    for (int i=0;i<4;i++)
    {
        result[i]=(outputvalue/8)%2;
        outputvalue *=2;
    }

    return result;
}

int generateIntFromBitBlock(char *block, long blocksize)
{
    int result=0;

    for(int i=0;i<blocksize;i++)
    {
        result = (2*result+block[i]);
    }

    return result;
}
