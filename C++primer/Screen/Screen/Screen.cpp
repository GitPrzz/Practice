#include "Screen.h"

Screen::Action Screen::Menu[] =
{
	&Screen::back,&Screen::up,&Screen::down,&Screen::forward,&Screen::home
};

Screen & Screen::Move(Direction mc)
{
	// TODO: �ڴ˴����� return ���
	return (this->*Menu[mc])();
}
