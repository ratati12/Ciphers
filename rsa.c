#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct key
{
    int n;
    int e;
    int d;
};


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
    key->e = 3;
    key->d = inverse(key->e,phi);;
    return 0;
}

unsigned long long encrypt(int m, struct key* key)
{
    unsigned long long c = (unsigned long long)(pow((double)m,(double)key->e))%key->n;
    return (unsigned long long)c;
}

int main(int argc, char *argv[])
{
    struct key key;
    int p = 3557;
    int q = 2579;
    unsigned long long m = 123; // Open text;
    unsigned long long c;
    printf("Open message: %llu\n",m);
    keygen(p, q, &key);
    printf("Open key: {e,n} = {%d,%d}\nSecret key: {d,n}={%d,%d}\n",key.e,key.n,key.d,key.n);
    c = encrypt(m, &key); 
    printf("Encrypted message: %llu\n", c);
    return 0;    
}
