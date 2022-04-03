#include <assert.h>
#include "../../prime-sums.h"
#include <stdio.h>
#include <stdbool.h>
#include "../../tuple-index.h"

range_typedef(prime_sum_tuple*, prime_sum_tuple_p);
window_typedef(prime_sum_tuple*, prime_sum_tuple_p);



int main()
{
    prime_sum_table table = {0};

    list_prime_sums (&table, .prime_count = 100, .tuple_size = 3);

    window_prime_sum_tuple ordered = {0};
    
    order_prime_sum_tuples(&ordered, &table);

    window_prime_sum_tuple selected;

    select_sums(&selected.region.const_cast, 77, &ordered.region);
    
    prime_sum_tuple * i;

    for_range (i, selected.region)
    {
	printf ("%d = ", i->sum);
	print_index(&i->contents);
    }

    return 0;
}
