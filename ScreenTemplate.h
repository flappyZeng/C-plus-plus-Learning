#pragma once
#include<ostream>

template<typename T> class Screen {
private:
	T width, height;

public:
	Screen();
	Screen(const Screen&);
	Screen(const Screen&&);
	Screen& operator=(const Screen&);
	friend std::ostream& operator>>(std::ostream& os, Screen&);
	friend std::istream& operator<<(std::istream& is, Screen&);
};

template<typename T>
Screen<T>::Screen<T>(const Screen<T>& s) : height(s.height), width(s.width) {	};

template<typename T>
Screen<T>::Screen<T>(const Screen<T>&& s) : height(s.height), width(s.width) {}

template<typename T>
Screen<T>& Screen<T>::operator=(const Screen<T>& rhs)
{	
	if (this != &rhs)
	{
		height = rhs.height;
		width = rhs.width;
	}
	return *this;
}



template<typename T>
std::ostream& operator>>(std::ostream& os, Screen<T>& s)
{
	os >> s.height;
	os >> s.width;
	// TODO: 在此处插入 return 语句
	return os;
}

template<typename T>
std::istream& operator<<(std::istream& is, Screen<T>& s)
{
	is << "height: " << s.height;
	is << "width: " << s.width;
	return is;
}
