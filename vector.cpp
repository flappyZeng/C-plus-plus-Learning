#include"Base.h"
#include<vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

void func_vector()
{
	vector<string>vcStr{ 10, "Hello" };  //这个相当于vector<string>vcStr(10, "hello")因为编译器发现列表内包含int，考虑调用默认初始化函数
	for (auto s : vcStr)
		cout << s << " " << endl;
}

int mainVec()
{
	func_vector();
	return 0;
}
