#include "prime.h"
#include <math.h>

/**
 * Returns
 * -1 : undefined
 * 0 : not prime 
 * 1 : is prime
 */
int is_prime(int num)
{
    if (num < 2) return -1;
    /* 2,3 is prime*/
    if (num < 4) return 1;
    if (num % 2 == 0) return 0;
    int i = 3;
    for (; i < floor(sqrt((double)num)) ; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int next_prime(int num)
{
    while (is_prime(num) != 1)
        ++num;

    return num;
}