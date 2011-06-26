#
# Cerberus
# GNU Makefile
#
# largely written by Steven Noonan <steven@uplinklabs.net>
#    (if something breaks, blame him.)
#

all:

GAME = cerberus

MAKEFLAGS += -Rr --no-print-directory

#
# Compiler Flags
#
# The compiler flag variables are separated into their individual
# purposes, making it easier to deal with the various tools involved
# in a compile.
#
# These are also divided into global vs. local flags. So for instance,
# CFOPTIMIZE affects Cerberus, SDL, and SDL_mixer, while CFOPTIMIZE_L only
# affects Cerberus.
#
# The variables are as follows:
# CFOPTIMIZE(_L) - Optimization flags
# CFWARN(_L) - Warning flags
# CFOTHERS(_L) - Anything else
#

ifdef USE_ICC

# If you have a Core 2 processor, this _really_ makes things fly:
#CFOPTIMIZE := -O2 -parallel -xT

# Optionally enable the 'ipo' feature, to facilitate inlining
# across object file bounds.
#CFOPTIMIZE_L := -ipo

# Some very good optimization flags.
CFOPTIMIZE := -O2 -parallel

else

CFOPTIMIZE := -O0 -ggdb

endif # USE_ICC

CFOTHERS := -fno-strict-aliasing -pipe $(EXTERNAL_FLAGS)
CFOTHERS_L := -fsigned-char
CFWARN := -Wall
CFWARN_L := -Wundef -Wno-long-long -Wno-variadic-macros -Wno-format -Wno-non-virtual-dtor

DEFINES := $(EXTERNAL_DEFINES)

#
# The GCC and GXX variables are set later.
#
AR = ar
RANLIB = ranlib
CC = $(GCC)
CXX = $(GXX)
RM = rm -f
COPY = cp
COPY_R = cp -r
STRIP = strip
WINDRES = windres
CHMOD = chmod 2>/dev/null
CHOWN = chown 2>/dev/null

export AR
export RANLIB
export RM
export CC
export CXX
export CFLAGS
export MAKEFLAGS
export CONFIGURE_FLAGS
export uname_S

CONTRIB := ../contrib

LIBCRISSCROSS := $(CONTRIB)/install/lib/libCrissCross.a
ifdef USE_LUAJIT
LIBLUA := $(CONTRIB)/install/lib/libluajit.a
else
LIBLUA := $(CONTRIB)/install/lib/liblua.a
endif
LIBFREETYPE := $(CONTRIB)/install/lib/libfreetype.a
LIBFTGL := $(CONTRIB)/install/lib/libftgl.a
LIBGLEW := $(CONTRIB)/install/lib/libglew.a
LIBSDL := $(CONTRIB)/install/lib/libSDL.a
LIBPNG := $(CONTRIB)/install/lib/libpng.a
LIBSDLIMAGE := $(CONTRIB)/install/lib/libSDL_image.a
LIBSDLMIXER := $(CONTRIB)/install/lib/libSDL_mixer.a
LIBSMPEG := $(CONTRIB)/install/lib/libsmpeg.a
LIBTOLUAPP := $(CONTRIB)/install/lib/libtolua++.a
LIBUNRAR := $(CONTRIB)/install/lib/libunrar.a
LIBZ := $(CONTRIB)/install/lib/libz.a

#
# Platform Detection
#
uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')
uname_M := $(shell sh -c 'uname -m 2>/dev/null || echo not')
uname_O := $(shell sh -c 'uname -o 2>/dev/null || echo not')
uname_R := $(shell sh -c 'uname -r 2>/dev/null || echo not')
uname_P := $(shell sh -c 'uname -p 2>/dev/null || echo not')
uname_V := $(shell sh -c 'uname -v 2>/dev/null || echo not')

ifdef CROSSHOST
	NO_AUTO_OPT = YesPlease
	NEED_STATIC = YesPlease
	CONFIGURE_FLAGS += --host=$(CROSSHOST)

	# If needed, override uname_S so we get the appropriate
	# things compiled.
	ifneq (,$(findstring mingw,$(CROSSHOST)))
		uname_S=MINGW32
	endif
endif
ifneq (,$(findstring MINGW,$(uname_S)))
	GAME = Cerberus.exe
	bin_prefix = .
	WIN32 = Yes
	NO_RDYNAMIC = YesPlease
	INCLUDES_L += -I$(CONTRIB)/DirectX/include
	EXTRA_LIBS += -lmingw32 -lgdi32 -lwinmm $(CONTRIB)/install/lib/libSDLmain.a -lopengl32 -lglu32 -ldxguid -mwindows
	BUILD_FREETYPE = YesPlease
	BUILD_FTGL = YesPlease
	BUILD_SDL = YesPlease
	BUILD_SDLMIXER = YesPlease
	BUILD_SDLIMAGE = YesPlease
else
	EXTRA_LIBS += -lpthread
	INCLUDES_L += -Ilib/irclib/linux
endif
ifeq ($(uname_S),FreeBSD)
	INCLUDES += -I/usr/local/include
	LIBS += -L/usr/local/lib
endif
ifeq ($(uname_S),Darwin)
	EXTRA_LIBS += -framework AppKit -framework AudioUnit -framework Carbon -framework IOKit -framework OpenGL $(CONTRIB)/install/lib/libSDLmain.a
	ifndef NO_APPLE_GCC
		APPLE_GCC = YesPlease
	endif
	BUILD_FREETYPE = YesPlease
	BUILD_FTGL = YesPlease
	BUILD_SDL = YesPlease
	BUILD_SDLMIXER = YesPlease
	BUILD_SDLIMAGE = YesPlease
endif
ifdef USE_LUAJIT
	BUILD_LUA := YesPlease
endif
ifdef USE_ICC
	NO_RDYNAMIC := YesPlease
endif
ifneq (,$(findstring CYGWIN,$(uname_S)))
	GAME = Cerberus.exe
	NO_RDYNAMIC = YesPlease
	BUILD_FREETYPE = YesPlease
	BUILD_FTGL = YesPlease
	BUILD_SDL = YesPlease
	BUILD_SDLMIXER = YesPlease
	BUILD_SDLIMAGE = YesPlease
endif

BUILD_CRISSCROSS = YesPlease
BUILD_FREETYPE = YesPlease
BUILD_FTGL = YesPlease
BUILD_GLEW = YesPlease
BUILD_UNRAR = YesPlease

ifdef BUILD_ALL
	BUILD_LUA = YesPlease
	BUILD_FREETYPE = YesPlease
	BUILD_FTGL = YesPlease
	BUILD_SDL = YesPlease
	BUILD_SDLIMAGE = YesPlease
	BUILD_SDLMIXER = YesPlease
	BUILD_SMPEG = YesPlease
	BUILD_TOLUAPP = YesPlease
	BUILD_LIBPNG = YesPlease
	BUILD_ZLIB = YesPlease
endif

#
# Set up object file dependencies for $(GAME) target.
#
include makefile.obj

# To get stack trace symbols.
# Note that MinGW doesn't support -rdynamic.
ifndef NO_RDYNAMIC
LDFLAGS := -rdynamic
endif
ifdef NEED_STATIC
LDFLAGS += -static
endif

ifdef USE_MERGE_BASE
MERGE_BASE := $(shell git merge-base HEAD $(USE_MERGE_BASE))
endif

# Permissions to set on the game executable.
MCHMOD := 2755

# Permissions to set on the save directory.
MCHMOD_SAVEDIR := 775

# The user:group to install the game as.
INSTALL_UGRP := games:games

chroot_prefix :=
prefix        :=

ifeq ($(patsubst %/local,%,$(patsubst %/,%,$(prefix))),/usr)
FHS := yes
endif

ifeq (,$(bin_prefix))
ifneq ($(patsubst %/,%,$(prefix)),/usr)
bin_prefix    := bin
else
bin_prefix    := games
endif
endif

INCLUDES_L += -I$(CONTRIB)/install/include
LIBS += -L$(CONTRIB)/install/lib

INCLUDES_L += -Iutil -I.

ifdef APPLE_GCC

ARCH := $(shell arch)

ifeq ($(ARCH),ppc)
    SDK_VER := 10.4
endif
ifeq ($(ARCH),i386)
    SDK_VER := 10.4
endif
ifeq ($(ARCH),x86_64)
    SDK_VER := 10.6
endif

# Mac OS X 10.4 adds a 'u' on the end of the SDK name. Everything
# else is much easier to predict the name of.
ifeq ($(SDK_VER),10.4)
GCC_VER := 4.0
SDKROOT := /Developer/SDKs/MacOSX$(SDK_VER)u.sdk
else
GCC_VER := 4.2
SDKROOT := /Developer/SDKs/MacOSX$(SDK_VER).sdk
endif

CC = $(GCC) -arch $(ARCH) -isysroot $(SDKROOT) -mmacosx-version-min=$(SDK_VER)
CXX = $(GXX) -arch $(ARCH) -isysroot $(SDKROOT) -mmacosx-version-min=$(SDK_VER)

ifdef USE_ICC
CC += -gcc-name=gcc-$(GCC_VER) -gxx-name=g++-$(GCC_VER)
CXX += -gcc-name=gcc-$(GCC_VER) -gxx-name=g++-$(GCC_VER)
endif

endif # MacOS

ifndef CROSSHOST

ifneq ($(GCC_VER),)
# We do this in a separate variable because if we
# specify GCC_VER on the make command-line, the
# variable is immutable, and we can't add the dash.
GCC_VER_SUFFIX:=-$(GCC_VER)
endif

# Attempt to use a full compiler name, to make
# distcc builds work nicely.
LMACH := $(shell gcc -dumpmachine)-
ifeq ($(LMACH),-)
LMACH :=
endif
ifeq ($(shell which $(LMACH)gcc$(GCC_VER_SUFFIX) 2> /dev/null),)
LMACH :=
endif

GCC := $(LMACH)gcc$(GCC_VER_SUFFIX)
GXX := $(LMACH)g++$(GCC_VER_SUFFIX)

else

# Cross-compiling is a weird case.
GCC := $(CROSSHOST)-gcc
GXX := $(CROSSHOST)-g++
AR := $(CROSSHOST)-ar
RANLIB := $(CROSSHOST)-ranlib
STRIP := $(CROSSHOST)-strip
WINDRES := $(CROSSHOST)-windres

endif
GCC_GTE_4_0_0 := $(shell ../scripts/gcc-gte.pl $(GCC) 4.0.0)
GCC_GTE_4_3_0 := $(shell ../scripts/gcc-gte.pl $(GCC) 4.3.0)

# Define this to automatically generate code optimized for your machine
# (GCC only as of now).
#
# NOTE: Don't use this with a release build, since the generated code
# won't work for all machines.
ifdef HURRY
NO_AUTO_OPT = YesPlease
endif

ifdef AUTO_OPT
ifndef NO_AUTO_OPT
CFOPTIMIZE += $(shell util/gcc-opt.pl $(GCC))
endif
endif

ifndef BUILD_LUA
  ifneq (,$(wildcard /usr/include/lua5.1))
    INCLUDES_L += -I/usr/include/lua5.1
    LIBS += -llua5.1
  else
    ifneq (,$(wildcard /usr/include/lua.h))
      LIBS += -llua
    else
      BUILD_LUA = yes
    endif
  endif
endif

ifdef BUILD_SDL
INCLUDES_L += -I$(CONTRIB)/install/include/SDL
endif

ifdef BUILD_FREETYPE
INCLUDES_L += -I$(CONTRIB)/install/include/freetype2
endif

# Okay, we have to assume we're on something else that
# uses standard UNIX-like methods for finding libs.
#
# For instance, on Linux and most other UNIX-likes,
# the app pkg-config can provide the appropriate
# CFLAGS and LDFLAGS.
#

ifneq ($(uname_S),Darwin)
ifeq (,$(findstring MINGW,$(uname_S)))
LIBS += -lGL -lGLU
endif
endif

DEFINES_L += $(PNG_CFLAGS) $(FREETYPE_CFLAGS) $(SDL_CFLAGS)
INCLUDES_L += $(PNG_INCLUDE) $(FREETYPE_INCLUDE) $(SDL_INCLUDE)

ifeq ($(GCC_GTE_4_3_0),1)
CFWARN_L += -Wno-array-bounds
endif

# TODO: Add -Wshadow and fix the warnings that show up.
CFWARN_L += -Wno-parentheses -Wwrite-strings -pedantic -D_FORTIFY_SOURCE=0
CFOTHERS_L = $(EXTERNAL_FLAGS_L) $(EXTRA_FLAGS) $(DEFINES) $(SDL_CFLAGS)

#
# Figure out the build settings for this type of build
#
ifdef HURRY
	NO_OPTIMIZE=YesPlease
endif
ifdef DEBUG
CFOTHERS := -ggdb $(CFOTHERS)
endif
ifndef FULLGAME
DEFINES_L += -DTESTGAME=1
else
DEFINES_L += -DFULLGAME=1
endif
ifdef NO_OPTIMIZE
CFOPTIMIZE  := -O0
endif
ifdef PCH
CFWARN_L += -Winvalid-pch
endif

# Cygwin has a panic attack if we do this...
ifndef NO_OPTIMIZE
ifneq ($(GCC_GTE_4_0_0),0)
CFWARN_L += -Wuninitialized
else
CFWARN_L += -Wno-uninitialized
endif
endif

ifdef USE_ICC
NO_INLINE_DEPGEN := YesPlease
GCC := icc
GXX := icpc
AR  := xiar
RANLIB := true
LIBS += -lguide -lpthread
CFWARN := -wd383,810,869,981,1418 -we14,193,304
CFWARN_L :=
LDFLAGS += $(CFOPTIMIZE) $(CFOPTIMIZE_L)
endif

ifdef REPORT
CFOTHERS += -ftime-report
endif

CFLAGS   := $(CFOPTIMIZE) $(DEFINES) $(CFWARN) $(INCLUDES) $(CFOTHERS)
CFLAGS_L := $(CFOPTIMIZE_L) $(DEFINES_L) $(CFWARN_L) $(INCLUDES_L) $(CFOTHERS_L)
ALL_CFLAGS := $(CFLAGS) $(CFLAGS_L)

ifneq ($(findstring $(MAKEFLAGS),s),s)
ifndef V
        QUIET_CC       = @echo '   ' CC $@;
        QUIET_CXX      = @echo '   ' CXX $@;
        QUIET_PCH      = @echo '   ' PCH $@;
        QUIET_LINK     = @echo '   ' LINK $@;
        QUIET_GEN      = @echo '   ' GEN $@;
        QUIET_COPY     = @echo '   ' COPY $@;
        QUIET_DEPEND   = @echo '   ' DEPEND $@;
        QUIET_WINDRES  = @echo '   ' WINDRES $@;
        export V
endif
endif

ifdef BUILD_CRISSCROSS
CONTRIBS += crisscross/source
CONTRIB_LIBS += $(LIBCRISSCROSS)
endif
ifdef BUILD_FTGL
CONTRIBS += FTGL
CONTRIB_LIBS += $(LIBFTGL)
endif
ifdef BUILD_FREETYPE
CONTRIBS += freetype
CONTRIB_LIBS += $(LIBFREETYPE)
endif
ifdef BUILD_GLEW
CONTRIBS += glew
CONTRIB_LIBS += $(LIBGLEW)
else
EXTRA_LIBS += -lglew
endif
ifdef BUILD_SDLIMAGE
CONTRIBS += SDL_image
CONTRIB_LIBS += $(LIBSDLIMAGE)
else
EXTRA_LIBS += -lSDL_image
endif
ifdef BUILD_SDLMIXER
CONTRIBS += SDL_mixer
CONTRIB_LIBS += $(LIBSDLMIXER)
else
EXTRA_LIBS += -lSDL_mixer
endif
ifdef BUILD_SMPEG
CONTRIBS += smpeg
CONTRIB_LIBS += $(LIBSMPEG)
else
EXTRA_LIBS += -lsmpeg
endif
ifdef BUILD_SDL
CONTRIBS += SDL
CONTRIB_LIBS += $(LIBSDL)
else
EXTRA_LIBS += -lSDL
endif
ifdef BUILD_LIBPNG
CONTRIBS += libpng
CONTRIB_LIBS += $(LIBPNG)
else
EXTRA_LIBS += -lpng
endif
ifdef BUILD_LUA
ifdef USE_LUAJIT
CONTRIBS += luajit/src
CFOTHER_L += -DUSE_LUAJIT
else
CONTRIBS += lua/src
endif
CONTRIB_LIBS += $(LIBLUA)
endif
ifdef BUILD_TOLUAPP
CONTRIBS += toluapp
CONTRIB_LIBS += $(LIBTOLUAPP)
else
EXTRA_LIBS += -ltolua++
endif
ifdef BUILD_ZLIB
CONTRIBS += zlib
CONTRIB_LIBS += $(LIBZ)
else
EXTRA_LIBS += -lz
endif
ifdef BUILD_UNRAR
CONTRIBS += unrar
CONTRIB_LIBS += $(LIBUNRAR)
endif

ifdef PROFILE
EXTRA_LIBS += -L/opt/perftools/lib -ltcmalloc
endif

-include Scripting/LuaBindings/makefile.obj

EXTRA_OBJECTS += App/version.o

LIBS += $(CONTRIB_LIBS) $(EXTRA_LIBS)

CONTRIB_DIR = ../../contrib

GAME_DEPENDS := $(OBJECTS) $(EXTRA_OBJECTS) $(CONTRIB_LIBS)

VERSION := $(git describe)

PCH_FILE := stdafx.h

BINDIR := ../bin

all: $(BINDIR)/$(GAME)

build_number.h:
	@../scripts/gen_ver.pl build_number.h

.PHONY: build_number.h

$(PCH_FILE).gch:
	@echo Precompiling $(PCH_FILE)...
	@$(CXX) $(ALL_CFLAGS) $(PCH_FILE) -o $(PCH_FILE).gch

App/version.cpp: build_number.h

pretty:
	@echo -n "Standardizing line endings... "
	-@find . -type f -name '*.cpp' -exec dos2unix {} \; &> /dev/null
	-@find . -type f -name '*.h' -exec dos2unix {} \; &> /dev/null
	@echo "done."
	@echo -n "Sedifying... "
	-@find . -type f -name '*.cpp' -exec ./sedify.sh {} \;
	-@find . -type f -name '*.h' -exec ./sedify.sh {} \;
	@echo "done."
	@echo -n "Running source code beautifier... "
	-@find . -type f -name '*.cpp' -exec uncrustify --no-backup -c uncrustify.cfg {} \; &> /dev/null
	-@find . -type f -name '*.h' -exec uncrustify --no-backup -c uncrustify.cfg {} \; &> /dev/null
	@echo "done."

$(BINDIR)/$(GAME): $(GAME_DEPENDS)
	$(QUIET_LINK)$(CXX) $(LDFLAGS) $(EXTRA_OBJECTS) $(OBJECTS) -o $(BINDIR)/$(GAME) $(LIBS)

distclean: clean clean-contrib

depend: $(OBJECTS:.o=.d)

clean:
	rm -rf $(OBJECTS) $(OBJECTS:.o=.d) $(PCH_FILE).gch $(BINDIR)/$(GAME) build_number.h .cflags

clean-contrib:
	+$(MAKE) -C $(CONTRIB) clean

ifdef NO_INLINE_DEPGEN
$(OBJECTS): $(OBJECTS:%.o=%.d)
endif

$(OBJECTS:%.o=%.d) App/version.o : | $(CONTRIB_LIBS)
$(OBJECTS:%.o=%.cpp) App/version.cpp: | $(CONTRIB_LIBS)

%.d: %.cpp .cflags $(GENERATED_FILES)
	$(QUIET_DEPEND)$(CXX) -MM $(ALL_CFLAGS) -MT $*.o $< > $*.d

%.o: %.cpp .cflags
ifdef NO_INLINE_DEPGEN
	$(QUIET_CC)$(CC) $(ALL_CFLAGS) -c $< -o $@
else
	$(QUIET_CC)$(CC) $(ALL_CFLAGS) -Wp,-MD,$*.d,-MT,$@ -c $< -o $@
endif

%.o: %.cpp .cflags
ifdef NO_INLINE_DEPGEN
	$(QUIET_CXX)$(CXX) $(ALL_CFLAGS) -c $< -o $@
else
	$(QUIET_CXX)$(CXX) $(ALL_CFLAGS) -Wp,-MD,$*.d,-MT,$@ -c $< -o $@
endif

#
# Contribs
#

$(CONTRIB_LIBS): .contrib-libs
	@:

.contrib-libs: .cflags
ifneq (,$(CONTRIBS))
	  +@$(MAKE) -C $(CONTRIB) $(CONTRIBS)
endif

$(foreach t,$(CONTRIB_LIBS),$(if $(wildcard $t),,$(shell rm -f .contrib-libs)))

.PHONY: .contrib-libs

ifeq (,$(findstring clean,$(MAKECMDGOALS)))

#
# CFLAGS difference check
#
# Check for flag changes between the previous build and the current one,
# because any CFLAGS change could result in an inconsistent build if the
# person building it isn't careful.
#
# This should eliminate an annoying need to use 'make clean' every time.
#

TRACK_CFLAGS = $(subst ','\'',$(CC) $(CXX) $(ALL_CFLAGS))           # (stray ' for highlights)

.cflags: .force-cflags
	@FLAGS='$(TRACK_CFLAGS)'; \
	if test x"$$FLAGS" != x"`cat .cflags 2>/dev/null`" ; then \
		echo "    * rebuilding cerberus: new build flags or prefix"; \
		echo "$$FLAGS" > .cflags; \
	fi

.PHONY: .force-cflags

##########################################################################
# Dependencies

DEPS := $(shell ls $(OBJECTS:.o=.d) 2> /dev/null)

ifneq ($(DEPS),)
-include $(DEPS)
endif

endif

