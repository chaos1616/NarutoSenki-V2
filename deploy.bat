@echo off

echo Building NarutoSenki Project ...

call ./build.bat

if not exist ./Build mkdir ./Build

"tools/7z/7z.exe" a Build/NarutoSenki.zip ./projects/NarutoSenki/__BIN__/*
