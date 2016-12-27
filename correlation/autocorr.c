#include "autocorr.h"


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
