#include <stdio.h>
#include <stdlib.h>

#include "correlation/autocorr.h"

int main()
{
    autocorr_input_t in[] = {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
    autocorr_output_t out[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    index_t size = 16;

    autocorr_naive(in,out,size);
    for(index_t i = 0; i < size; i++) {
        printf("%u ",out[i]);
    }
    printf("\n");

    return 0;
}
