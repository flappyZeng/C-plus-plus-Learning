#include<iostream>
#include<vector>
#include"String.h"
#include<fstream>
#include<iterator>
#include<algorithm>
#include<functional>
#include<map>
#include<exception>

using namespace std;

struct X {
	int i;
	std::string s;
};
struct hasX {
	X mem;
};

int C13T46()
{
	X x, x2 = std::move(x); // 如果x2 = x，则是按值拷贝，两个地址不一样
	cout << &x << endl << &x2 << endl;  //两个地址一样
	hasX hx, hx2 = std::move(hx);
	std::vector<String>vS;
	char word[] = "abcde";
	String s("abc");
	std::cout << "这里" << endl;

	//下面一共调用了6次拷贝构造函数? 为什么是6次
	//原因：
	//	每次调用push_back都是将vector中的元素复制一遍
	for (int i = 0; i < 3; ++i)
	{
		vS.push_back(s);
		std::cout << std::endl;
	}
	
	vS.push_back(std::move(s));

	std::plus<int>intAdd; //类定义了调用运算符，那么这个对象称为函数对象
	int sum = intAdd(1, 2);
	return 0;
}


class checkStringEqualK{
private:
	size_t size;
public:
	checkStringEqualK(size_t k):size(k) {}
	bool operator()(const string& s) { return s.size() == size; }
};
int C14T38()
{
	string path = "C:\\Users\\Administrator\\Desktop\\words.txt";
	ifstream ifs(path);
	istream_iterator<string>in(ifs), eof;
	vector<checkStringEqualK>ck{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	vector< vector<string> >cnts(10, vector<string>());
	vector<int>cnt(10, 0);
	while (in != eof)
	{
		for (int i = 0; i < 10; ++i)
			if (ck[i](*in))
			{
				cnts[i].emplace_back(*in);
				cnt[i] ++;
			}
				
		in++;
	}
	for (auto& vs : cnts)
	{
		for (auto& str : vs)
			cout << str << " ";
		cout << endl << endl;
	}

	for (auto& item : cnt)
		cout << item << " ";
	cout << endl;
	return 0;
}

int C14T42()
{
	vector<int>val = { 1, 2, 1025, 5 ,1068, 10, 3222, 2236, 3 };
	auto cnt = count_if(val.begin(), val.end(), bind(greater<int>(), placeholders::_1, 1024));
	cout << cnt << endl;;

	vector<string>str = { "pooh", "pooc", "pooh", "cooh", "pooh" };
	auto cnts =  find_if(str.cbegin(), str.cend(), bind(not_equal_to<string>(), placeholders::_1, "pooh"));
	cout << *cnts << endl;

	vector<int>mul = { 2, 4, 6, 7, 8,9 ,10 };
	transform(mul.begin(), mul.end(), mul.begin(), bind(multiplies<int>(), placeholders::_1, 2));
	for_each(mul.cbegin(), mul.cend(), [](const int& item) { cout << item << " "; });

	return 0;
}

class divide {
public:
	int operator()(int i, int j)
	{
		try {
			if (j == 0)
				throw "divide by 0!";
			else
				return i / j;
		}
		catch (exception e)
		{
			cout << "can't divide by 0!" << endl;
		}
	}
};

int C14T44()
{
	map<string, function<int(int, int)> >calular{
		{"+", [](int i, int j) {return i + j; }},
		{"-", [](int i, int j) { return i - j; }},
		{"*", bind(multiplies<int>(), placeholders::_1, placeholders::_2)},
		{"/", divide()}
	};
	cout << calular["+"](2, 2) << endl;
	cout << calular["-"](2, 2) << endl;
	cout << calular["*"](2, 2) << endl;
	cout << calular["/"](2, 2) << endl;
	return 0;
}
int mainC13()
{
	C14T44();
	return 0;
}