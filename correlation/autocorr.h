#ifndef AUTOCORR_H_INCLUDED
#define AUTOCORR_H_INCLUDED

#include "../common.h"

#define AUTOCORR_TEST

typedef SINGLE autocorr_input_t;
typedef DOUBLE autocorr_output_t;

void autocorr_naive(autocorr_input_t* in, autocorr_output_t* out, index_t size);
void autocorr_lessnaive(autocorr_input_t* in, autocorr_output_t* out, index_t size);
void autocorr_binary(autocorr_input_t* in, autocorr_output_t* out, index_t size);

#ifdef AUTOCORR_TEST
void autocorr_testall(void);
#endif

#endif // AUTOCORR_H_INCLUDED
