#ifndef _SLL_H_
#define _SLL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <sys/types.h>

#include <dsint.h>
#include <glitter.h>

#include <sll_node.h>

typedef struct {
   sll_node_t *restrict head;
   sll_node_t *restrict tail;
   size_t esz;
   size_t n;
} sll_t;

size_t sll_nodesz (size_t esz)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

size_t sllsz (size_t esz, size_t n)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

size_t sllsz2 (sll_t const *restrict sll)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

void *index_sll (sll_t const *restrict sll, size_t i)
__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result)) ;

void init_sll (sll_t *restrict sll, size_t esz)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void get_sll (sll_t const *restrict sll, size_t i,
   void *restrict e)
__attribute__ ((nonnull (1, 3), nothrow)) ;

void gets_sll (sll_t const *restrict sll, size_t i,
   void *restrict e, size_t n)
__attribute__ ((nonnull (1, 3), nothrow)) ;

void set_sll (sll_t const *restrict sll, size_t i,
	void const *restrict e)
__attribute__ ((nonnull (1, 3), nothrow)) ;

void sets_sll (sll_t const *restrict sll, size_t i,
	void const *restrict e, size_t n)
__attribute__ ((nonnull (1, 3), nothrow)) ;

void free_sll (sll_t const *restrict sll)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void cp_sll (sll_t const *restrict sll, size_t i, size_t j)
__attribute__ ((nonnull (1), nothrow)) ;

/* src and dest should not overlap */
void cps_sll (sll_t const *restrict sll,
	size_t i, size_t j, size_t n)
__attribute__ ((nonnull (1), nothrow)) ;

void mvs_sll (sll_t const *restrict sll,
	size_t i, size_t j, size_t n)
__attribute__ ((nonnull (1), nothrow)) ;

void swap_sll (sll_t const *restrict sll,
	size_t i, size_t j, void *restrict tmp)
__attribute__ ((nonnull (1, 4), nothrow)) ;

void swaps_sll (sll_t const *restrict sll,
	size_t i, size_t j, size_t n, void *restrict tmp)
__attribute__ ((nonnull (1, 5), nothrow)) ;

/* src and dest should not overlap ? */
void swap_sll2 (sll_t const *restrict sll,
	size_t i, size_t j)
__attribute__ ((nonnull (1), nothrow)) ;

/* src and dest should not overlap ? */
void swaps_sll2 (sll_t const *restrict sll,
	size_t i, size_t j, size_t n)
__attribute__ ((nonnull (1), nothrow)) ;

size_t indexOf_sll (sll_t const *restrict sll,
	void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

bool contains_sll (sll_t const *restrict sll,
	void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

ssize_t indexOf_sll_chk (sll_t const *restrict sll,
	void const *restrict e)
__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

void frees_sll (sll_t const *restrict sll, free_t cb)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;





void insert_rear_sll (sll_t *restrict sll, void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

int ez_insert_rear_sll (sll_t *restrict sll, void const *restrict e)
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result)) ;

void inserts_rear_sll (sll_t *restrict sll,
   void const *restrict e, size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

int ez_inserts_rear_sll (sll_t *restrict sll,
   void const *restrict e, size_t n)
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result)) ;

void insert_front_sll (sll_t *restrict sll, size_t i,
   void const *restrict e)
__attribute__ ((leaf, nonnull (1, 3), nothrow)) ;

int ez_insert_front_sll (sll_t *restrict sll, size_t i,
   void const *restrict e)
__attribute__ ((nonnull (1, 3), nothrow, warn_unused_result)) ;

void inserts_front_sll (sll_t *restrict sll, size_t i,
   void const *restrict e, size_t n)
__attribute__ ((leaf, nonnull (1, 3), nothrow)) ;

int ez_inserts_front_sll (sll_t *restrict sll, size_t i,
   void const *restrict e, size_t n)
__attribute__ ((nonnull (1, 3), nothrow, warn_unused_result)) ;

void remove_rear_sll (sll_t *restrict sll, void *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void removes_rear_sll (sll_t *restrict sll,
   void *restrict e, size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void remove_front_darr (darr_t *restrict darr, size_t i,
   void *restrict e)
__attribute__ ((leaf, nonnull (1, 3), nothrow)) ;

void removes_front_darr (darr_t *restrict darr, size_t i,
   void *restrict e, size_t n)
__attribute__ ((leaf, nonnull (1, 3), nothrow)) ;

void make_gaps_darr (darr_t *restrict darr,
   size_t const is[], size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void inserts_darr (darr_t *restrict darr, size_t const is[],
   void const *restrict e, size_t n)
__attribute__ ((nonnull (1, 2, 3), nothrow)) ;

int ez_inserts_darr (darr_t *restrict darr, size_t const is[],
   void const *restrict e, size_t n)
__attribute__ ((nonnull (1, 2, 3), nothrow, warn_unused_result)) ;

void unmake_gaps_darr (darr_t *restrict darr,
   size_t const is[], size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void removes_darr (darr_t *restrict darr, size_t const is[],
   void *restrict e, size_t n)
__attribute__ ((nonnull (1, 2, 3), nothrow)) ;

bool isfull_darr (darr_t const *restrict darr)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

bool isempty_darr (darr_t const *restrict darr)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

size_t remaining_space_darr (darr_t const *restrict darr)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

size_t used_space_darr (darr_t const *restrict darr)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

void free_darr (darr_t const *restrict darr)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

size_t indexOf_darr (darr_t const *restrict darr,
	void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

bool contains_darr (darr_t const *restrict darr,
	void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

ssize_t indexOf_darr_chk (darr_t const *restrict array,
   void const *restrict e)
__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

void *index_darr (darr_t const *restrict darr, size_t i)
__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result)) ;

void frees_darr (darr_t const *restrict darr, free_t cb)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _SLL_H_ */