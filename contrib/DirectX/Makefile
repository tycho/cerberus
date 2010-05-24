# -*- Makefile -*- for DirectX

ifneq ($(findstring $(MAKEFLAGS),s),s)
ifndef V
        QUIET_CXX      = @echo '   ' CXX $@;
        QUIET_AR       = @echo '   ' AR $@;
        QUIET_RANLIB   = @echo '   ' RANLIB $@;
        QUIET_INSTALL  = @echo '   ' INSTALL $<;
        export V
endif
endif

prefix ?= /usr/local
libdir := $(prefix)/lib
includedir := $(prefix)/include

HEADERS = \
    d3d.h \
    d3dcaps.h \
    d3drm.h \
    d3drmdef.h \
    d3drmobj.h \
    d3drmwin.h \
    d3dtypes.h \
    d3dvec.inl \
    d3dx.h \
    d3dxcore.h \
    d3dxerr.h \
    d3dxmath.h \
    d3dxmath.inl \
    d3dxshapes.h \
    d3dxsprite.h \
    ddraw.h \
    dinput.h \
    dinputd.h \
    dls1.h \
    dls2.h \
    dmdls.h \
    dmerror.h \
    dmksctrl.h \
    dmusbuff.h \
    dmusicc.h \
    dmusicf.h \
    dmusici.h \
    dplay.h \
    dplobby.h \
    dsetup.h \
    dsound.h \
    dvp.h \
    dxfile.h \
    dxsdk.inc \
    multimon.h \
    rmxfguid.h \
    rmxftmpl.h \
    rmxftmpl.x

LIBS = \
    DSETUP.lib \
    d3dim.lib \
    d3drm.lib \
    d3dx.lib \
    d3dxof.lib \
    ddraw.lib \
    dinput.lib \
    dplayx.lib \
    dsound.lib \
    dxguid.lib

HEADERS_INST := $(patsubst %,$(includedir)/%,$(HEADERS))
LIBS_INST := $(patsubst %.lib,$(libdir)/lib%.a,$(LIBS))

.PHONY: install

all:

$(includedir)/%: include/%
	-@if [ ! -d $(includedir)  ]; then mkdir -p $(includedir); fi
	$(QUIET_INSTALL)cp $< $@
	@chmod 0644 $@

$(libdir)/lib%.a: lib/%.lib
	-@if [ ! -d $(libdir)  ]; then mkdir -p $(libdir); fi
	$(QUIET_INSTALL)cp $< $@
	@chmod 0644 $@

install: $(HEADERS_INST) $(LIBS_INST)

clean:

distclean:
