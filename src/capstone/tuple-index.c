#include "tuple-index.h"
#include <stdio.h>

static bool iterate_sub (unsigned int * i, unsigned int * end, unsigned int max)
{
    if (i == end)
    {
	return false;
    }

    (*i)++;

    if (*i == max)
    {
	if (!iterate_sub (i + 1, end, max))
	{
	    return false;
	}

	*i = *(i + 1);
    }

    return true;
}

bool tuple_index_iterate (range_unsigned_int * index, unsigned int max)
{
    return iterate_sub (index->begin, index->end, max);
}

void print_index (range_const_unsigned_int * index)
{
    const unsigned int * i;

    printf("{ ");
    for_range (i, *index)
    {
	printf("%u, ", *i);
    }

    printf("}\n");
}
