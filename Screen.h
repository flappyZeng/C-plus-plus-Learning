#ifndef SCREEN_H
#define SCREEN_H
#include<string>
#include<vector>


class Window_mgr;
class Screen
{
public:
	friend  class Window_mgr;
	typedef std::string::size_type  pos;
	Screen() = default;
	Screen(pos ht, pos wd) :height(ht), width(wd), contents(ht* wd, ' '), access_ctr(0) {}
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht* wd, c), access_ctr(0) {}
	const Screen& display(std::ostream& op) const;
	Screen& display(std::ostream& op);
	char get() const { return contents[cursor]; }  //隐式内联函数
	inline char get(pos ht, pos wd) const;  //显式内联函数
	inline Screen& set(char c)
	{
		contents[cursor] = c;
		return *this;
	}
	inline Screen& set(pos ht, pos wd, char c)
	{
		contents[ht * width + wd] = c;
		return *this;
	}
	Screen& move(pos r, pos c);
	void some_member() const;
	pos size() const;

private:
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
	mutable size_t access_ctr = 0;    //可变类型，即使对象是const类型也能被修改
	void do_display(std::ostream& op) const { op << contents; }

};

class Window_mgr
{
public:
	using ScreenIndex = std::vector<Screen>::size_type;
	void clear(ScreenIndex i);
	ScreenIndex addScreen(const Screen& s);

private:
	std::vector<Screen>screens{ Screen(24, 80, ' ') };
};



#endif // !SCREEN_H