#include"Base.h"

using std::cin;
using std::cout;
using std::endl;


int arr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

void print(int ia[])  //��������ȼ���print(int *ia)���Է������������� ����������10��
{
	cout << "����ָ��汾" << endl;
	for (auto i = 0; i  != 10; ++i)
		cout << ia[i] << endl;
}

void print(int(&ia)[10])
{
	cout << "�������ð汾" << endl;
	for (auto i = 0; i != 10; ++i)
		cout << ia[i] << endl;
}

//��������ĺ���
int(*func(int arr[][10], int i))[10]
{
	return &arr[i];
}

//�������麯���ĵڶ��ඨ��, ���������python���﷨��
auto func_two(int arr[][10], int i) -> int(*)[10]
{
	return &arr[i];
}

//�������麯���ĵ����ඨ��, ���ﲻ�ܵ���ʹ��decltype(arr1)����Ϊ����decltypeֻ�ܻ�ȡ�������飬�ܲ��ܻ�ȡָ��
decltype(arr1)* func_three(int arr[][10], int i)
{
	cout << __func__ << endl;  //�������溯�����ֵĺ�
	return &arr[i];
}

int mainarrs()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int arr3[][10] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10} };
	int(&b)[10] = arr1;
	func_three(arr3, 0);
	//print(b);
	return 0;
}