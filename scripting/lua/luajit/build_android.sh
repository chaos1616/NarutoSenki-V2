#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
host_os=`uname -s | tr "[:upper:]" "[:lower:]"`

SRCDIR=$DIR/LuaJIT
cd "$SRCDIR"

# NOTE: You should setup NDK_ROOT path first
NDKDIR=$NDK_ROOT
NDKBIN=${NDKDIR}toolchains/llvm/prebuilt/linux-x86_64/bin
NDKABI=21
make clean

# Android/ARM64, aarch64
DESTDIR=$DIR/android/arm64-v8a
NDKCROSS=$NDKBIN/aarch64-linux-android-
NDKCC=$NDKBIN/aarch64-linux-android${NDKABI}-clang
make -j HOST_CC="clang -m64" CROSS=$NDKCROSS \
     STATIC_CC=$NDKCC DYNAMIC_CC="$NDKCC -fPIC" \
     TARGET_LD=$NDKCC TARGET_AR="$NDKBIN/llvm-ar rcus" \
     TARGET_STRIP=$NDKBIN/llvm-strip

if [ -f $SRCDIR/src/libluajit.a ]; then
    cp $SRCDIR/src/libluajit.a $DESTDIR/libluajit.a
fi;

make clean

# Android/ARM, armeabi-v7a (ARMv7 VFP)
DESTDIR=$DIR/android/armeabi-v7a
NDKCROSS=$NDKBIN/arm-linux-androideabi-
NDKCC=$NDKBIN/armv7a-linux-androideabi${NDKABI}-clang
make -j HOST_CC="clang -m32" CROSS=$NDKCROSS \
     STATIC_CC=$NDKCC DYNAMIC_CC="$NDKCC -fPIC" \
     TARGET_LD=$NDKCC TARGET_AR="$NDKBIN/llvm-ar rcus" \
     TARGET_STRIP=$NDKBIN/llvm-strip

if [ -f $SRCDIR/src/libluajit.a ]; then
    cp $SRCDIR/src/libluajit.a $DESTDIR/libluajit.a
fi;
