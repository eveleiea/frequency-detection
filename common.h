#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

/* Standard integer definitions */
#include <stdint.h>

/* fake boolean values */
#define TRUE 1
#define FALSE 0

/* integer datatype macros */
/* unsigned integer minimum and maximum values*/
#define UINT_MIN(bits) 0
#define UINT_MAX(bits) ((2<<(bits-1))-1)
/* signed integer minimum and maximum values */
#define INT_MIN(bits) (-(2<<(bits-2)))
#define INT_MAX(bits) ((2<<(bits-2))-1)

/* single-width sample datatype */
#define SINGLE_NUM_BITS 8
#define SINGLE_NUM_BYTES 1
#define SINGLE_SIGNED FALSE
#define SINGLE_TYPE uint8_t
typedef SINGLE_TYPE single_t;
#define SINGLE_MIN UINT_MIN(SINGLE_NUM_BITS)
#define SINGLE_MAX UINT_MAX(SINGLE_NUM_BITS)

/* double-width sample datatype */
#define DOUBLE_NUM_BITS (2*SINGLE_NUM_BITS)
#define DOUBLE_NUM_BYTES (2*SINGLE_NUM_BYTES)
#define DOUBLE_TYPE uint16_t
#define DOUBLE_SIGNED SINGLE_SIGNED
typedef DOUBLE_TYPE double_t;
#define DOUBLE_MIN UINT_MIN(DOUBLE_NUM_BITS)
#define DOUBLE_MAX UINT_MIN(DOUBLE_NUM_BITS)


/* index datatype (strictly unsigned) */
#define INDEX_NUM_BITS 8
#define INDEX_NUM_BYTES 1
#define INDEX_TYPE uint8_t
typedef INDEX_TYPE index_t;
#define INDEX_MIN UINT_MIN(INDEX_NUM_BITS)
#define INDEX_MAX UINT_MIN(INDEX_NUM_BITS)


#endif // COMMON_H_INCLUDED
