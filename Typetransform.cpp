#include"Base.h"

using std::cin;
using std::cout;
using std::endl;

void func_type_trans()
{
	unsigned char a = 0;
	a = 178;
	cout <<"a: "<<  a << endl;
}

void explicit_trans()
{
	int i = 0, j = 1;
	double d = 0.0;
	//static_cast: 任意具备明确定义的类型转换，只要不包含顶层const,可以将大类型安全的转化为小类型
	double slope = static_cast<double>(i) / j;  //调用static_cast将i转换为double
	void* p = &d;
	double* dp = static_cast<double*>(p);   //将void* --> double*

	//dynamic_cast： 运行时进行类型识别

	//const_cast: const_cast只能改变运算对象底层的const，只能去掉const，不能完成类型转换
	char c = 'a';
	const char* pc = &c;
	char* pcc = const_cast<char*>(pc);  //可以转换，但是如何对象是一个常量，对pcc进行写值的行为是未定义

	char ch = 'a';
	const int in = 10;

	const int* pin = &in; //不能通过pin修改in；
	const char* pch = &ch;  //不能通过pch修改ch；

	int* pincc = const_cast<int*>(pin);
	*pincc = 20;  //未定义行为

	char* pchcc = const_cast<char*>(pch);  //可以通过pchcc修改ch的值；
	*pchcc = 'd'; //可行；


	//reinterpret_cast:对指针的类型进行重新解释（较低层次) 最危险的转换；
	int* ip = &i;
	char* pcs = reinterpret_cast<char*>(ip);  //不建议

}

int maintrans()
{
	func_type_trans();
	return 0;
}