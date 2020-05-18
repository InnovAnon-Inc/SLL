AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

lib_LTLIBRARIES += libsll_node.la
libsll_node_la_CPPFLAGS = $(GLITTER_CFLAGS) $(SWAP_CFLAGS) $(MMALLOC_CFLAGS)
libsll_node_la_LIBADD   = $(GLITTER_LIBS)   $(SWAP_LIBS)   $(MMALLOC_LIBS)
include_HEADERS += sll_node.h

lib_LTLIBRARIES += libsll_node3.la
libsll_node3_la_CPPFLAGS = $(GLITTER_CFLAGS) $(SWAP_CFLAGS) $(MMALLOC_CFLAGS)
libsll_node3_la_LIBADD   = $(GLITTER_LIBS)   $(SWAP_LIBS)   $(MMALLOC_LIBS)
include_HEADERS += sll_node3.h

lib_LTLIBRARIES += libsll.la
libsll_la_CPPFLAGS =            $(GLITTER_CFLAGS) $(DARR_CFLAGS) $(SWAP_CFLAGS) $(MMALLOC_CFLAGS)
libsll_la_LIBADD   = -lsll_node $(GLITTER_LIBS)   $(DARR_LIBS)   $(SWAP_LIBS)   $(MMALLOC_LIBS)
EXTRA_libsll_la_DEPENDENCIES = libsll_node.la
include_HEADERS += sll.h

bin_PROGRAMS += sll-test
sll_test_CPPFLAGS =                  $(GLITTER_CFLAGS) $(ARRAY_CFLAGS) $(SIMON_CFLAGS) $(SWAP_CFLAGS) $(MMALLOC_CFLAGS)
sll_test_LDADD    = -lsll -lsll_node $(GLITTER_LIBS)   $(ARRAY_LIBS)   $(SIMON_LIBS)   $(SWAP_LIBS)   $(MMALLOC_LIBS)
EXTRA_sll_test_DEPENDENCIES = libsll.la

