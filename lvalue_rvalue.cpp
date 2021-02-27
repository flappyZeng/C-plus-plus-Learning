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
int main()
{
	int grade = 90;
	cout << ((grade > 60) ? "fail" : "pass");
	return 0;
}