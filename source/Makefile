OUTFILE=bin/ARC

CC=source/ccdv gcc
CXX=source/ccdv g++
# CC=gcc
# CXX=g++
LINK=$(CXX)
LIBS=-Wl,-Bstatic -Lcontrib/crisscross/source -lCrissCross -lSDLmain -Wl,-Bdynamic -lz -lSDL -lSDL_mixer -lSDL_image -lGL -lX11 -rdynamic

CXXFLAGS=-O2 -ggdb -pipe -Wall -Wno-long-long -rdynamic -std=c++98 -pedantic -fno-strict-aliasing -ffast-math
CPPFLAGS=-D_DEBUG

STRIP=:strip
NM=:nm

INCLUDE=-Isource -Icontrib/OpenGL/include -Icontrib/unrar -Icontrib/crisscross/source -I/opt/local/include -I/opt/local/include/SDL

# find . -name '*.cpp' | sed 's%^\./\(.*\)%\1 \\%'

UNRAR_SOURCES = \
contrib/unrar/archive.cpp \
contrib/unrar/arcread.cpp \
contrib/unrar/cmddata.cpp \
contrib/unrar/consio.cpp \
contrib/unrar/crc.cpp \
contrib/unrar/crypt.cpp \
contrib/unrar/encname.cpp \
contrib/unrar/errhnd.cpp \
contrib/unrar/extinfo.cpp \
contrib/unrar/extract.cpp \
contrib/unrar/filcreat.cpp \
contrib/unrar/file.cpp \
contrib/unrar/filefn.cpp \
contrib/unrar/filestr.cpp \
contrib/unrar/find.cpp \
contrib/unrar/getbits.cpp \
contrib/unrar/global.cpp \
contrib/unrar/isnt.cpp \
contrib/unrar/list.cpp \
contrib/unrar/match.cpp \
contrib/unrar/options.cpp \
contrib/unrar/pathfn.cpp \
contrib/unrar/rarvm.cpp \
contrib/unrar/rawread.cpp \
contrib/unrar/rdwrfn.cpp \
contrib/unrar/recvol.cpp \
contrib/unrar/resource.cpp \
contrib/unrar/rijndael.cpp \
contrib/unrar/rs.cpp \
contrib/unrar/savepos.cpp \
contrib/unrar/scantree.cpp \
contrib/unrar/sha1.cpp \
contrib/unrar/smallfn.cpp \
contrib/unrar/strfn.cpp \
contrib/unrar/strlist.cpp \
contrib/unrar/system.cpp \
contrib/unrar/timefn.cpp \
contrib/unrar/ulinks.cpp \
contrib/unrar/unicode.cpp \
contrib/unrar/unpack.cpp \
contrib/unrar/unrar.cpp \
contrib/unrar/volume.cpp

SOURCES = \
source/App/app.cpp \
source/App/binary_stream_readers.cpp \
source/App/databuffer.cpp \
source/App/debug_utils.cpp \
source/App/file_utils.cpp \
source/App/preferences.cpp \
source/App/resource.cpp \
source/App/string_utils.cpp \
source/App/text_stream_readers.cpp \
source/arc.cpp \
source/Game/bounce.cpp \
source/Game/collide.cpp \
source/Game/game.cpp \
source/Game/grenade.cpp \
source/Game/grenade_explosion.cpp \
source/Game/grenade_smoke.cpp \
source/Game/laser.cpp \
source/Game/missile.cpp \
source/Game/missile_smoke.cpp \
source/Game/player.cpp \
source/Game/shrapnel.cpp \
source/Game/spark.cpp \
source/Game/weapon.cpp \
source/Graphics/graphics.cpp \
source/Graphics/graphics_opengl.cpp \
source/Graphics/graphics_sdl.cpp \
source/Graphics/opengl.cpp \
source/Graphics/surface.cpp \
source/Graphics/texture.cpp \
source/Graphics/texture_directx.cpp \
source/Graphics/texture_opengl.cpp \
source/Interface/bouncing_window.cpp \
source/Interface/button.cpp \
source/Interface/chat_overlay.cpp \
source/Interface/error_window.cpp \
source/Interface/inputwidget.cpp \
source/Interface/interface.cpp \
source/Interface/laser_zap.cpp \
source/Interface/loading_window.cpp \
source/Interface/quit_window.cpp \
source/Interface/ship.cpp \
source/Interface/ship_explosion.cpp \
source/Interface/sidebar.cpp \
source/Interface/text.cpp \
source/Interface/text_input.cpp \
source/Interface/widget.cpp \
source/Interface/window.cpp \
source/Network/connection.cpp \
source/Network/net.cpp \
source/Network/net_crisscross.cpp \
source/Network/net_raknet.cpp \
source/Network/packet.cpp \
source/Sound/soundsystem.cpp \
source/Sound/soundsystem_null.cpp \
source/Sound/soundsystem_openal.cpp \
source/Sound/soundsystem_sdlmixer.cpp \
source/universal_include.cpp \
source/World/map.cpp

CXXFLAGS+=$(INCLUDE)

OBJDIR=.linux-objs
OBJECTS=$(SOURCES:%.cpp=$(OBJDIR)/%.o) $(UNRAR_SOURCES:%.cpp=$(OBJDIR).rar/%.o)
PCH_FILE=source/universal_include.h

all: source/ccdv
	$(MAKE) -f source/Makefile all-before
	$(MAKE) -f source/Makefile $(OUTFILE)

all-before: $(PCH_FILE).gch

source/ccdv: source/ccdv.c
	@gcc -O2 -o source/ccdv source/ccdv.c
	@strip source/ccdv

clean:
	rm -f $(OUTFILE)
	rm -f $(PCH_FILE).gch
	rm -f source/ccdv
	rm -rf $(OBJDIR)
	rm -rf $(OBJDIR).rar

$(PCH_FILE).gch: $(PCH_FILE)
	$(shell pwd)/scripts/gen_buildnum_h.sh $(shell pwd)/source/build_number.h
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(PCH_FILE) -o $(PCH_FILE).gch

$(OUTFILE): $(OBJECTS)
	@$(LINK) $+ $(LIBS) -o $@ 

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJDIR).rar/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -w -c $< -o $@

$(OBJDIR).rar/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CXXFLAGS) -w -c $< -o $@

