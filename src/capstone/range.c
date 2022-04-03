#include "range.h"
#include <stdlib.h>

static int qsort_callback (const void * a, const void * b)
{
    return *(unsigned int*)a - *(unsigned int*)b;
}

void sort_numbers(range_unsigned_int * target)
{
    qsort(target->begin, range_count(*target), sizeof(*target->begin), qsort_callback);
}
