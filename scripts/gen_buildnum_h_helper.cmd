@echo off
set PATH=C:\cygwin\bin;C:\msysgit\bin;C:\msysgit\mingw\bin;%PATH%
cd "%1"
perl.exe "scripts/gen_buildnum_h.pl" "%1/source/build_number.h"
