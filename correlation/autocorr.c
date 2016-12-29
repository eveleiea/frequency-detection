#include "autocorr.h"

/* naive autocorrelation using the DSP definition and no optimization */
void autocorr_naive(autocorr_input_t* in, autocorr_output_t* out, index_t size) {
    index_t lag = 0;
    index_t i = 0;
    autocorr_output_t sum;

    for(lag = 0; lag < size; lag++) {
        sum = 0;
        for(i = 0; i < size; i++) {
            if(i+lag < size) {
                sum += in[i]*in[i+lag];
            }
            else {
                sum += in[i]*0;
            }
        }
        out[lag] = sum;
    }
}

/* less naive autocorrelation using the DSP definition and optimizing inner loop */
void autocorr_lessnaive(autocorr_input_t* in, autocorr_output_t* out, index_t size) {
    index_t lag = 0;
    index_t i = 0;
    autocorr_output_t sum;

    for(lag = 0; lag < size; lag++) {
        sum = 0;
        for(i = 0; i < (size-lag); i++) {
            sum += in[i]*in[i+lag];
        }
        out[lag] = sum;
    }
}

/* less naive autocorrelation considering only the lsb of the input samples */
void autocorr_binary(autocorr_input_t* in, autocorr_output_t* out, index_t size) {
    index_t lag = 0;
    index_t i = 0;
    autocorr_output_t sum;

    for(lag = 0; lag < size; lag++) {
        sum = 0;
        for(i = 0; i < (size-lag); i++) {
            /* binary multiplication reduces to logical and */
            sum += (in[i]&in[i+lag])&1;
        }
        out[lag] = sum;
    }
}


/* test section for the above functions */
#ifdef AUTOCORR_TEST
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define SEQUENCE_LENGTH 16
autocorr_input_t sequence[SEQUENCE_LENGTH];
#define MAX_INPUT 1//sqrt(DOUBLE_MAX/SEQUENCE_LENGTH)
#define NUM_TESTS 10

autocorr_output_t out_naive[SEQUENCE_LENGTH];
autocorr_output_t out_lessnaive[SEQUENCE_LENGTH];
autocorr_output_t out_binary[SEQUENCE_LENGTH];

void autocorr_testall(void) {
    const int max_input = MAX_INPUT;
    int pass;

    printf("Testing %u sequences of length %u with a maximum value of %u.\n", NUM_TESTS, SEQUENCE_LENGTH, max_input);
    srand(time(NULL));
    for(int n = 0; n < NUM_TESTS; n++) {
        printf("Test #%i:\n", n+1);

        printf("Input: [");
        for(int i = 0; i < SEQUENCE_LENGTH; i++) {
            sequence[i] = (autocorr_input_t)(rand()>>8)%(max_input+1);
            printf("%i ",sequence[i]);
        }
        printf("]\n");

        autocorr_naive(sequence,out_naive,SEQUENCE_LENGTH);
        autocorr_lessnaive(sequence,out_lessnaive,SEQUENCE_LENGTH);
        autocorr_binary(sequence,out_binary,SEQUENCE_LENGTH);

        pass = TRUE;
        printf("Integer Output: [");
        for(int i = 0; i < SEQUENCE_LENGTH; i++) {
            if(out_naive[i] != out_lessnaive[i]) {
                pass = FALSE;
            }
            printf("%i ",out_lessnaive[i]);
        }
        printf("]\n");

        if(pass == TRUE) {
            printf("Integer PASS\n");

        }
        else {
            printf("Integer FAIL\n");
        }

        /* binary test only passes if MAX_INPUT is 1 */
        pass = TRUE;
        printf("Binary Output: [");
        for(int i = 0; i < SEQUENCE_LENGTH; i++) {
            if(out_naive[i] != out_binary[i]) {
                pass = FALSE;
            }
            printf("%i ",out_lessnaive[i]);
        }
        printf("]\n");

        if(pass == TRUE) {
            printf("Binary PASS\n");
        }
        else {
            printf("Binary FAIL\n");
        }


        printf("\n");
    }
}
#endif
