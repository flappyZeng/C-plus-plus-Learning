#include"Base.h"
#include<cstdarg>
using namespace std;

int sum(int start, ...) //优先级最低
{
	va_list args;
	va_start(args, start);
	int i = start;
	int sumNum = 0;
	while (i != -1)
	{
		sumNum += i;
		i = va_arg(args, int);
	}
	return sumNum;
}

int mainS()
{
	cout <<"ans: " <<  sum(1, 2, 3, 4, 5, 6, 7, -1) << endl;
	return 0;

}