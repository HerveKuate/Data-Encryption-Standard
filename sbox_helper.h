#ifndef SBOX_HELPER_H_INCLUDED
#define SBOX_HELPER_H_INCLUDED

char *sbox(char*, char [8][64]);
char *generateBitBlockFromInt(int);
int generateIntFromBitBlock(char*, long);

#endif // SBOX_HELPER_H_INCLUDED
