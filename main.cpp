#include <iostream>
#include "permutations.h"
#include "include/expansion.h"
#include "bit_tables.h"
#include "data_tables.h"
#include "include/pc2.h"
#include "include/LKeyFunction.h"
#include "include/RKeyFunction.h"
#include "include/ShiftKey.h"
#include "data_messages_examples.h"
#include "include/XORFUNCTION.h"
#include "sbox_helper.h"
 #include <fstream>

using namespace std;

int main()
{
    char *firstperm;

    int i;
    cout << "Message : "<<endl;
    displayBitTable(message_03,64); cout << " / "; //message_3
    displayAsHex(message_03,64);
    cout << endl<<endl;

    firstperm=permute(message_03,init_perm,64);

    cout << "Permutted Key\n";
    displayBitTable(firstperm,64); cout << " / ";
    displayAsHex(firstperm,64); cout << endl<<endl;
    //displayBitTable(firstperm,64);
    //displayAsHex(firstperm,64);

    /************Get R & L************/
    char **L = new char*[17];
    char **R = new char*[17];
    for(i = 0; i < 17; ++i){
        L[i] = new char[32];
        R[i] = new char[32];
    }

    int L_Ingrement = 0;
    int R_Ingrement = 0;
    for(int i=0; i<64; i++)
	{
        if(i < 64/2)
            L[0][L_Ingrement++]= firstperm[i];
        else
            R[0][R_Ingrement++]= firstperm[i];
	}
	cout << "Splitted block L0 R0 \n";
	 cout << "L0 : ";
       displayBitTable(L[0],28); cout << " / ";
       displayAsHex(L[0],28); cout << endl;
       cout << "R0 : ";
       displayBitTable(R[0],28);cout << " / ";
       displayAsHex(R[0],28);cout << endl<<endl;

    /**********Step 2***********************/
    char *Lkey = new char[28];
    char *Rkey = new char[28];
    char **Subkey = new char*[17];
    char *LkeyShifted = new char[28];
    char *RkeyShifted = new char[28];

	Lkey = LKeyFunction(GLOBAL_KEY, pc_1_left,28);
	Rkey = RKeyFunction(GLOBAL_KEY, pc_1_right,28);
    cout << "LKey : ";
       displayBitTable(Lkey,28); cout << " / ";
       displayAsHex(Lkey,28); cout << endl;
       cout << "RKey : ";
       displayBitTable(Rkey,28);cout << " / ";
       displayAsHex(Rkey,28);cout << endl<<endl;

    cout<<"***********Subkey Generator***********"<<endl;
	 for(int round=0; round< 16; round++){ //each round

       LkeyShifted = ShiftKey(Lkey, (int)keyshift[round]);
       RkeyShifted = ShiftKey(Rkey, (int)keyshift[round]);

       cout << "ROUND " << round+1 << "\n";
       cout << "L : ";
       displayBitTable(Lkey,28); cout << " / ";
       displayAsHex(Lkey,28); cout << endl;
       cout << "R : ";
       displayBitTable(Rkey,28);cout << " / ";
       displayAsHex(Rkey,28);cout << endl<<endl;

       cout << "leftshifting L and R by "<< (int)keyshift[round] << " bits" <<endl;
       cout << "shifted L : ";
       displayBitTable(LkeyShifted,28); cout << " / ";
       displayAsHex(LkeyShifted,28); cout << endl;
       cout << "shifted R : ";
       displayBitTable(RkeyShifted,28);cout << " / ";
       displayAsHex(RkeyShifted,28);cout << endl<<endl;

        //Append 48 block
        char *AppendKey = new char[56];
        L_Ingrement=0;
        R_Ingrement=0;
        for(int i=0; i<56; i++){
            if(i<28)
                AppendKey[i] = LkeyShifted[L_Ingrement++];
            else
                AppendKey[i] = RkeyShifted[R_Ingrement++];
        }
        cout<<"reunited : ";
        displayBitTable(AppendKey,56);cout << " / ";
        displayAsHex(AppendKey,56);cout << endl;


        Subkey[round] = pc2(AppendKey, pc_2, 48);
        cout<<"after pc_2 permutation : 48 BITS KEY VALUE : "<<endl;
        displayBitTable(Subkey[round],48);cout << " / ";
        displayAsHex(Subkey[round],48);cout << endl<<endl;
	 }
	 cout<<"SUBKEY"<<endl;
	 for(int round=0; round< 16; round++){
        displayBitTable(Subkey[round],48);cout << " / ";
        displayAsHex(Subkey[round],48);cout << endl;
	 }


    char **RExpan = new char*[17];
    char **RXOR = new char*[17];
    char **RSbox = new char*[17];
    char **secondperm = new char*[32];
    char **RXOR2 = new char*[17];


    cout<<endl<<"           *********Main Process*********"<<endl;
    ofstream DESDumpFile;
    DESDumpFile.open ("DES - dump.txt");
    for(int round=0; round< 16; round++){
    DESDumpFile<<"Round "<<round+1<<":"<<endl;
    DESDumpFile<<"L"<<round<<" : ";
    DESDumpFile.close();
    displayToDES(L[round],32);
    DESDumpFile.open ("DES - dump.txt", std::ios::app);

    DESDumpFile<<"R"<<round<<" : ";
    DESDumpFile.close();
    displayToDES(R[round],32);
    DESDumpFile.open ("DES - dump.txt", std::ios::app);

    RExpan[round] = expans(R[round], expansion_table, 48);
    DESDumpFile<<"Expansion"<<" : ";
    DESDumpFile.close();
    displayToDES(RExpan[round],48);
    DESDumpFile.open ("DES - dump.txt", std::ios::app);

    DESDumpFile<<"Used Subkey : ";
    DESDumpFile.close();
    displayToDES(Subkey[round],48);
    DESDumpFile.open ("DES - dump.txt", std::ios::app);

    RXOR[round] = XOR(RExpan[round],Subkey[round],48);
    DESDumpFile<<"Xor output   : ";
    DESDumpFile.close();
    displayToDES(RXOR[round],48);
    DESDumpFile.open ("DES - dump.txt", std::ios::app);

    RSbox[round] = sbox(RXOR[round],s_boxes);
    DESDumpFile<<"SBox output   : ";
    DESDumpFile.close();
    displayToDES(RSbox[round],32);
    DESDumpFile.open ("DES - dump.txt", std::ios::app);


    secondperm[round] = permute(RSbox[round],permut_32,32);
    DESDumpFile<<"after perm32 : ";
     DESDumpFile.close();
    displayToDES(secondperm[round],32);
    DESDumpFile.open ("DES - dump.txt", std::ios::app);

    RXOR2[round] = XOR(secondperm[round],L[round],32);
    DESDumpFile<<"Xor output   : ";
     DESDumpFile.close();
    displayToDES(RXOR2[round],32);
    DESDumpFile.open ("DES - dump.txt", std::ios::app);
    DESDumpFile<<endl;


    R[round+1]=RXOR2[round];
    L[round+1]=R[round];

    }

    char *Joining = new char[64];
    int counter1 = 0;
    int counter2 = 0;
    for(int i=0; i<64;i++){
        if(i<32)Joining[i]=R[16][counter1++];
        else Joining[i]=L[16][counter2++];
    }
    DESDumpFile<<"Joining R16+L16 : ";
     DESDumpFile.close();
    displayToDES(Joining,64);
    DESDumpFile.open ("DES - dump.txt", std::ios::app);
    DESDumpFile<<endl;

    char *encryptedMessage;
    encryptedMessage = permute(Joining,reverse_perm,64);
    DESDumpFile<<"Encrypted message :";
    DESDumpFile.close();
    displayToDES(encryptedMessage,64);
    DESDumpFile.open ("DES - dump.txt", std::ios::app);
    DESDumpFile<<endl;

cout<<"Look to file DES - dump.txt generated at the relative directory";
DESDumpFile.close();

    /**********************************************/



}
