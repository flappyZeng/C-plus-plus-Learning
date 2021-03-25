#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include"quote.h"
class Base {
public:
	static void statmem() {
		std::cout << "I am static member!" << std::endl;
	}
	friend class pal;
	void memfcn(Base& b) { b = *this; }  //func

private:
	static int statVal;
public:
	int baseWord;
};

int Base::statVal = 0;

class Derived : private Base {
	void f(const Derived _obj)
	{
		Base::statmem();  //可以访问
		Derived::statmem();  //继承类也可以访问
		_obj.statmem(); //通过Derived对象进行访问
		statmem();   //Derived也可以通过this指针访问，等价于this->statmem();

		// Base::statVal; 无法访问父类的私有静态对象。
	}
private:
	int member;
public:
	using Base::baseWord; //改变成员的访问权限，现在Derived的所有用户都能访问baseWord
};
class pal {
	int f(Base b) { return b.statVal; }
	//int f2(Derived d) { return d.member; } ,不可访问，友元不具有传递性
	int f3(Derived d) { return d.baseWord; } //可以访问；
};

struct Pub_Derv: public Base{
	void memfcn(Base& b) { b = *this; }
};
struct Pro_Derv : protected Base {
	void memfcn(Base& b) { b = *this; }
};
struct Pri_Derv : private Base {
	void memfcn(Base& b) { b = *this; }
};
//以上三个符合，不管以什么方式继承自Base,派生类的成员函数以及友元函数都能完成派生类到基类的类型转换


struct Derived_from_Public : public Pub_Derv {
	void memfcn(Base& b) { b = *this; }
};
struct Derived_from_Private : public Pri_Derv {
	//void memfcn(Base& b) { b = *this; }
};
struct Derived_From_Protected : public Pro_Derv {
	void memfcn(Base& b) { b = *this; }
};
//对于派生类的派生类的成员函数以及友元函数，至于派生类是public或者protected的继承方式才能完成类型转换

class BaseT {
	char data[3];
public:
	virtual void f() { std::cout << "Base::f" << std::endl; }
	virtual void g() { std::cout << "Base::g" << std::endl; }
	virtual void h() { std::cout << "Base::h" << std::endl; }

};
int f()
{
	char c = 'a';
	return true;
}
class BaseE {

};
int maint()
{
	
	/*
	Quote qu("abc", 3.00);
	Bulk_quote bq("abc", 3.00, 3, 0.3);
	Bulk_quote_exceed bqe("abc", 3.00, 3, 0.2);
	print_total(std::cout, bqe, 4);
	print_total(std::cout, qu, 4);
	print_total(std::cout, bq, 4);
	
	Derived D = Derived();
	std::cout << D.baseWord << std::endl; //可以访问，因为using Base::baseWord;
	//Disc_quote dq; 不允许声明为抽象基类的对象
	Pub_Derv d1;
	Pri_Derv d2;
	Pro_Derv d3;
	Derived_from_Public dd1;
	Derived_from_Private dd2;
	Derived_From_Protected dd3;

	Base* p = &d1;  //可行，因为d1是public继承自base
	//Base* p2 = &d2;  不可行，因为d2是private继承自base;
	//Base* p3 = &d3;  不可行，因为d2是protected继承自base;
	Base* p4 = &dd1;  //可行，dd1是public继承自Pub_Derv，而Pub_Derv是public继承自Base;
	//Base* p5 = &dd2; 不可行，d2都不可行，同理
	//Base *p6 = &dd3; 不可行，d3都不可行；

	std::set<int>vc{ 1,2 ,3, 4, 5, 6, 7, 8, 9 };
	std::cout << vc.count(1) << std::endl;
	
	char s1[] = { " abcd " }; 
	int a[3];
	a[0] = 0; a[1] = 1; a[2] = 2;
	int* p, * q;
	p = a;
	q = &a[2];
	//std::cout << a[q - p];
	std::cout << sizeof(BaseT) << std::endl;
	*/
	int k = 2000;
	while (k > 1)
	{
		k = k >> 1;
		std::cout << 2;
	}
	
	int i = 010, j = 10; 
	std::cout << i << j << std::endl;
	printf("%d,%d\n", ++i, j--);
	
	return 0;
}

#include"./Query.h"
int mainQuery()
{
	std::string path = "C:\\Users\\Administrator\\Desktop\\words.txt";
	std::ifstream ifs(path, std::ifstream::in);
	TextQuery text(ifs);
	Query q = Query("is") | Query("are");
	print(std::cout, q.eval(text));
	return 0;
}



