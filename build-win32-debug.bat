@echo off

echo./*
echo. * Check VC++ environment...
echo. */
echo.

set VSTOOLS="%VS142COMNTOOLS%"
set VC_VER=142

set VSTOOLS=%VSTOOLS:"=%
set "VSTOOLS=%VSTOOLS:\=/%"

set VSVARS="%VSTOOLS%vsvars32.bat"

if not defined VSVARS (
    echo Can't find VC2019 installed!
    goto ERROR
)

echo./*
echo. * Building cocos2d-x library binary, please wait a while...
echo. */
echo.

call %VSVARS%

msbuild cocos2d-win32.sln /p:Configuration="Debug" /m

echo./*
echo. * Check the cocos2d-win32 application "NarutoSenki.exe" ...
echo. */
echo.

pushd ".\Debug.win32\"

set CC_BIN=NarutoSenki.exe
set CC_RES=..\projects\NarutoSenki\Resources
set CC_LUA=..\projects\NarutoSenki\lua

echo./*
echo. * Copy resources
echo. *
echo. *************************************************************
echo. * NOTE: Doesn't automatically copy lua files in debug mode. *
echo. *************************************************************
echo. *
echo. */

rm -rf ..\projects\NarutoSenki\__BIN__\Data
mkdir .\Data
xcopy /Y /D /E /Y /Q "%CC_RES%" ..\projects\NarutoSenki\__BIN__\Data
xcopy /E /Y /Q .\*.dll ..\projects\NarutoSenki\__BIN__
xcopy /E /Y /Q .\*.exe ..\projects\NarutoSenki\__BIN__

if not exist "%CC_BIN%" (
    echo Can't find the binary "NarutoSenki.exe", is there build error?
    goto ERROR
)

popd
goto EOF

:ERROR
pause

:EOF
