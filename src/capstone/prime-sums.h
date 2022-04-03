#ifndef FLAT_INCLUDES
#include "../table/pointer.h"
#include "../window/def.h"
#include "range.h"
#include <stdint.h>
#include <stdlib.h>
#include "../keyargs/keyargs.h"
#include "../range/alloc.h"
#include "../window/alloc.h"
#endif

map_pointer_type_declare(prime_sum);
map_pointer_type_define(prime_sum, uintptr_t, window_range_unsigned_int);
static void prime_sum_value_clear (prime_sum_value * target)
{
    range_unsigned_int * i;

    for_range (i, target->region)
    {
	range_clear (*i);
    }

    window_clear(*target);
}
map_pointer_function_define(prime_sum);

keyargs_declare(void, list_prime_sums, prime_sum_table * output; unsigned int prime_count; unsigned int tuple_size;);
#define list_prime_sums(...) keyargs_call(list_prime_sums, __VA_ARGS__)

typedef struct {
    unsigned int sum;
    range_const_unsigned_int contents;
}
    prime_sum_tuple;

range_typedef(prime_sum_tuple, prime_sum_tuple);
window_typedef(prime_sum_tuple, prime_sum_tuple);

void order_prime_sum_tuples (window_prime_sum_tuple * output, prime_sum_table * src);

void select_sums (range_const_prime_sum_tuple * result, unsigned int select, range_prime_sum_tuple * src);
