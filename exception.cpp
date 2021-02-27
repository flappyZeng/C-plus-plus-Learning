#include"Base.h"
#include<stdexcept>

using std::endl;
using std::cin;
using std::cout;

void fun_exception()
{
	double x, y;
	while (cin >> x >> y)
	{
		try
		{
			if (y != 0)
				cout << "answer is : " << x / y << endl;
			else
				throw std::runtime_error("the divided number shouldn't be zero!");
		}
		catch (const std::runtime_error& err)
		{
			cout << err.what() << endl;
			cout << "try again£º" << endl;
		}
	}
}

int mainexception()
{
	fun_exception();
	return 0;
}