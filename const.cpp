#include"Base.h"

int func_const()
{
	//顶层const
	//顶层const表示指针本身是一个常量
	//底层const表示指针所指的对象是一个常量

	
	int i = 0;
	int* const p1 = &i; // 这是一个顶层const;
	const int c2 = 42; // 这也是一个顶层const;
	const int *p2 = &c2; //这个指针p2是可以被改变的，例如 p2 = &c1,说明不是顶层const
	const int* const p3 = p2; // 前者是底层const，后者是顶层const


	//int* p = p3;//这个是报错的，前者是底层const ,后者是顶层const
	const int* const p4 = p2; //前者是顶层const，后者是底层const，这个是可行的


	/*
		顶层const 表示任意的对象是常量，而于数据类型无关
		底层const则与指针以及引用复合类型的基本类型部分有关（指针既可以是底层const也可以是顶层const)
	*/
	const int* ps = &i;  //底层const
	int* const pt = &i; // 顶层const

	return 0;
}
