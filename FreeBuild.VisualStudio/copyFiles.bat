set here=%cd%
cd ../..
set top=%cd%

@echo off
echo Removing dlls...

del %here%\Debug\*.dll
del %here%\Release\*.dll

echo Copying dlls...
goto release
:: duznt work...
copy %top%\rocket\Build\cmake_build\Debug\*_d.dll %here%\Debug\
copy %top%\support\freetype\lib\freetype6.dll %here%\Debug
copy %top%\FreeBuild\FreeBuild.VisualStudio\zlib1.dll %here%\Debug\
copy %top%\support\boost\stage\lib\*-mt-gd-1_53.dll %here%\Debug\
copy %top%\support\python\PCbuild\python27_d.dll %here%\Debug\

:release
copy %top%\rocket\Build\cmake_build\Release\*.dll %here%\Release\
copy %top%\support\freetype\lib\freetype6.dll %here%\Release
copy %top%\FreeBuild\FreeBuild.VisualStudio\zlib1.dll %here%\Release\
copy %top%\support\boost\stage\lib\*-mt-1_53.dll %here%\Release\
copy %top%\support\python\PCbuild\python27.dll %here%\Release\

echo Copying scripts and data...
copy %top%\FreeBuild\FreeBuild\main.py %here%\Release
mkdir %here%\Release\scripts
echo a | xcopy %top%\FreeBuild\FreeBuild\scripts %here%\Release\scripts /e
mkdir %here%\Release\data
echo a | xcopy %top%\FreeBuild\FreeBuild\data %here%\Release\data /e

echo Done!
@echo on

echo Running Release version...
cd %here%
release.bat

pause