libconsole.a:console.o
	ar cr libconsole.a console.o
console.o:console.cpp console.h os.h
	g++ -c console.cpp -Wall -g
linux:
	cp os_linux.h os.h
	g++ -c console.cpp -O3
	ar cr libconsole.a console.o
windows:windows_msvc
windows_msvc:
	copy os_win.h os.h
	cl /c console.cpp
	lib console.obj console.lib
windows_mingw:
	copy os_win.h os.h
	g++ -c console.cpp -O3
	ar cr libconsole.a console.o