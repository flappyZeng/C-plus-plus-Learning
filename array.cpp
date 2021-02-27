#include"Base.h"

using std::cin;
using std::cout;
using std::endl;

void func_array()
{
	constexpr unsigned int cnt = 42;
	std::string arr[cnt];  // cnt�����ǳ������ʽ
	char a2[] = "Danie";
	char a1[6] = "Danie";  // ����5���ַ�����ΪĬ�Ͻ�β��'\0'
	//cout << a1.size() << " " << a2.size() << endl; ����

	// begin�Լ�end����
	char* p = std::begin(a1);
	char* last = std::end(a1);
	while (p != last)
	{
		cout << *p << " ";
		p++;
	}

	char* notExsit = &a1[6];  // ������Ԫ�أ�������ʾ����Ľ�β����������lastָ����ͬ
	cout << (last == notExsit) << endl;  //����1,True

	char* minus = &a1[3];
	char c = minus[-2];
	cout << c << endl;  // ��ӡ����a ��Daniel�� 3 - 2 = 1;

	// c_str��c++Ϊ�˼���c�ṩ��һ���ӿڣ�
	std::string s = "abcsrd";
	const char* pc = s.c_str(); // ���Խ�stringתΪc�����ַ���,pc��ָ��s��ָ�룬�����Ǹ���s��s�ı���pcҲ���
	s = "absced";
	const char* ls = pc + s.length();
	cout << "p����ַ���" << endl;
	while (pc != ls)  // �������"absced"
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
	//��Χfor���
	for (int (&arr)[4] : ai) // ʹ����������� �ȵȼ��� int_array & arr : ai
		for (int &val : arr)
			cout << val << " ";
	cout << endl;

	// �±��������
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			cout << ai[i][j] << " ";
	cout << endl;

	//ָ��汾
	for (int (*p)[4] = ai; p != std::end(ai); ++p) // ʹ��ָ�������ָ�� �ȼ���int_array *p;
		for (int* q = *p; q != std::end(*p); ++q)
			cout << *q << " ";
	cout << endl;

	//����ѭ���ڵ�����������������Ըĳ�auto
}
int mainArr()
{
	//func_array();
	func_multiLayersArray();
	return 0;
}