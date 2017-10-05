AM_CPPFLAGS = -D__STDC_INT64__

if USE_SUBMODULES
SUBDIRS = ../glitter
AM_CPPFLAGS += -I $(top_srcdir)/glitter/src

#SUBDIRS += ../swap
#AM_CPPFLAGS += -I $(top_srcdir)/swap/src

SUBDIRS += ../MultiMalloc
AM_CPPFLAGS += -I $(top_srcdir)/MultiMalloc/src
endif

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

include Makefile-LIBADD.inc

lib_LTLIBRARIES += libsll_node.la
libsll_node_la_LIBADD = $(LIBSLL_NODE_LIBADD)
include_HEADERS += sll_node.h

lib_LTLIBRARIES += libsll_node3.la
libsll_node3_la_LIBADD = $(LIBSLL_NODE3_LIBADD)
include_HEADERS += sll_node3.h

lib_LTLIBRARIES += libsll.la
libsll_la_LIBADD = $(LIBSLL_LIBADD)
include_HEADERS += sll.h
bin_PROGRAMS += sll-test
sll_test_LDADD = libsll.la $(LIBSLL_LIBADD)
