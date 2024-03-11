@echo off

rem Получаем путь к текущему бат-файлу
set "ScriptPath=%~dp0"

rem Устанавливаем имя директории для сборки
set "BuildPath=%ScriptPath%Build"

rem rmdir /s /q %BuildPath%

rem Создаем директорию для сборки
mkdir %BuildPath%

del /q %ScriptPath%\cppCGAL\cppCGAL.dll

rem msbuild %ScriptPath%\cppCGAL\cppCGAL.vcxproj /p:Configuration=Debug /p:Platform=x64 /p:OutDir=%BuildPath%\

rem ***************
rem msbuild %ScriptPath%\cppCGAL\cppCGAL.vcxproj /p:Configuration=Release /p:Platform=x64 /p:OutDir=%BuildPath%\
rem ***************

del /q %BuildPath%\cppCGAL.exp
del /q %BuildPath%\cppCGAL.lib
del /q %ScriptPath%\cppCGAL\cppCGAL.vcxproj.user
rmdir /s /q %ScriptPath%\cppCGAL\cppCGAL
rmdir /s /q %ScriptPath%\cppCGAL\Build

rem Сборка проекта из подпапки \netCGAL\
rem dotnet publish -c Release -r win-x64 --self-contained false -o %BuildPath%\ /p:TargetFramework=net8.0 %ScriptPath%netCGAL\netCGAL.csproj
rem copy %BuildPath%\netCGAL.dll %ScriptPath%\netCGAL\

rem Удаление папок bin и obj
rmdir /s /q %ScriptPath%\netCGAL\bin
rmdir /s /q %ScriptPath%\netCGAL\obj



rem Сборка проекта из подпапки \consCGAL\
rem dotnet publish -c Release -r win-x64 --self-contained false /p:PublishSingleFile=true -o %BuildPath%\ /p:TargetFramework=net8.0 %ScriptPath%appCGAL\appCGAL.csproj
rem dotnet publish -c Release -r win-x64 -p:PublishSingleFile=true --self-contained false -o %BuildPath%\ /p:TargetFramework=net8.0 %ScriptPath%appCGAL\appCGAL.csproj
dotnet publish -c Release -r win-x64 -p:PublishSingleFile=true --self-contained false -o %BuildPath%\ /p:TargetFramework=net8.0 %ScriptPath%appCGAL\appCGAL.csproj
rem dotnet build -c Release -r win-x64 -p:PublishSingleFile=true --self-contained false -o %BuildPath%\ /p:TargetFramework=net8.0 %ScriptPath%appCGAL\appCGAL.csproj
rem copy %BuildPath%\consCGAL.exe %ScriptPath%\consCGAL\

rem Удаление папок bin и obj
rmdir /s /q %ScriptPath%\appCGAL\bin
rmdir /s /q %ScriptPath%\appCGAL\obj


rem Удаление файлов consCGAL.pdb и netCGAL.pdb
del /q %BuildPath%\appCGAL.pdb
del /q %BuildPath%\netCGAL.pdb
del /q %BuildPath%\netCGAL.deps.json
rmdir /s /q %BuildPath%\Debug

rmdir /s /q %ScriptPath%x64

for /l %%i in (1,1,3) do (
    echo.
)

echo [32mCompilation Done![0m

start /d %BuildPath% appCGAL.exe

pause
