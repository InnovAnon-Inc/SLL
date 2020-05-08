#ifndef _SLL_NODE_H_
#define _SLL_NODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <sys/types.h>

#include <dsint.h>
#include <glitter.h>

typedef struct sll_node {
	struct sll_node *restrict next;
	void *restrict data;
} sll_node_t;

size_t sll_nodesz (void)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

size_t sll_nodesz2 (size_t esz)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;
/*
void init_sll_node (sll_node_t *restrict sll,
	sll_node_t /*const* / *restrict next, void *restrict data)
__attribute__ ((leaf, nonnull (1, 3), nothrow)) ;
*/
void init_sll_node (sll_node_t *restrict sll,
	sll_node_t /*const*/ *restrict next)
__attribute__ ((leaf, nonnull (1), nothrow)) ;
void init_sll_node2 (sll_node_t *restrict sll,
	sll_node_t /*const*/ *restrict next,
	void *restrict data, size_t esz)
__attribute__ ((nonnull (1, 3), nothrow)) ;
/*
sll_node_t *alloc_sll_node (sll_node_t /*const* / *restrict next,
	size_t esz)
__attribute__ ((nothrow, warn_unused_result)) ;
*/
sll_node_t *alloc_sll_node (sll_node_t /*const*/ *restrict next)
__attribute__ ((nothrow, warn_unused_result)) ;
sll_node_t *alloc_sll_node2 (sll_node_t /*const*/ *restrict next,
	size_t esz)
__attribute__ ((nothrow, warn_unused_result)) ;

sll_node_t *alloc_sll_node3 (sll_node_t /*const*/ *restrict next,
	void *restrict data, size_t esz)
__attribute__ ((nonnull (2), nothrow, warn_unused_result)) ;

void setNext_sll_node (sll_node_t *restrict sll,
	sll_node_t /*const*/ *restrict next)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

sll_node_t *getNext_sll_node (sll_node_t *restrict sll)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

bool hasNext_sll_node (sll_node_t *restrict sll)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

void setData_sll_node (sll_node_t *restrict sll,
	void *restrict data)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void setData_sll_node2 (sll_node_t *restrict sll,
	void *restrict data, size_t esz)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void *getData_sll_node (sll_node_t *restrict sll)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;
/*
void setData_sll_node2 (sll_node_t *restrict sll,
	void *restrict data, size_t esz)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;
*/
__attribute__ ((leaf, nonnull (1), nothrow))
void free_sll_node (sll_node_t *restrict sll, free_t f)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void free_sll_node2 (sll_node_t *restrict sll)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _SLL_NODE_H_ */
