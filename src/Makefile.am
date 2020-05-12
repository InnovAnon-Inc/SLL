AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#
##SUBDIRS += ../swap
##AM_CPPFLAGS += -I $(top_srcdir)/swap/src
#
#SUBDIRS += ../MultiMalloc
#AM_CPPFLAGS += -I $(top_srcdir)/MultiMalloc/src
#endif

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

#include Makefile-LIBADD.inc
dist_bin_SCRIPTS = libsll_node_config libsll_node3_config libsll_config sll_test_config

lib_LTLIBRARIES += libsll_node.la
#libsll_node_la_LIBADD = $(LIBSLL_NODE_LIBADD)
libsll_node_la_LIBADD = @LIBSLL_NODE_LIBADD@
include_HEADERS += sll_node.h

lib_LTLIBRARIES += libsll_node3.la
libsll_node3_la_LIBADD = @LIBSLL_NODE3_LIBADD@
include_HEADERS += sll_node3.h

lib_LTLIBRARIES += libsll.la
#libsll_la_LIBADD = $(LIBSLL_LIBADD)
#libsll_la_LIBADD = libsll_node.la $(LIBSLL_NODE_LIBADD)
libsll_la_LIBADD = @LIBSLL_LIBADD@
EXTRA_libsll_la_DEPENDENCIES = libssl_node.la
include_HEADERS += sll.h
#include ../../Array/src/Makefile-LIBADD.inc
bin_PROGRAMS += sll-test
#sll_test_LDADD = -lsll $(LIBSLL_LIBADD) -larray $(LIBARRAY_LIBADD)
#sll_test_LDADD = libsll.la $(LIBSLL_LIBADD) -larray $(LIBARRAY_LIBADD)
#sll_test_LDADD = libsll.la libsll_node.la -larray $(LIBARRAY_LIBADD)
#sll_test_LDADD = $(SLL_TEST_LIBADD)
sll_test_LDADD = @SLL_TEST_LIBADD@
EXTRA_sll_test_DEPENDENCIES = libsll.la
