#include "list-primes.h"
#include "is-prime.h"

void list_primes(range_unsigned_int * primes)
{
    unsigned int * i;

    int check = 1;

    for_range (i, *primes)
    {
	while (!is_prime (++check))
	{}

	*i = check;
    }
}
