#include "Screen.h"

Screen::Action Screen::Menu[] =
{
	&Screen::back,&Screen::up,&Screen::down,&Screen::forward,&Screen::home
};

Screen & Screen::Move(Direction mc)
{
	// TODO: 在此处插入 return 语句
	return (this->*Menu[mc])();
}
