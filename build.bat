rm -R __BIN__/lua
cp projects/NarutoSenki/lua __BIN__/lua

cd tools\tolua++
./build

cd ../../
./build-win32
