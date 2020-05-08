#include $(top_srcdir)/swap/src/Makefile-LIBADD.inc
#include $(top_srcdir)/MultiMalloc/src/Makefile-LIBADD.inc

#if USE_SUBMODULES
#LIBSLL_LIBADD  =
##LIBSLL_LIBADD += ../swap/src/.libs/libswap.la $(LIBSWAP_LIBADD)
#LIBSLL_LIBADD += ../MultiMalloc/src/.libs/libmmalloc.la $(LIBMMALLOC_LIBADD)
#else
LIBSLL_NODE_LIBADD  =
#LIBSLL_NODE_LIBADD += -lswap $(LIBSWAP_LIBADD)
LIBSLL_NODE_LIBADD += -lmmalloc $(LIBMMALLOC_LIBADD)

LIBSLL_NODE3_LIBADD  =
#LIBSLL_NODE3_LIBADD += -lswap $(LIBSWAP_LIBADD)
LIBSLL_NODE3_LIBADD += -lmmalloc $(LIBMMALLOC_LIBADD)

LIBSLL_LIBADD  = -lsll_node $(LIBSLL_NODE_LIBADD)
#LIBSLL_LIBADD += -lsll_node3 $(LIBSLL_NODE3_LIBADD)
#endif
