@rem https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170
@rem TODO https://docs.microsoft.com/en-us/visualstudio/install/build-tools-container?view=vs-2022
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat"
cl /I.\include /Fe.\m2k.exe *.c