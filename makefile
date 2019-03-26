libconsole.a:console.o
	ar cr libconsole.a console.o
console.o:console.cpp console.h os.h
	g++ -c console.cpp -Wall -g
linux:
	cp os_linux.h os.h
	g++ -c console.cpp -O3
	ar cr libconsole.a console.o
windows_msvc:
	copy os_win.h os.h
	cl /c console.cpp
	lib console.obj /OUT:console.lib
windows_mingw:
	cp os_win.h os.h
	g++ -c console.cpp -O3
	ar cr libconsole.a console.o