#include "is-prime.h"
#include <math.h>

bool is_prime(unsigned int n)
{
    unsigned int test_max = sqrt(n);
    if (n == 1)
    {
	return false;
    }
    else if (n & 1) // odd
    {
	for (unsigned int test = 3; test <= test_max; test += 2)
	{
	    if (n % test == 0)
	    {
		return false;
	    }
	}

	return true;
    }
    else
    {
	return n == 2;
    }
}
