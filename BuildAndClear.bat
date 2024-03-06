@echo off

rem Получаем путь к текущему бат-файлу
set "ScriptPath=%~dp0"

rem Устанавливаем имя директории для сборки
set "BuildPath=%ScriptPath%Build"

rmdir /s /q %BuildPath%

rem Создаем директорию для сборки
mkdir %BuildPath%

del /q %ScriptPath%\cppCGAL\cppCGAL.dll

rem msbuild %ScriptPath%\cppCGAL\cppCGAL.vcxproj /p:Configuration=Debug /p:Platform=x64 /p:OutDir=%BuildPath%\
msbuild %ScriptPath%\cppCGAL\cppCGAL.vcxproj /p:Configuration=Release /p:Platform=x64 /p:OutDir=%BuildPath%\

del /q %BuildPath%\cppCGAL.exp
del /q %BuildPath%\cppCGAL.lib
del /q %ScriptPath%\cppCGAL\cppCGAL.vcxproj.user
rmdir /s /q %ScriptPath%\cppCGAL\cppCGAL
rmdir /s /q %ScriptPath%\cppCGAL\Build

rem Сборка проекта из подпапки \netCGAL\
dotnet publish -c Debug -r win-x64 --self-contained false -o %BuildPath%\ /p:TargetFramework=net8.0 %ScriptPath%netCGAL\netCGAL.csproj
rem copy %BuildPath%\netCGAL.dll %ScriptPath%\netCGAL\

rem Удаление папок bin и obj
rmdir /s /q %ScriptPath%\netCGAL\bin
rmdir /s /q %ScriptPath%\netCGAL\obj



rem Сборка проекта из подпапки \consCGAL\
dotnet publish -c Debug -r win-x64 --self-contained false /p:PublishSingleFile=true -o %BuildPath%\ /p:TargetFramework=net8.0 %ScriptPath%consCGAL\consCGAL.csproj
rem copy %BuildPath%\consCGAL.exe %ScriptPath%\consCGAL\

rem Удаление папок bin и obj
rmdir /s /q %ScriptPath%\consCGAL\bin
rmdir /s /q %ScriptPath%\consCGAL\obj


rem Удаление файлов consCGAL.pdb и netCGAL.pdb
del /q %BuildPath%\consCGAL.pdb
del /q %BuildPath%\netCGAL.pdb
del /q %BuildPath%\netCGAL.deps.json
rmdir /s /q %BuildPath%\Debug

rmdir /s /q %ScriptPath%x64

for /l %%i in (1,1,3) do (
    echo.
)

echo [32mCompilation Done![0m

start /d %BuildPath% consCGAL.exe

pause
