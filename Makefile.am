# Install the pkg-config file.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libsll.pc src/libsll_node.pc src/libsll_node3.pc src/sll-test.pc

DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = src/libsll.pc.in src/libsll_node.pc.in src/libsll_node3.pc.in src/sll-test.pc.in

SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4

