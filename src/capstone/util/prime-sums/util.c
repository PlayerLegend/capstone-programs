#include <assert.h>
#include "../../prime-sums.h"
#include <stdio.h>
#include <stdbool.h>
#include "../../tuple-index.h"

int main()
{
    prime_sum_table table = {0};

    list_prime_sums (&table, .prime_count = 100, .tuple_size = 3);

    window_prime_sum_tuple ordered = {0};
    
    order_prime_sum_tuples(&ordered, &table);

    prime_sum_tuple * i;

    for_range (i, ordered.region)
    {
	printf ("%d = ", i->sum);
	print_index(&i->contents);
    }

    return 0;
}
