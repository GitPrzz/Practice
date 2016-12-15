#pragma once

#include <string>

class Screen {
public:
	using pos = std::string::size_type;
	Screen() = default;
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht*wd, c) { }

	char get() const { return contents[cursor]; }
	std::string get_all() const { return contents; }
	char get(pos r, pos c) const { return contents[r*width + c]; }
	static const std::string Screen::*data()
	{
		return &Screen::contents;
	}
	using Action = char(Screen::*)(Screen::pos, Screen::pos) const;
	Screen &action(Screen &t, Action = &Screen::get);
	Screen& home();
	Screen& forward();
	Screen& up();
	Screen& down();
	Screen& back();
	enum Direction {BACK,UP,DOWN,FORWARD,HOME};
	Screen &Move(Direction);
private:
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
	static Action Menu[];
};
