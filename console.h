#ifndef _CONSOLE_H_
#define _CONSOLE_H_
//#define WIN_OS
#ifdef WIN_OS
#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#else
#include<curses.h>
#include<unistd.h>
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
		static void scan(const char *str,Args... args){
			#ifdef WIN_OS
			scanf(str,args...);
			#else
			scanw(str,args...);
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
		static void mvscan(int x,int y,const char *str,Args... args){
			#ifdef WIN_OS
			move(x,y);
			scanf(str,args...);
			#else
			mvscanw(x,y,str,args...);
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
			#ifdef WIN_OS
				system("cls");
			#else
				::clear();
			#endif
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
