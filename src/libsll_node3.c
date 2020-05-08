#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <mmalloc.h>
#include <swap.h>

#include <sll_node3.h>

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t sll_node3sz (void) {
	return sizeof (sll_node3_t);
}

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t sll_node4sz (size_t esz) {
	return sizeof (sll_node3_t) + esz;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void init_sll_node3 (sll_node3_t *restrict sll,
	sll_node3_t *restrict next, size_t esz) {
	sll->esz  = esz;
	sll->next = next;
}

__attribute__ ((nothrow, warn_unused_result))
sll_node3_t *alloc_sll_node3 (sll_node3_t *restrict next,
	size_t esz) {
	/*sll_node3_t *restrict ret = alloc (sizeof (sll_node3_t));*/
	sll_node3_t *restrict ret = malloc (sizeof (sll_node3_t));
	error_check (ret == NULL) return NULL;
	init_sll_node3 (next, NULL, esz);
	return ret;
}

__attribute__ ((nothrow, warn_unused_result))
sll_node3_t *alloc_sll_node4 (sll_node3_t *restrict next,
	size_t esz) {
	void *restrict *restrict combined[2];
	size_t eszs[2];
	/*sll_node3_t *restrict caq;*/
	void *restrict caq;
	void *restrict data;

	eszs[0] = sizeof (sll_node3_t);
	eszs[1] = esz;
	combined[0] = &caq;
	combined[1] = &data;
	error_check (mmalloc2 (combined, eszs,
		eszs[0] + eszs[1], ARRSZ (eszs)) != 0)
		return NULL;

	init_sll_node3 ((sll_node3_t *) caq, next, esz);
	((sll_node3_t *) caq)->data = data;
	return (sll_node3_t *) caq;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void setNext_sll_node3 (sll_node3_t *restrict sll,
	sll_node3_t *restrict next) {
	sll->next = next;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
sll_node3_t *getNext_sll_node3 (sll_node3_t const *restrict sll) {
	return sll->next;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool hasNext_sll_node3 (sll_node3_t const *restrict sll) {
	return sll->next == NULL;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void setData_sll_node3 (sll_node3_t *restrict sll,
	void *restrict data, size_t esz) {
	sll->data = data;
	sll->esz  = esz;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void setData_sll_node4 (sll_node3_t *restrict sll,
	void const *restrict data) {
	(void) memcpy (sll->data, data, sll->esz);
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
void *getData_sll_node3 (sll_node3_t const *restrict sll) {
	return sll->data;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void getData_sll_node4 (sll_node3_t const *restrict sll,
	void *restrict data) {
	(void) memcpy (data, sll->data, sll->esz);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void free_sll_node3 (sll_node3_t *restrict sll, free_t f) {
	f (sll->data);
	free (sll);
}
/*
__attribute__ ((leaf, nonnull (1), nothrow))
void free_sll_node4 (sll_node_t *restrict sll) {
	free (sll);
}
*/
__attribute__ ((leaf, nonnull (1), nothrow))
void free_sll_node4 (sll_node3_t *restrict sll) {
	free (sll);
}
