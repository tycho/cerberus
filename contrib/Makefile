PREFIX := install

SUBDIRS = DirectX SDL SDL_image SDL_mixer glew smpeg crisscross/source FTGL freetype libpng zlib unrar

ifdef USE_LUAJIT
SUBDIRS += luajit/src
else
SUBDIRS += lua/src
endif

all:
	@$(MAKE) $(SUBDIRS)

clean distclean:
	@for a in $(SUBDIRS); do \
		echo $$a; \
	    $(MAKE) -C $$a distclean; \
	done
	rm -rf $(PREFIX)

$(SUBDIRS):
	@if [ ! -x $@ ]; then \
	    echo "**********************************************************"; \
	    echo; \
	    echo "The '$@' folder is missing. Have you run"; \
	    echo "   'git submodule update --init'?"; \
	    echo; \
	    echo "**********************************************************"; \
	    exit 1; \
	fi
	@if [ ! -f $@/Makefile ] && [ ! -f $@/makefile ]; then \
	    echo "**********************************************************"; \
	    echo; \
	    echo "The '$@' folder exists, but the Makefile is missing!"; \
	    echo "Did 'git submodule update' work properly?"; \
	    echo; \
	    echo "**********************************************************"; \
	    exit 1; \
	fi
	@cd $@ && \
	$(MAKE) all prefix=$(shell echo $@ | perl -pe 's/[^\/]+/../g')/$(PREFIX) && \
	$(MAKE) install prefix=$(shell echo $@ | perl -pe 's/[^\/]+/../g')/$(PREFIX)

FTGL: freetype
libpng freetype: zlib
SDL: DirectX
SDL_image: SDL libpng
SDL_mixer: smpeg

.PHONY: $(SUBDIRS)
