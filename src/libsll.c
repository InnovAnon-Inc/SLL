#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <assert.h>
#include <limits.h>
#ifndef NDEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>

#include <mmalloc.h>
#include <swap.h>

#include <sll.h>

__attribute ((const, leaf, nothrow, warn_unused_result))
bool isempty_sll (sll_t *restrict sll) {
   bool ret = sll->head == NULL;
   assert (sll->tail == NULL);
   return ret;
}

__attribute ((const, leaf, nothrow, warn_unused_result))
bool hasone_sll (sll_t *restrict sll) {
   return ! isempty_sll (sll) && sll->head == sll->tail;
}

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t sll_nodesz (size_t esz) {
	return sizeof (sll_node_t) + esz;
}

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t sllsz (size_t esz, size_t n) {
	return sizeof (sll_t) + n * sll_nodesz (esz);
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
size_t sllsz2 (sll_t const *restrict sll) {
	return sllsz (sll->esz, sll->n);
}



__attribute__ ((leaf, nonnull (1), nothrow))
void init_sll (sll_t *restrict sll, size_t esz) {
	sll->head = NULL;
	sll->tail = NULL;
	sll->esz  = esz;
	sll->n    = (size_t) 0;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void insert_rear_sll (sll_t *restrict sll, void const *restrict e) {
	/*sll_node *restrict node = alloc_sll_node (sll->esz);*/
	sll_node_t *restrict node = alloc_sll_node2 (NULL, sll->esz);
	if (isempty_sll (sll))
		sll->head = node;
	else if (hasone_sll (sll))
		setNext_sll_node (sll->head, node);
	else
		setNext_sll_node (sll->tail, node);
	sll->tail = node;
	sll->n++;
}

#ifdef WTFDARR
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
int ez_insert_rear_darr (darr_t *restrict darr, void const *restrict e) {
   error_check (ensure_cap_darr (darr, darr->n + 1) != 0) return -1;
   insert_rear_darr (darr, e);
   return 0;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void inserts_rear_darr (darr_t *restrict darr,
   void const *restrict e, size_t n) {
   assert (remaining_space_darr (darr) >= n);
#ifndef NDEBUG
   fprintf (stderr, "inserts rear()\n");
   /*fprintf (stderr, "i    : %d\n", (int) i);*/
   fprintf (stderr, "n    : %d\n", (int) n);
   /*fprintf (stderr, "i + 1: %d\n", (int) (i + 1));*/
   fprintf (stderr, "curN : %d\n", (int) (darr->n));
   fprintf (stderr, "maxN : %d\n", (int) (darr->array.n));
   /*fprintf (stderr, "mv   : %d\n", (int) mv);*/
#endif
   sets_array (&(darr->array), darr->n, e, n);
   darr->n += n;
   assert (darr->n >= n);
}

__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
int ez_inserts_rear_darr (darr_t *restrict darr,
   void const *restrict e, size_t n) {
   error_check (ensure_cap_darr (darr, darr->n + n) != 0) return -1;
   inserts_rear_darr (darr, e, n);
   return 0;
}

__attribute__ ((leaf, nonnull (1, 3), nothrow))
void insert_front_darr (darr_t *restrict darr, size_t i,
   void const *restrict e) {
   size_t mv;
   assert (! isfull_darr (darr));
   if (i + 1 >= darr->n)
      mv = darr->n - i;
   else
      mv = darr->n - (i + 1);
#ifndef NDEBUG
   fprintf (stderr, "insert front()\n");
   fprintf (stderr, "i    : %d\n", (int) i);
   /*fprintf (stderr, "n    : %d\n", (int) n);*/
   fprintf (stderr, "i + 1: %d\n", (int) (i + 1));
   fprintf (stderr, "curN : %d\n", (int) (darr->n));
   fprintf (stderr, "maxN : %d\n", (int) (darr->array.n));
   fprintf (stderr, "mv   : %d\n", (int) mv);
#endif
   mvs_array (&(darr->array), i + 0, i + 1, mv);
   set_array (&(darr->array), i + 0, e);
   darr->n++;
   assert (darr->n <= darr->array.n);
#ifdef TEST
   /*if (i != darr->n)*/
      mvs_array (&(darr->array), i + 0, i + 1, darr->n - i);
   set_array (&(darr->array), i + 0, e);
   darr->n++;
   assert (darr->n <= darr->array.n);
#endif
}

__attribute__ ((nonnull (1, 3), nothrow, warn_unused_result))
int ez_insert_front_darr (darr_t *restrict darr, size_t i,
   void const *restrict e) {
   error_check (ensure_cap_darr (darr, darr->n + 1) != 0) return -1;
   insert_front_darr (darr, i, e);
   return 0;
}

__attribute__ ((leaf, nonnull (1, 3), nothrow))
void inserts_front_darr (darr_t *restrict darr, size_t i,
   void const *restrict e, size_t n) {
   size_t mv;
   assert (remaining_space_darr (darr) >= n);
   if (i + n >= darr->n)
      mv = darr->n - i;
   else
      mv = darr->n - (i + n);
#ifndef NDEBUG
   fprintf (stderr, "inserts front()\n");
   fprintf (stderr, "i    : %d\n", (int) i);
   fprintf (stderr, "n    : %d\n", (int) n);
   fprintf (stderr, "i + n: %d\n", (int) (i + n));
   fprintf (stderr, "curN : %d\n", (int) (darr->n));
   fprintf (stderr, "maxN : %d\n", (int) (darr->array.n));
   fprintf (stderr, "mv   : %d\n", (int) mv);
#endif
   mvs_array (&(darr->array), i + 0, i + n, mv);
   sets_array (&(darr->array), i + 0, e, n);
   darr->n += n;
   assert (darr->n >= n);
#ifdef TEST
   if (i + n >= darr->n)
      mv = darr->n - i;
   else
      mv = darr->n - (i + n);
      /*mv = darr->n - i;*/
      /*mv = n;*/
   /*if (mv != 0)*/
   mvs_array (&(darr->array), i + 0, i + n, mv);
   sets_array (&(darr->array), i + 0, e, n);
   darr->n += n;
   assert (darr->n >= n);
#endif
}

__attribute__ ((nonnull (1, 3), nothrow, warn_unused_result))
int ez_inserts_front_darr (darr_t *restrict darr, size_t i,
   void const *restrict e, size_t n) {
   error_check (ensure_cap_darr (darr, darr->n + n) != 0) return -1;
   inserts_front_darr (darr, i, e, n);
   return 0;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void remove_rear_darr (darr_t *restrict darr, void *restrict e) {
   assert (! isempty_darr (darr));
#ifndef NDEBUG
   fprintf (stderr, "remove rear()\n");
   /*fprintf (stderr, "i    : %d\n", (int) i);*/
   /*fprintf (stderr, "n    : %d\n", (int) n);*/
   /*fprintf (stderr, "i + 1: %d\n", (int) (i + 1));*/
   fprintf (stderr, "curN : %d\n", (int) (darr->n));
   fprintf (stderr, "maxN : %d\n", (int) (darr->array.n));
   /*fprintf (stderr, "mv   : %d\n", (int) mv);*/
#endif
   get_array (&(darr->array), darr->n - 1, e);
   darr->n--;
   assert (darr->n != SIZE_MAX);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void removes_rear_darr (darr_t *restrict darr,
   void *restrict e, size_t n) {
   assert (darr->n >= n || n == 0);
#ifndef NDEBUG
   fprintf (stderr, "removes rear()\n");
   /*fprintf (stderr, "i    : %d\n", (int) i);*/
   fprintf (stderr, "n    : %d\n", (int) n);
   /*fprintf (stderr, "i + 1: %d\n", (int) (i + 1));*/
   fprintf (stderr, "curN : %d\n", (int) (darr->n));
   fprintf (stderr, "maxN : %d\n", (int) (darr->array.n));
   /*fprintf (stderr, "mv   : %d\n", (int) mv);*/
#endif
   gets_array (&(darr->array), darr->n - n, e, n);
   darr->n -= n;

#ifdef TEST
#ifndef NDEBUG
   fprintf (stderr, "remaining:  %d\n", (int) remaining_space_darr (darr));
   fprintf (stderr, "amt_to_add: %d\n", (int) n);
#endif
   assert (darr->n >= n || n == 0);
   gets_array (&(darr->array), darr->n - n, e, n);
   darr->n -= n;
   TODO (check underflow)
#endif
}

__attribute__ ((leaf, nonnull (1, 3), nothrow))
void remove_front_darr (darr_t *restrict darr, size_t i,
   void *restrict e) {
   size_t mv;
   assert (! isempty_darr (darr));
   assert (darr->n >= 1);
   if (i + 1 >= darr->n)
      mv = darr->n - i - 1;
   else
      mv = darr->n - (i + 1) - 1;
#ifndef NDEBUG
   fprintf (stderr, "remove front()\n");
   fprintf (stderr, "i    : %d\n", (int) i);
   /*fprintf (stderr, "n    : %d\n", (int) n);*/
   fprintf (stderr, "i + 1: %d\n", (int) (i + 1));
   fprintf (stderr, "curN : %d\n", (int) (darr->n));
   fprintf (stderr, "maxN : %d\n", (int) (darr->array.n));
   fprintf (stderr, "mv   : %d\n", (int) mv);
#endif
   get_array (&(darr->array), i + 0, e);
   mvs_array (&(darr->array), i + 1, i + 0, mv);
   darr->n--;
#ifdef TEST
   assert (! isempty_darr (darr));
   get_array (&(darr->array), i + 0, e);
   if (i != darr->n)
      mvs_array (&(darr->array), i + 1, i + 0, darr->n - i - 1);
   darr->n--;
   assert (darr->n != SIZE_MAX);
#endif
}

__attribute__ ((leaf, nonnull (1, 3), nothrow))
void removes_front_darr (darr_t *restrict darr, size_t i,
   void *restrict e, size_t n) {
   size_t mv;
/*#ifndef NDEBUG
   fprintf (stderr, "remaining:  %d\n", (int) remaining_space_darr (darr));
   fprintf (stderr, "amt_to_rem: %d\n", (int) n);
#endif*/
   assert (darr->n >= n || n == 0);
   assert (! isempty_darr (darr));
   assert (darr->n >= n);
   if (i + n >= darr->n)
      mv = darr->n - i - 1;
   else
      mv = darr->n - (i + n) - 1;
#ifndef NDEBUG
   fprintf (stderr, "removes front()\n");
   fprintf (stderr, "i    : %d\n", (int) i);
   fprintf (stderr, "n    : %d\n", (int) n);
   fprintf (stderr, "i + n: %d\n", (int) (i + n));
   fprintf (stderr, "curN : %d\n", (int) (darr->n));
   fprintf (stderr, "maxN : %d\n", (int) (darr->array.n));
   fprintf (stderr, "mv   : %d\n", (int) mv);
#endif
   gets_array (&(darr->array), i + 0, e, n);
   mvs_array (&(darr->array), i + n, i + 0, mv);
   darr->n -=n;
#ifdef TEST
   sets_array (&(darr->array), i + 0, e, n);
   /* TODO i + n != darr->n*/
   if (i + n < darr->n)
      mvs_array (&(darr->array), i + n, i + 0, darr->n - i - n);
   darr->n -= n;
   TODO (check underflow)
#endif
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void make_gaps_darr (darr_t *restrict darr,
   size_t const is[], size_t n) {
   size_t i, prev;
   assert (remaining_space_darr (darr) <= n);
   for (i = n, prev = darr->n; i != 0; i--, prev = is[i])
      mvs_array (&(darr->array),
         is[i - 1], is[i - 1] + i, prev - is[i - 1]);

   darr->n += n;
   assert (darr->n >= n);
}

__attribute__ ((nonnull (1, 2, 3), nothrow))
void inserts_darr (darr_t *restrict darr, size_t const is[],
   void const *restrict e, size_t n) {
   array_t tmp;
   size_t i;
   void const *restrict E;

   make_gaps_darr (darr, is, n);

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
   init_array (&tmp, e, darr->array.esz, n);
	#pragma GCC diagnostic pop

	#pragma GCC ivdep
   for (i = 0; i != n; i++) {
      E = index_array (&tmp, i);
      set_array (&(darr->array), is[i] + i, E);
   }
}

__attribute__ ((nonnull (1, 2, 3), nothrow, warn_unused_result))
int ez_inserts_darr (darr_t *restrict darr, size_t const is[],
   void const *restrict e, size_t n) {
   error_check (ensure_cap_darr (darr, darr->n + n) != 0) return -1;
   inserts_darr (darr, is, e, n);
   return 0;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void unmake_gaps_darr (darr_t *restrict darr,
   size_t const is[], size_t n) {
   size_t i;
   assert (remaining_space_darr (darr) >= n);
   for (i = 0; i != n - 1; i++)
      mvs_array (&(darr->array), is[i], is[i] + i, is[i + 1] - is[i]);
   mvs_array (&(darr->array), is[i], is[i] + i, darr->n - is[i]);

   darr->n -= n;
   TODO (check underflow)
}

__attribute__ ((nonnull (1, 2, 3), nothrow))
void removes_darr (darr_t *restrict darr, size_t const is[],
   void *restrict e, size_t n) {
   array_t tmp;
   size_t i;
   void *restrict E;

   init_array (&tmp, e, darr->array.esz, n);

	#pragma GCC ivdep
   for (i = 0; i != n; i++) {
      E = index_array (&tmp, i);
      get_array (&(darr->array), is[i] /*+ i*/, E);
   }

   unmake_gaps_darr (darr, is, n);
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isfull_darr (darr_t const *restrict darr) {
   if (darr->n == darr->array.n) {
      assert (remaining_space_darr (darr) == 0);
      return true;
   }
   assert (remaining_space_darr (darr) != 0 || darr->array.n == 0);
   return false;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isempty_darr (darr_t const *restrict darr) {
   if (darr->n == 0) {
      assert (remaining_space_darr (darr) != 0 || darr->array.n == 0);
      return true;
   }
   /*assert (remaining_space_darr (darr) == 0);*/
   return false;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
size_t remaining_space_darr (darr_t const *restrict darr) {
   return darr->array.n - darr->n;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
size_t used_space_darr (darr_t const *restrict darr) {
   return darr->n;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_darr (darr_t const *restrict darr) {
   free_array (&(darr->array));
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
size_t indexOf_darr (darr_t const *restrict darr,
	void const *restrict e) {
   size_t ret;
   array_t tmp;
   init_array2 (&tmp, &(darr->array), (size_t) 0, darr->n);
   ret = indexOf_array (&tmp, e);
   assert (ret < darr->n);
   return ret;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
bool contains_darr (darr_t const *restrict darr,
	void const *restrict e) {
   bool ret;
   array_t tmp;
   init_array2 (&tmp, &(darr->array), (size_t) 0, darr->n);
   ret = contains_array (&tmp, e);
   return ret;
}

__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result))
ssize_t indexOf_darr_chk (darr_t const *restrict darr,
   void const *restrict e) {
   ssize_t ret;
   array_t tmp;
   init_array2 (&tmp, &(darr->array), (size_t) 0, darr->n);
   ret = indexOf_array_chk (&tmp, e);
   assert (ret == (ssize_t) -1 || ret < (ssize_t) darr->n);
   return ret;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result))
void *index_darr (darr_t const *restrict darr, size_t i) {
   array_t tmp;
   init_array2 (&tmp, &(darr->array), (size_t) 0, darr->n);
   return index_array (&tmp, i);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void frees_darr (darr_t const *restrict darr, free_t f) {
   array_t tmp;
   init_array2 (&tmp, &(darr->array), (size_t) 0, darr->n);
   frees_array (&tmp, f);
}
#endif








































NOTE (this would be way faster if esz were static
	i.e. this is the cost of this style of generics)
__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result))
void *index_array (array_t const *restrict array, size_t i) {
	char *restrict data;
	char *restrict ret;
	assert (i < array->n || (i == 0 && array->n == 0));
	data = (char *restrict) array->data;
	ret  = data + i * array->esz;
	return (void *restrict) ret;
}

__attribute__ ((nonnull (1, 3), nothrow))
void get_array (array_t const *restrict array, size_t i,
	void *restrict e) {
	void const *restrict src = index_array (array, i);
	(void) memcpy (e, src, array->esz);
	assert (memcmp (src, e, array->esz) == 0);
}

__attribute__ ((nonnull (1, 3), nothrow))
void gets_array (array_t const *restrict array, size_t i,
	void *restrict e, size_t n) {
	void const *restrict src;
	/*assert (i + n < array->n);*/
	assert (i + n <= array->n);
	if (n == 0) return;
	src = index_array (array, i);
	(void) memcpy (e, src, datasz (array->esz, n));
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1, 3), nothrow))
void set_array (array_t const *restrict array, size_t i,
	void const *restrict e) {
	void *restrict dest = index_array (array, i);
	(void) memcpy (dest, e, array->esz);
	assert (memcmp (dest, e, array->esz) == 0);
}

__attribute__ ((nonnull (1, 3), nothrow))
void sets_array (array_t const *restrict array, size_t i,
	void const *restrict e, size_t n) {
	void *restrict dest;
	/*assert (i + n < array->n);*/
	assert (i + n <= array->n);
	if (n == 0) return;
	dest = index_array (array, i);
	(void) memcpy (dest, e, datasz (array->esz, n));
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1), nothrow))
void cp_array (array_t const *restrict array, size_t i, size_t j) {
	void const *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	memcpy (dest, src, array->esz);
	assert (memcmp (src, dest, array->esz) == 0);
}

/* src and dest should not overlap */
__attribute__ ((nonnull (1), nothrow))
void cps_array (array_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void const *restrict src;
	void *restrict dest;
	/*assert (i + n < array->n);
	assert (j + n < array->n);
	assert (i + n < j || j + n < i);*/
	assert (i + n <= array->n);
	assert (j + n <= array->n);
	assert (i + n <= j || j + n <= i);
	src  = index_array (array, i);
	dest = index_array (array, j);
	memcpy (dest, src, datasz (array->esz, n));
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1), nothrow))
void mvs_array (array_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void const *src;
	void *dest;
	/*assert (i + n < array->n);
	assert (j + n < array->n);*/
	assert (i + n <= array->n);
	assert (j + n <= array->n);
	if (n == 0) return;
	src  = index_array (array, i);
	dest = index_array (array, j);
	memmove (dest, src, datasz (array->esz, n));
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1, 4), nothrow))
void swap_array (array_t const *restrict array,
	size_t i, size_t j, void *restrict tmp) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	swap (src, dest, tmp, array->esz);
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1, 5), nothrow))
void swaps_array (array_t const *restrict array,
	size_t i, size_t j, size_t n, void *restrict tmp) {
	void *restrict src;
	void *restrict dest;
	/*assert (i + n < array->n);
	assert (j + n < array->n);*/
	assert (i + n <= array->n);
	assert (j + n <= array->n);
	src  = index_array (array, i);
	dest = index_array (array, j);
	swaps (src, dest, tmp, array->esz, n);
	TODO (verify that data is correctly copied)
}

/* src and dest should not overlap ? */
__attribute__ ((nonnull (1), nothrow))
void swap_array2 (array_t const *restrict array,
	size_t i, size_t j) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	swap2 (src, dest, array->esz);
	TODO (verify that data is correctly copied)
}

/* src and dest should not overlap ? */
__attribute__ ((nonnull (1), nothrow))
void swaps_array2 (array_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void *restrict src  = index_array (array, i);
	void *restrict dest = index_array (array, j);
	swaps2 (src, dest, array->esz, n);
	TODO (verify that data is correctly copied)
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_array (array_t const *restrict array) {
	free (array->data);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
size_t indexOf_array (array_t const *restrict array,
	void const *restrict e) {
	size_t i;
	void *restrict tmp;
	TODO (is this pragma ok ?)
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		tmp = index_array (array, i);
		if (memcmp (tmp, e, array->esz) == 0)
			return i;
	}
	assert (false);
	__builtin_unreachable ();
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
bool contains_array (array_t const *restrict array,
	void const *restrict e) {
	size_t i;
	void *restrict tmp;
	TODO (is this pragma ok ?)
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		tmp = index_array (array, i);
		if (memcmp (tmp, e, array->esz) == 0)
			return true;
	}
	return false;
}

__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result))
ssize_t indexOf_array_chk (array_t const *restrict array,
	void const *restrict e) {
	size_t i;
	void *restrict tmp;
	TODO (is this pragma ok ?)
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		tmp = index_array (array, i);
		if (memcmp (tmp, e, array->esz) == 0)
			return (ssize_t) i;
	}
	return (ssize_t) -1;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void frees_array (array_t const *restrict array, free_t f) {
	size_t i;
	void *restrict tmp;
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		tmp = index_array (array, i);
		f (tmp);
	}
}

/*
typedef __attribute__ ((nonnull (1, 3), warn_unused_result))
size_t (*print_elem_t) (char buf[], size_t bufsz,
	void const *restrict e) ;

typedef __attribute__ ((nonnull (1), warn_unused_result))
size_t (*print_sep_t) (char buf[], size_t bufsz) ;

TODO (maybe change to toString_data())

__attribute__ ((leaf, nonnull (1, 3, 4, 5), nothrow, warn_unused_result))
size_t toString_array (char buf[], size_t busfz,
	print_elem_t print_elem, print_sep_t print_sep,
	array_t const *restrict array) {
	size_t i, prt;
	void *restrict e;
	if (array->n == 0) return ?;

	e   = index_array (array, 0);
	prt = print_elem (buf + prt, bufsz - prt, e);

	for (i = 1; i != array->n && prt != bufsz; i++) {
		prt += print_sep  (buf + prt, bufsz - prt);
		if (prt == bufsz) break;
		e = index_array (array, i);
		prt += print_elem (buf + prt, bufsz - prt, e);
	}
	return prt;
}
*/

/* one version takes a statically allocated array */
/* another allocates it for you, based on the number of separators */
/*
__attribute__ ((leaf, nonnull (1, 3, 4), nothrow, warn_unused_result))
size_t fromString_array (array_t *restrict array,
	char const buf[], size_t busfz,
	parse_elem_t parse_elem) {
	TODO ()
	size_t i, prt;
	void *restrict e;
	if (array->n == 0) return;

	e   = index_array (array, 0);
	prt = print_elem (buf + prt, bufsz - prt, e);

	for (i = 1; i != array->n && prt != bufsz; i++) {
		prt += print_sep  (buf + prt, bufsz - prt);
		if (prt == bufsz) break;
		e = index_array (array, i);
		prt += print_elem (buf + prt, bufsz - prt, e);
	}
	return prt;
}
*/
/*
void toStdint_array (void *restrict buf, array_t const *restrict array) {
	*((uint64_t *) buf++) = array->n;
	*((uint64_t *) buf++) = array->esz;
	(void) memcpy (buf, array->data, datasz (array->esz, array->n));
}

void fromStdint_array (array_t *restrict array, void const *restrict buf) {
	array->n   = *((uint64_t *) buf++);
	array->esz = *((uint64_t *) buf++);
	(void) memcpy (array->data, buf, datasz (array->esz, array->n));
}
*/
