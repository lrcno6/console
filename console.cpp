#include"console.h"
using namespace std;
#ifndef WIN_OS
bool Console::Color::m_started=false;
short Console::Color::m_next_id=1;
#endif