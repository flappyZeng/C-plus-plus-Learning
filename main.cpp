#include<iostream>
#include<vector>
#include"String.h"

using namespace std;
struct X {
	int i;
	std::string s;
};
struct hasX {
	X mem;
};

int main()
{
	X x, x2 = std::move(x); // ���x2 = x�����ǰ�ֵ������������ַ��һ��
	cout << &x << endl << &x2 << endl;  //������ַһ��
	hasX hx, hx2 = std::move(hx);
	std::vector<String>vS;
	char word[] = "abcde";
	String s("abc");
	std::cout << "����" << endl;

	//����һ��������6�ο������캯��? Ϊʲô��6��
	//ԭ��
	//	ÿ�ε���push_back���ǽ�vector�е�Ԫ�ظ���һ��
	for (int i = 0; i < 3; ++i)
	{
		vS.push_back(s);
		std::cout << std::endl;
	}
	
	vS.push_back(std::move(s));
	return 0;
}