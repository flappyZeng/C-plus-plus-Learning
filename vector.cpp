#include"Base.h"
#include<vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

void func_vector()
{
	vector<string>vcStr{ 10, "Hello" };  //����൱��vector<string>vcStr(10, "hello")��Ϊ�����������б��ڰ���int�����ǵ���Ĭ�ϳ�ʼ������
	for (auto s : vcStr)
		cout << s << " " << endl;
}

int mainVec()
{
	func_vector();
	return 0;
}
