#include"Base.h"

using std::cin;
using std::endl;
using std::cout;

void caculate()
{
	bool b = true;

	//b1是true的原因b --提升为int--> 1 --> 取负 --> -1 --强制转换为bool --> true
	bool b1 = -b; // 结果也是true, bool值不应该参加运算

	//赋值运算符返回的是其左侧运算对象
	int a, c;
	a = c = 1; //可行
}
int maincal()
{
	std::string s = "word";
	std::string p1 = s + ((s[s.size() - 1] == 's')?"" : "s");
	//int grade = 90;
	//cout << (grade > 60) ? "fail" : "pass"; //输出1；

	unsigned char bits = 0227;
	cout << (bits << 8) << endl; // char进行位运算会被提升为int类型

	long long  x[10], * p = x;
	cout << sizeof(x) << endl; //返回数组占用总容量大小
	cout << sizeof(*x) << endl;//返回数组首元素大小
	cout << sizeof(p) << endl;//返回指针大小（一个地址，32位）
	cout << sizeof(*p) << endl;//返回数组首元素大小
	return 0;
}