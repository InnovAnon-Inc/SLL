#ifndef _SLL_NODE3_H_
#define _SLL_NODE3_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <sys/types.h>

#include <dsint.h>
#include <glitter.h>

typedef struct sll_node3 {
	struct sll_node3 *restrict next;
	void *restrict data;
	size_t esz;
} sll_node3_t;

size_t sll_node3sz (void)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

size_t sll_node4sz (size_t esz)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

void init_sll_node3 (sll_node3_t *restrict sll,
	sll_node3_t *restrict next, size_t esz)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

sll_node3_t *alloc_sll_node3 (sll_node3_t *restrict next,
	size_t esz)
__attribute__ ((nothrow, warn_unused_result)) ;

sll_node3_t *alloc_sll_node4 (sll_node3_t *restrict next,
	size_t esz)
__attribute__ ((nothrow, warn_unused_result)) ;

void setNext_sll_node3 (sll_node3_t *restrict sll,
	sll_node3_t *restrict next)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

sll_node3_t *getNext_sll_node3 (sll_node3_t const *restrict sll)
__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result)) ;

bool hasNext_sll_node3 (sll_node3_t const *restrict sll)
__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result)) ;

void setData_sll_node3 (sll_node3_t *restrict sll,
	void *restrict data, size_t esz)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void setData_sll_node4 (sll_node3_t *restrict sll,
	void const *restrict data)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void *getData_sll_node3 (sll_node3_t const *restrict sll)
__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result)) ;

void getData_sll_node4 (sll_node3_t const *restrict sll,
	void *restrict data)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void free_sll_node3 (sll_node3_t *restrict sll, free_t f)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void free_sll_node4 (sll_node_t *restrict sll)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _SLL_NODE3_H_ */