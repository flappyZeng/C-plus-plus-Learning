#include"Base.h"

struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};


struct Foo { /* something empty*/ };

// 不加上;会导致编译器将Foo识别为函数的返回值， 提示Foo后面接int是非法的
int mainBase()
{
	return 0;
}