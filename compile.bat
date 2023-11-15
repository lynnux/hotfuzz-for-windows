call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
clang-cl /I . -c hotfuzz-module.c -o hotfuzz-module.o /MT
clang-cl /I . -c pthread.cpp -o pthread.o /MT /EHsc
link /def:hotfuzz-module.def -dll hotfuzz-module.o pthread.o /out:hotfuzz-module.dll
