#include"Base.h"

using std::cin;
using std::cout;
using std::endl;

void func_array()
{
	constexpr unsigned int cnt = 42;
	std::string arr[cnt];  // cnt必须是常量表达式
	char a2[] = "Danie";
	char a1[6] = "Danie";  // 最多放5个字符，因为默认结尾是'\0'
	//cout << a1.size() << " " << a2.size() << endl; 报错

	// begin以及end函数
	char* p = std::begin(a1);
	char* last = std::end(a1);
	while (p != last)
	{
		cout << *p << " ";
		p++;
	}

	char* notExsit = &a1[6];  // 不存在元素，仅仅表示数组的结尾。和上述的last指针相同
	cout << (last == notExsit) << endl;  //返回1,True

	char* minus = &a1[3];
	char c = minus[-2];
	cout << c << endl;  // 打印的是a ，Daniel， 3 - 2 = 1;

	// c_str是c++为了兼容c提供的一个接口；
	std::string s = "abcsrd";
	const char* pc = s.c_str(); // 可以将string转为c风格的字符串,pc是指向s的指针，并不是复制s；s改变了pc也会变
	s = "absced";
	const char* ls = pc + s.length();
	cout << "p风格字符串" << endl;
	while (pc != ls)  // 输出的是"absced"
	{
		cout << *pc;
		pc++;
	}
	cout << endl;

	
}

void func_multiLayersArray()
{
	int ai[3][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

	using int_array = int[4];
	//范围for语句
	for (int (&arr)[4] : ai) // 使用数组的引用 等等价于 int_array & arr : ai
		for (int &val : arr)
			cout << val << " ";
	cout << endl;

	// 下标运算符：
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			cout << ai[i][j] << " ";
	cout << endl;

	//指针版本
	for (int (*p)[4] = ai; p != std::end(ai); ++p) // 使用指向数组的指针 等价于int_array *p;
		for (int* q = *p; q != std::end(*p); ++q)
			cout << *q << " ";
	cout << endl;

	//上述循环内的所有类别声明都可以改成auto
}
int mainArr()
{
	//func_array();
	func_multiLayersArray();
	return 0;
}