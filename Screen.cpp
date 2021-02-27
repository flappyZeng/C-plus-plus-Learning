#include<iostream>
#include"Screen.h"

using std::cin;
using std::cout;
using std::endl;

char Screen::get(pos r, pos c) const
{
	return contents[r * width + c];
}

Screen& Screen::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

void Screen::some_member() const
{
	++access_ctr;       //虽然传入的是const对象，但是还是可以改变access_ctr
}

const Screen& Screen::display(std::ostream& op) const
{
	do_display(op);
	return *this;
}

Screen& Screen::display(std::ostream& op)
{
	do_display(op);
	return *this;
}

Screen::pos Screen::size() const
{
	return height * width;
}

//Window_mgr
void Window_mgr::clear(Window_mgr::ScreenIndex i)
{
	Screen& s = this->screens[i];
	s.contents = std::string(s.height * s.width, ' ');
}

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen& s)
{
	screens.push_back(s);
	return screens.size() - 1;
}
