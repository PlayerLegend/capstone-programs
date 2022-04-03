#include <assert.h>
#include "prime-sums.h"
#include "../range/alloc.h"
#include "list-primes.h"
#include <stdbool.h>
#include "tuple-index.h"
#include <stdio.h>

unsigned int calculate_sum (range_unsigned_int * tuple, range_unsigned_int * primes)
{
    unsigned int sum = 0;

    unsigned int * i;

    for_range (i, *tuple)
    {
	assert (*i < range_count(*primes));
	sum += primes->begin[*i];
    }

    return sum;
}

void set_tuple (range_unsigned_int * dst, range_unsigned_int * src, range_unsigned_int * primes)
{
    unsigned int size = range_count(*src);

    range_calloc(*dst, size);

    for (unsigned int i = 0; i < size; i++)
    {
	assert (src->begin[i] < range_count(*primes));

	dst->begin[i] = primes->begin[src->begin[i]];
    }
}

static bool index_repeats(range_unsigned_int * target)
{
    size_t max = range_count(*target);
    for (size_t i = 0; i < max; i++)
    {
	for (size_t j = i + 1; j < max; j++)
	{
	    if (target->begin[i] == target->begin[j])
	    {
		return true;
	    }
	}
    }

    return false;
}

keyargs_define(list_prime_sums)
{
    range_unsigned_int primes;
    range_calloc (primes, args.prime_count);
    list_primes(&primes);

    range_unsigned_int index;
    range_calloc (index, args.tuple_size);

    window_range_unsigned_int * push_target;
    
    do {
	if (!index_repeats (&index))
	{
	    push_target = &prime_sum_include(args.output, calculate_sum(&index, &primes))->value;
	    
	    set_tuple(window_push(*push_target), &index, &primes);
	}
    }
    while (tuple_index_iterate(&index, args.prime_count));
}

int qsort_callback(const void * a, const void * b)
{
    const prime_sum_tuple * a_tuple = a;
    const prime_sum_tuple * b_tuple = b;

    if (a_tuple->sum != b_tuple->sum)
    {
	return a_tuple->sum - b_tuple->sum;
    }

    size_t size = range_count(a_tuple->contents);

    for (size_t i = 0; i < size; i++)
    {
	if (a_tuple->contents.begin[i] != b_tuple->contents.begin[i])
	{
	    return a_tuple->contents.begin[i] - b_tuple->contents.begin[i];
	}
    }

    return 0;
}

void order_prime_sum_tuples (window_prime_sum_tuple * output, prime_sum_table * src)
{
    prime_sum_link ** bucket;
    prime_sum_link * item;

    const range_unsigned_int * tuple;

    for_range (bucket, *src)
    {
	item = *bucket;

	while (item)
	{
	    for_range (tuple, item->child.value.region)
	    {
		*window_push(*output) = (prime_sum_tuple) { .sum = item->child.ref, .contents = tuple->const_cast };
	    }
		
	    item = item->peer;
	}
    }
    
    qsort (output->region.begin, range_count(output->region), sizeof(*output->region.begin), qsort_callback);
}

void select_sums (range_const_prime_sum_tuple * result, unsigned int select, range_prime_sum_tuple * src)
{
    result->begin = src->begin;

    while (result->begin < src->end && result->begin->sum < select)
    {
	result->begin++;
    }
    
    result->end = result->begin;

    while (result->end < src->end && result->end->sum == select)
    {
	result->end++;
    }
}
