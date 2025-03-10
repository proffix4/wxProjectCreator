# Project Configuration (for 64-bit Debug)

## General Settings
- **Type**: Win32 Console  
- **Default Encoding**: UTF-8  

## Compiler Set
- **Base Compiler Set**: MinGW-w64 GCC 11.4.0 64-bit Debug  
- **Set Encoding for the Executable**: ✅ UTF-8  

## Custom Compile Options

### C++ Compiler
```sh
-pipe -mthreads -D__GNUWIN32__ -D__WXMSW__ -DwxUSE_UNICODE -Wall -g -O0 
```

### Linker
#### Для консольной wx-программы:
```sh
-mthreads 
-lwxmsw32ud_core -lwxbase32ud -lwxpngd -lwxjpegd -lwxtiffd -lwxzlibd 
-lwxregexud -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 
-lshell32 -lole32 -loleaut32 -luuid -lcomctl32 -lwsock32 -lodbc32 -lshlwapi 
-lversion -loleacc -luxtheme -lstdc++ -finput-charset=utf-8 -lsqlite3 -static
```

#### Для оконной wx-программы:
```sh
-mthreads 
-lwxmsw32ud_core -lwxbase32ud -lwxpngd -lwxjpegd -lwxtiffd -lwxzlibd 
-lwxregexud -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 
-lshell32 -lole32 -loleaut32 -luuid -lcomctl32 -lwsock32 -lodbc32 -lshlwapi 
-lversion -loleacc -luxtheme -lstdc++ -finput-charset=utf-8 -lsqlite3 -mwindows -static
```

## Directories

### Libraries
```sh
D:/Development/RedPanda-CPP/wxWidgets/lib/gcc_lib
```

### Includes
```sh
D:/Development/RedPanda-CPP/wxWidgets/include
D:/Development/RedPanda-CPP/wxWidgets/lib/gcc_lib/mswud
```
