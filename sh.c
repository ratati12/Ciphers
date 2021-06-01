#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
FILE * fp[3];

int main()
{
setlocale(LC_ALL, "Rus");
fp[0] = fopen("open.txt", "r");
fp[1] = fopen("key.txt", "r");
fp[2] = fopen("close.txt", "w");
unsigned int key[26];
unsigned int c;
for (int i = 0; i < 26; i++) 
{
    key[i] = fgetc(fp[1]);
}
while (!feof(fp[0]))
{
    c = fgetc(fp[0]);
    if (c <= 90 && c >= 65)
    {
        c -= 65;
        fputc(key[c], fp[2]);
    } else if (c <= 122 && c >= 97)
    {
        c -= 97;
        fputc(key[c], fp[2]);
    }
    else fputc(c,fp[2]);
}
return 0;
}
