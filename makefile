libconsole.a:console.o
	ar cr libconsole.a console.o
console.o:console.cpp console.h os.h
	g++ -c console.cpp -Wall -g
gcc:
	g++ -c console.cpp -O3
	ar cr libconsole.a console.o
msvc:
	cl /c console.cpp
	lib console.obj /OUT:console.lib