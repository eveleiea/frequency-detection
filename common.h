#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

/* Standard integer definitions */
#include <stdint.h>

/* fake boolean values */
#define TRUE 1
#define FALSE 0

/* single-width sample datatype */
#define SINGLE_NUM_BITS 8
#define SINGLE_NUM_BYTES 1
#define SINGLE_TYPE uint8_t
#define SINGLE_SIGNED FALSE

typedef SINGLE_TYPE single_t;
#define SINGLE_MIN ((single_t)0)
#define SINGLE_MAX ((single_t)((2<<SINGLE_NUM_BITS)-1))

/* double-width sample datatype */
#define DOUBLE_NUM_BITS (2*SINGLE_NUM_BITS)
#define DOUBLE_NUM_BYTES (2*SINGLE_NUM_BYTES)
#define DOUBLE_TYPE uint16_t
#define DOUBLE_SIGNED SINGLE_SIGNED
#define DOUBLE_MIN ((double_t)0)
#define DOUBLE_MAX ((double_t)((2<<SINGLE_NUM_BITS)-1))

typedef DOUBLE_TYPE double_t;

/* index datatype (strictly unsigned) */
#define INDEX_NUM_BITS 8
#define INDEX_NUM_BYTES 1
#define INDEX_TYPE uint8_t

typedef INDEX_TYPE index_t;

#define INDEX_MIN ((index_t)0)
#define INDEX_MAX ((index_t)((2<<INDEX_NUM_BITS)-1))


#endif // COMMON_H_INCLUDED
