#ifndef _CONSOLE_H_
#define _CONSOLE_H_
#include<cstdlib>
#define WIN_OS
#ifdef WIN_OS
#include<cstdio>
#include<windows.h>
#include<conio.h>
#else
#include<curses.h>
#endif
class Console{
	public:
		static void cursor_set(bool visible){
			#ifdef WIN_OS
			HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_CURSOR_INFO cci;
			GetConsoleCursorInfo(hout,&cci);
			cci.bVisible=visible;
			SetConsoleCursorInfo(hout,&cci);
			#else
			curs_set(visible);
			#endif
		}
		static bool echo(bool e=true){
			#ifdef WIN_OS
			return false;
			#else
			if(e)
				::echo();
			else
				noecho();
			return true;
			#endif
		}
		static void move(int x,int y){
			#ifdef WIN_OS
			HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(hout,{(short)y,(short)x});
			#else
			::move(x,y);
			#endif
		}
		template<typename... Args>
		static void print(const char *str,Args... args){
			#ifdef WIN_OS
			printf(str,args...);
			#else
			printw(str,args...);
			#endif
		}
		template<typename... Args>
		static void mvprint(int x,int y,const char *str,Args... args){
			#ifdef WIN_OS
			move(x,y);
			printf(str,args...);
			#else
			mvprintw(x,y,str,args...);
			#endif
		}
		static void clear(){
			system(
				#ifdef WIN_OS
				"cls"
				#else
				"clear"
				#endif
			);
		}
		static void sleep(unsigned ms){
			#ifdef WIN_OS
			Sleep(ms);
			#else
			usleep(ms*1000);
			#endif
		}
		static void pause(int x,int y){
			#ifdef WIN_OS
			move(x,y);
			system("pause");
			#else
			mvprint(x,y,"Press any key to continue...");
			getch();
			#endif
		}
		Console(){
			#ifndef WIN_OS
			initscr();
			#endif
		}
		~Console(){
			#ifndef WIN_OS
			endwin();
			#endif
		}
};
#endif
