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

#include <sll_node.h>

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t sll_nodesz (void) {
	return sizeof (sll_node_t);
}

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t sll_nodesz2 (size_t esz) {
	return sizeof (sll_node_t) + esz;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void init_sll_node (sll_node_t *restrict sll,
	sll_node_t /*const*/ *restrict next) {
	sll->next = next;
}

__attribute__ ((nothrow, warn_unused_result))
sll_node_t *alloc_sll_node (sll_node_t *restrict next) {
	sll_node_t *restrict ret = alloc (sizeof (sll_node_t));
	error_check (ret == NULL) return NULL;
	init_sll_node (ret, next);
	return ret;
}

__attribute__ ((nothrow, warn_unused_result))
sll_node_t *alloc_sll_node2 (sll_node_t /*const*/ *restrict next,
	size_t esz) {
	void *restrict *restrict combined[2];
	size_t eszs[2];
	sll_node_t *restrict caq;
	void *restrict data;

	eszs[0] = sizeof (sll_node_t);
	eszs[1] = esz;
	combined[0] = (void *restrict *restrict) &caq;
	combined[1] = (void *restrict *restrict) &data;
	error_check (mmalloc2 (combined, eszs,
		eszs[0] + eszs[1], ARRSZ (eszs)) != 0)
		return NULL;

	init_sll_node (caq, next);
	caq->data = data;
	return caq;
}

__attribute__ ((nonnull (2), nothrow, warn_unused_result))
sll_node_t *alloc_sll_node2 (sll_node_t /*const*/ *restrict next,
	void *restrict data, size_t esz) {
	void *restrict *restrict combined[2];
	size_t eszs[2];
	sll_node_t *restrict caq;
	void *restrict data;

	eszs[0] = sizeof (sll_node_t);
	eszs[1] = esz;
	combined[0] = (void *restrict *restrict) &caq;
	combined[1] = (void *restrict *restrict) &data;
	error_check (mmalloc2 (combined, eszs,
		eszs[0] + eszs[1], ARRSZ (eszs)) != 0)
		return NULL;

	init_sll_node2 (caq, next, data, esz);
	return caq;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void setNext_sll_node (sll_node_t *restrict sll,
	sll_node_t /*const*/ *restrict next) {
	sll->next = next;
}

__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result))
sll_node_t *getNext_sll_node (sll_node_t *restrict sll) {
	return sll->next;
}

__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result))
bool hasNext_sll_node (sll_node_t *restrict sll) {
	return sll->next == NULL;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void setData_sll_node (sll_node_t *restrict sll,
	void *restrict data) {
	sll->data = data;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void setData_sll_node2 (sll_node_t *restrict sll,
	void *restrict data, size_t esz) {
	(void) memcpy (sll->data, data, esz);
}

__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result))
void *getData_sll_node (sll_node_t *restrict sll) {
	return sll->data;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void setData_sll_node2 (sll_node_t *restrict sll,
	void *restrict data, size_t esz) {
	(void) memcpy (data, sll->data, esz);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void free_sll_node (sll_node_t *restrict sll, free_t f) {
	f (sll->data);
	free (sll);
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_sll_node2 (sll_node_t *restrict sll) {
	free (sll);
}
