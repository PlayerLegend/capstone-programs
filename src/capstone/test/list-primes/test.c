#include "../../list-primes.h"
#include "../../../range/alloc.h"
#include "../../is-prime.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main()
{
    range_unsigned_int primes;

    range_calloc (primes, 1000);

    list_primes(&primes);

    unsigned int * i;

    for_range(i, primes)
    {
	assert (is_prime(*i));
	printf("%u\n", *i);
    }

    return 0;
}
