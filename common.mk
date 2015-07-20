
# common flags used in openocd build
AM_CPPFLAGS = -I$(top_srcdir)/src \
			  -I$(top_builddir)/src \
			  -I$(top_srcdir)/src/helper \
			  -DPKGDATADIR=\"$(pkgdatadir)\" \
			  -DBINDIR=\"$(bindir)\"

# MinGW by default uses MSVCRT printf format specifiers
# This forces a compatibility header to be included at the start of every
# source file to ensure the printf functions are fully C99 compliant
if IS_MINGW
AM_CPPFLAGS += -include helper/mingw_compat.h
endif

if INTERNAL_JIMTCL
AM_CPPFLAGS += -I$(top_srcdir)/jimtcl \
			   -I$(top_builddir)/jimtcl
endif
