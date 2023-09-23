CC=${CC:-i686-w64-mingw32-g++}
CDEFS=${CDEFS:--DWIN32 -D_WINDOWS -D_USRDLL}
CFLAGS=${CFLAGS:--Wall -Wextra -pedantic -Os -g0 -Wl,--strip-all,--kill-at}

set -xe

# Dependency
if [ ! -f 'atsplugin.h' ]; then
	wget 'https://bvets.net/jp/edit/formats/vehicle/atsplugin.h'
fi

$CC $CFLAGS $CDEFS -shared ats.c -o ats_c.dll
$CC $CFLAGS $CDEFS -shared ats.cpp -o ats.dll
