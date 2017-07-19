@ECHO OFF
REM (C) 2017 
REM Help VS build version.
REM kongfl888(kongfl888@outlook.com) in 2017.
REM See the folder 'docs' for more information.
SET "GIT=C:\Program Files\Git"

set "WORKDIR=%~dp0"
set "gitver_file=%WORKDIR%version_r.h"

PUSHD "%~dp0"

IF EXIST "build.user.bat" CALL "build.user.bat"

IF NOT EXIST "%GIT%"    GOTO MissingVar

set "gitexe=%GIT%\bin\git.exe"

for /f "tokens=1,2,3 delims=-" %%a in ('"%gitexe%" describe --tags') do ( set "MainVer=%%a" && set "GitBuildVer=%%b" && set "gitHash=%%c" )
echo Main Version: %MainVer%
echo Build Version: %GitBuildVer%
echo Hash: %gitHash%

echo %GitBuildVer%|findstr /be "[0-9]*" >nul && GOTO ChangVer || GOTO MissingVar 
REM echo %MainVer%|findstr /be "[0-9.]*" >nul && GOTO ChangVer || GOTO MissingVar 

:ChangVer
echo.#define Rversion ^"%GitBuildVer%^" > %gitver_file%

:END
POPD

EXIT /B 0


:MissingVar
echo.#define Rversion ^"1^" > %gitver_file%
POPD
EXIT /B 0