#include "../../tuple-index.h"
#include "../../../range/alloc.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main()
{
    range_unsigned_int index;

    range_calloc(index, 3);

    do
    {
	print_index(&index);
    }
    while (tuple_index_iterate(&index, range_count(index)));

    return 0;
}
