// RC5XOR-32/12/16
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int WORD;       // Should be 32-bit = 4 bytes

#define w        32             // word size in bits                 
#define r        12             // number of rounds                  
#define b        16             // number of bytes in key            
#define c         4             // number  words in key = ceil(8*b/w)
#define t        26             // size of table S = 2*(r+1) words   
WORD S[t];                      // expanded key table                
WORD P = 0xb7e15163, Q = 0x9e3779b9;               
// Rotation operators. x must be unsigned, to get logical right shift
#define ROTL(x,y) ((x)<<(y))

void RC5_encrypt(WORD *open, WORD *close) // 2 WORD input open/output close    
{ 
    WORD i, A = open[0]+S[0], B = open[1]+S[1];
    for (i=1; i<=r; i++)
    { 
        A = ROTL(A^B,B)^S[2*i];
        B = ROTL(B^A,A)^S[2*i+1];
    }
    close[0] = A; 
    close[1] = B;
}

void RC5_setup(unsigned char *K)
{  
    WORD i, j, k, u=w/8, A, B, L[c];
    for (i = b-1, L[c-1] = 0; i != -1; i--) // split the key of a word 
    {
        L[i/u] = (L[i/u] << 8)+K[i];
    }
    for (S[0] = P,i = 1; i < t; i++) // creating the table of expanded key
    {
        S[i] = S[i-1]+Q;
    }
    for (A = B = i = j = k = 0; k < 3*t; k++, i = (i+1)%t, j = (j+1)%c)   
    { 
        A = S[i] = ROTL(S[i]+(A+B),3);
        B = L[j] = ROTL(L[j]+(A+B),(A+B)); 
    }
}

int main()
{
    WORD i, j, open[2] = {1, 1}, close[2] = {0, 0};
    unsigned char key[b];
    if (sizeof(WORD) != 4) printf ("Error: WORD has %ld bytes. \n", sizeof(WORD));
        for (j = 0; j < b; j++)
        {
            RC5_setup(key);
            RC5_encrypt(open,close);
            printf("key = ");
            for (j = 0; j < b; j++) printf("%X", key[j]);
            printf ("\nopentext:\t");
            printf("%u",open[0]);
            printf("%u\n",open[1]);
            printf("ciphertext:\t ");
            printf("%u",close[0]);
            printf("%u",close[1]);
            printf("\n");
        }
    
    return 0;
}
