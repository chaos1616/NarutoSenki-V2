cd tools\tolua++
./build

cd ../../
./build-win32

rm -rf __BIN__/lua
 cp projects/NarutoSenki/lua/* __BIN__/lua/
