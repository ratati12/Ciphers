#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned __int128 uint128_t;

typedef struct key
{
    int n;
    int e;
    int d;
}key;


int inverse(int n, int modulus) 
{
	int a = n, b = modulus;
	int x = 0, y = 1, x0 = 1, y0 = 0, q, temp;
	while(b != 0) {
		q = a / b;
		temp = a % b;
		a = b;
		b = temp;
		temp = x; x = x0 - q * x; x0 = temp;
		temp = y; y = y0 - q * y; y0 = temp;
	}
if(x0 < 0) x0 += modulus;
	return x0;
}

int keygen(int p, int q, struct key* key)
{
    int phi = (p-1)*(q-1);
    key->n = p*q;
    key->d = inverse(key->e,phi);;
    return 0;
}

uint128_t encrypt(int m, struct key* key)
{
    uint128_t c = (uint128_t)(powl((double)m,(double)key->e))%key->n;
    return (uint128_t)c;
}

int main(int argc, char *argv[])
{
    key key;
    int p;
    int q;

    printf("Enter p:");
    scanf ("%d", &p);
    printf("Enter q:");
    scanf ("%d", &q);
    printf("Enter e:");
    scanf ("%d", &key.e);

    uint128_t m = 111111; // Open text;
    uint128_t c;
    printf("Open message: %llu %llu\n",(u_int64_t)(m>>64),(u_int64_t)(m));
    keygen(p, q, &key);
    printf("Open key: {e,n} = {%d,%d}\nSecret key: {d,n}={%d,%d}\n",key.e,key.n,key.d,key.n);
    if (key.d == 1) 
    {
        fprintf(stderr,"Bad input!\n");
        return -1;
    }
    c = encrypt(m, &key); 
    printf("Encrypted message: %llu %llu\n", (u_int64_t)(c>>64), (u_int64_t)(c));
    return 0;    
}
