#ifndef _CONSOLE_H_
#define _CONSOLE_H_
#include<cstdlib>
#include"os.h"
#ifdef WIN_OS
#include<cstdio>
#include<windows.h>
#include<conio.h>
#else
#include<system_error>
#include<climits>
#include<curses.h>
#include<unistd.h>
#endif
class Console{
	public:
		class Color{
			public:
				enum color_value{
					#ifdef WIN_OS
					Default=-1,black=0,red=FOREGROUND_RED,green=FOREGROUND_GREEN,yellow=FOREGROUND_RED|FOREGROUND_GREEN,blue=FOREGROUND_BLUE,magenta=FOREGROUND_RED|FOREGROUND_BLUE,cyan=FOREGROUND_GREEN|FOREGROUND_BLUE,white=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE
					#else
					Default=-1,black=COLOR_BLACK,red=COLOR_RED,green=COLOR_GREEN,yellow=COLOR_YELLOW,blue=COLOR_BLUE,magenta=COLOR_MAGENTA,cyan=COLOR_CYAN,white=COLOR_WHITE
					#endif
				};
				static void start_color(){
					#ifndef WIN_OS
					if(!m_started){
						int code=::start_color();
						if(code!=OK)
							throw std::system_error(std::error_code(code,std::generic_category()),"Console::Color::start_color: start color failed");
						use_default_colors();
						m_started=true;
					}
					#endif
				}
				Color(color_value fg,color_value bg)noexcept{
					#ifdef WIN_OS
					m_fg=fg;
					m_bg=bg;
					#else
					start_color();
					m_id=m_next_id++;
					init_pair(m_id,fg,bg);
					#endif
				}
				void Begin()const noexcept{
					#ifdef WIN_OS
					HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
					CONSOLE_SCREEN_BUFFER_INFO info;
					GetConsoleScreenBufferInfo(handle,&info);
					WORD default_color=info.wAttributes;
					color_value fg=m_fg==black?m_fg:(color_value)(m_fg|FOREGROUND_INTENSITY),bg=m_bg==black?m_bg:(color_value)(m_fg|FOREGROUND_INTENSITY);
					SetConsoleTextAttribute(handle,fg|bg<<4);
					#else
					attron(COLOR_PAIR(m_id));
					#endif
				}
				void End()const noexcept{
					#ifndef WIN_OS
					attroff(COLOR_PAIR(m_id));
					#endif
				}
			private:
				#ifdef WIN_OS
				color_value m_fg,m_bg;
				#else
				static bool m_started;
				static short m_next_id;
				short m_id;
				#endif
		};
		static void cursor_set(bool visible)noexcept{
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
		static void echo(bool e=true)noexcept{
			#ifndef WIN_OS
			if(e)
				::echo();
			else
				noecho();
			#endif
		}
		static void move(int x,int y)noexcept{
			#ifdef WIN_OS
			HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(hout,{(short)y,(short)x});
			#else
			::move(x,y);
			#endif
		}
		template<typename... Args>
		static void scan(const char *str,Args... args)noexcept{
			#ifdef WIN_OS
			scanf(str,args...);
			#else
			scanw(str,args...);
			#endif
		}
		template<typename... Args>
		static void print(const char *str,Args... args)noexcept{
			#ifdef WIN_OS
			printf(str,args...);
			#else
			printw(str,args...);
			#endif
		}
		template<typename... Args>
		static void print(const Color &color,const char *str,Args... args)noexcept{
			color.Begin();
			#ifdef WIN_OS
			printf(str,args...);
			#else
			printw(str,args...);
			#endif
			color.End();
		}
		template<typename... Args>
		static void mvscan(int x,int y,const char *str,Args... args)noexcept{
			#ifdef WIN_OS
			move(x,y);
			scanf(str,args...);
			#else
			mvscanw(x,y,str,args...);
			#endif
		}
		template<typename... Args>
		static void mvprint(int x,int y,const char *str,Args... args)noexcept{
			#ifdef WIN_OS
			move(x,y);
			printf(str,args...);
			#else
			mvprintw(x,y,str,args...);
			#endif
		}
		template<typename... Args>
		static void mvprint(int x,int y,const Color &color,const char *str,Args... args)noexcept{
			color.Begin();
			#ifdef WIN_OS
			move(x,y);
			printf(str,args...);
			#else
			mvprintw(x,y,str,args...);
			#endif
			color.End();
		}
		static void flush()noexcept{
			#ifndef WIN_OS
			refresh();
			#endif
		}
		static void clear()noexcept{
			#ifdef WIN_OS
			system("cls");
			#else
			::clear();
			#endif
		}
		static void sleep(unsigned ms)noexcept{
			#ifdef WIN_OS
			Sleep(ms);
			#else
			usleep(ms*1000);
			#endif
		}
		static void pause(int x,int y)noexcept{
			#ifdef WIN_OS
			move(x,y);
			system("pause");
			#else
			mvprint(x,y,"Press any key to continue...");
			getch();
			#endif
		}
		Console()noexcept{
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
