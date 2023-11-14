call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
clang-cl -c hotfuzz-module.cpp -o hotfuzz-module.o /MT
link -dll hotfuzz-module.o
