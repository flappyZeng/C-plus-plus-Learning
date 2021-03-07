#include<iostream>
#include"quote.h"
class Base {
public:
	static void statmem() {
		std::cout << "I am static member!" << std::endl;
	}
private:
	static int statVal;
};

int Base::statVal = 0;


class Derived : public Base {
	void f(const Derived _obj)
	{
		Base::statmem();  //可以访问
		Derived::statmem();  //继承类也可以访问
		_obj.statmem(); //通过Derived对象进行访问
		statmem();   //Derived也可以通过this指针访问，等价于this->statmem();

		// Base::statVal; 无法访问父类的私有静态对象。
	}
};

int main()
{
	Quote qu("abc", 3.00);
	Bulk_quote bq("abc", 3.00, 3, 0.3);
	Bulk_quote_exceed bqe("abc", 3.00, 3, 0.2);
	print_total(std::cout, bqe, 4);
	print_total(std::cout, qu, 4);
	print_total(std::cout, bq, 4);
	//Disc_quote dq; 不允许声明为抽象基类的对象
	return 0;
}



