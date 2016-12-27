#ifndef AUTOCORR_H_INCLUDED
#define AUTOCORR_H_INCLUDED

#include "../common.h"

typedef single_t autocorr_input_t;
typedef double_t autocorr_output_t;

void autocorr_naive(autocorr_input_t* in, autocorr_output_t* out, index_t size);

#endif // AUTOCORR_H_INCLUDED
