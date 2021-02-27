#include"Base.h"
//已经有了algorithm
#include<list>
#include<iterator>  //各种迭代器
#include<numeric>  //这个和algorithm一样，也是装算法的头文件， partition函数
#include<functional> //bind函数, ref,cref函数，帮助bind函数传入ostream流的引用
#include<fstream>
#include<forward_list>


using std::cin;
using std::cout;
using std::endl;

void C10T1(int num)
{
	std::vector<int>vc;
	vc.reserve(50);
	int inp;
	while (cin >> inp)
	{
		vc.push_back(inp);
	}
	cout << std::count(vc.begin(), vc.end(), num) << endl;
}

void C10T2(const std::string& str)
{
	std::list<std::string>ls;
	std::string s;
	while (cin >> s)
	{
		ls.push_back(s);
	}
	cout << std::count(ls.begin(), ls.end(), str);
}

void C10T6()
{
	std::vector<int>vc = { 1, 2, 3, 4,5, 6, 7, 8,9 };
	std::fill_n(vc.begin(), vc.end() - vc.begin(), 0);
	for (int& in : vc)
		cout << in << " ";
	cout << endl;
}

//删除容器中的重复元素
void C10T9()
{
	std::vector<int>vc = { 1, 2, 6, 8, 9, 3,6 , 3, 5, 66, 1, 3, 90 };
	std::sort(vc.begin(), vc.end());
	for (int& i : vc)
		cout << i << " ";
	cout << endl;
	auto it = std::unique(vc.begin(), vc.end());
	for (int& i : vc)
		cout << i << " ";
	cout << endl;
	vc.erase(it, vc.end());
	for (int& i : vc)
		cout << i << " ";
	cout << endl;
}

bool C10T13(std::vector<std::string >& vec)
{
	auto it = std::partition(vec.begin(), vec.end(),[](const std::string& a) {return a.size() > 5; });
	auto be = vec.begin();
	for (; be != it; ++be)
		cout << *be << " ";
	cout << endl;
	return !(it == vec.end());
}

void C10T29()
{
	std::vector < std::string>vec;
	std::ifstream in("C:\\Users\\Administrator\\Desktop\\2.txt");
	std::istream_iterator<std::string>in_iter(in), eof;
	while (in_iter != eof)
	{
		vec.push_back(*in_iter++);
	}
	cout << vec[0] << endl;
	for (std::string& item : vec)
		cout << item << " ";
	cout << endl;
}

void C10T30()
{
	std::vector<int>vc;
	std::istream_iterator<int>in_iter(cin), eof;
	std::ostream_iterator<int>out_iter(cout, " ");
	std::ostream_iterator<std::string>out_iter2(cout);

	std::copy(in_iter, eof, std::back_inserter(vc));  //因为不知道要输入多少个元素，所以不能用vc.begin(),而要使用尾部插入迭代器
	std::sort(vc.begin(), vc.end());
	std::copy(vc.begin(), vc.end(), out_iter);
	//C10T31，打印不重复的元素
	*out_iter2++ = "\n";
	std::unique_copy(vc.begin(), vc.end(), out_iter);  //unique只能去掉相邻的重复元素，所以一般用之前需要排序
}

void C10T33(const std::string inFileName, const std::string outOddFileName, const std::string outEvenFileName)
{
	std::ifstream in(inFileName);
	std::istream_iterator<int>in_iter(in), eof;
	std::ofstream outOdd(outOddFileName, std::fstream::ate);
	std::ofstream outEven(outEvenFileName, std::fstream::ate);
	std::ostream_iterator<int>out_iter_odd(outOdd, " ");
	std::ostream_iterator<int>out_iter_even(outEven, " ");
	while (in_iter != eof)
	{
		//奇数
		if ((*in_iter) & 1)
			*out_iter_odd++ = *in_iter++;
		else
			*out_iter_even++ = *in_iter++;
	}
	cout << "over" << endl;
}

void lambda(int c)
{
	auto lamb = [](const int& a, const int& b) -> int { return a + b; };
	auto lamb1 = [c](const int& a) -> int {return a + c; };
	cout << lamb(1, 2) << endl;
	
}

void testLambda()
{
	size_t v1 = 42;
	auto f = [v1] {return v1; };
	auto f2 = [=] {return v1; };  //值捕获
	auto f1 = [&v1] {return v1; };
	auto f3 = [&] {return v1; };   //引用捕获
	v1 = 0;
	cout << f() << endl; //42，lambda在创建时就会捕获
	cout << f2() << endl; //42，lambda在创建时就会捕获
	cout << f1() << endl; //0，使用引用的方式捕获
	cout << f3() << endl; //0，使用引用的方式捕获
}

void testLambdaVal()
{
	size_t v2 = 42;
	//auto f = [v2]() {return ++v2; };  //会报错，lambda默认不改变值
	auto f = [v2]() mutable {return ++v2; }; //可行.
	cout << f() << endl; //43
	cout << v2 << endl;  //因为是传值，所以v2还是42
}

void testLambdaRet()
{
	int v = 43;
	auto f = [](int k) { if (k > 0) return k; else return 0; }; //不报错
	auto f2 = [](int k) -> int { if (k > 0) return k; else return 0; }; //指定返回类型
	auto f3 = [&v]() -> bool { if (v > 0) { --v; return false; } else return true; };
	while (!f3())
	{
		cout << v << " ";
	}
}

bool checkSize(const std::string& s, std::string::size_type sz)
{
	if (s.length() > sz)
		return true;
	else
		return false;
}


//反向迭代器
void funcReverseIter()
{
	std::vector<int>vc = { 1, 2, 3, 4, 5, 6 ,7, 8 ,9, 10 };
	std::copy(vc.crbegin(), vc.crend() - 5, std::ostream_iterator<int>(cout, " "));  //这里应该用到-5,而不是+5,因为vc.crend()是一个常量反向迭代器
	auto it =  std::find_if(vc.crbegin(), vc.crend(), [](const int& a) {return a < 5; });
	cout << endl;
	std::copy(vc.crbegin(), it, std::ostream_iterator<int>(cout, " "));
	cout << endl;
	std::copy(it.base(), vc.cend(), std::ostream_iterator<int>(cout, " "));   // 与上一行反序输出， it是一个反向迭代器，it.base()返回一个对应位置后一个位置的正向迭代器。(a - 1, b] --> [a, b + 1)
	cout << endl;
}


//fill函数以及fill_n函数
void others()
{
	std::vector<double>vc{ 1.0, 2.5, 3, 4 ,5 ,6, 7, 8, 9, 10 };
	std::fill(vc.begin(), vc.begin() + 5, 10); //前五个元素置为10
	std::fill_n(&vc[0], 3, 20); //vc开始的3个元素置为20,第一个位置为指针或者迭代器
	cout << std::accumulate(vc.begin(), vc.end(), 0); //求和，--> 参数： 开始，结束，初始值

	//插入迭代器，保证有足够的空间插入元素
	std::vector<int>vec;
	std::fill_n(std::back_inserter(vec), 10, 5);  //可以向空容器插入元素，上面的例子不能
}

std::ostream&  print(std::ostream& os, const std::string & s,const char& c)
{
	return os << s << c ;
}


int mainAlgo()
{
	//C10T1(5);
	//C10T2("abc");
	//C10T6();
	//C10T9();
	
	std::vector<std::string>vec = { "adaffs", "fsfsf", "sfsfsf", "sdfsfsfsf", "fs", "fsfsfs", "fsfs", "fasfrewrw", "wrw" };
	std::string::size_type sz = 4;

	auto it = std::find_if(vec.cbegin(), vec.cend(), [sz](const std::string& s) {return s.size() > sz; });
	if (it != vec.end())
		cout << *it << endl;

	//下面部分和上面3行代码作用一样
	auto it1 = std::find_if(vec.cbegin(), vec.cend(), std::bind(checkSize, std::placeholders::_1, sz)); //std::placeholder::_1是占位符
	if (it1 != vec.end())
		cout << *it1 << endl;

	std::ostream& os = cout;
	std::for_each(vec.cbegin(), vec.cend(), [&os](const std::string& s) {os << s << " "; });
	cout << endl;
	const char c = ' ';

	//参数记得传引用，不能直接掺入os
	std::for_each(vec.cbegin(), vec.cend(), std::bind(print, std::ref(os), std::placeholders::_1, std::cref(c))); //这里报错，已经处理
	
	//插入迭代器
	auto it2 = std::back_inserter(vec); //相当于push_back；
	const std::string s = std::string("aaaa");
	*it2 = s;  //向vec的尾部插入s串；

	std::back_insert_iterator<std::vector<std::string>> it21 = std::back_inserter(vec);
																										 //cout << C10T13(vec);
	//cout << std::count_if(vec.begin(), vec.end(), [](const std::string& s) {return s.length() > 6; }) << endl;
	//std::vector<std::string>newVec = std::vector<std::string>(vec.begin(), it);
	//testLambdaRet();
	return 0;
}


//迭代器： 输入迭代器、输出迭代器、 前向迭代器、双向迭代器、 随机访问迭代器


// 迭代器适配器，插入迭代器适配器：back_inserter, front_inserter, inserter
int mainInsert()
{
	std::list<int>lst = { 1, 2, 3, 4 , 5, 3};
	std::list<int>lst2, lst3, lst4, lst1 = { 5 };
	std::copy(lst.begin(), lst.end(), std::inserter(lst1, lst1.begin())); //正序 1 2 3 4 ， insert后还是指向lst1.begin()所指的位置
	//				5       -->   1 5  -->  1 2 5  -->  1 2 3 5   --> 1 2 3 4 5
	//迭代器位置：  ⬆               ⬆           ⬆             ⬆               ⬆，
	//所以上面的inserter的结果还是正序
	std::copy(lst.begin(), lst.end(), std::front_inserter(lst2));   //倒序4 3 2 1
	std::copy(lst.begin(), lst.end(), std::back_inserter(lst3));   //正序 1 2 3 4
	for(auto & in : lst1)
		cout << in << " ";
	cout << endl;

	for (auto& in : lst2)
		cout << in << " ";
	cout << endl;

	for (auto& in : lst3)
		cout << in << " ";
	cout << endl;
	// std::sort(lst.begin(), lst.end(), [](int& a, int& b) {return a < b; });list不提供随机访问，所以不能调用algorithm中的排序函数
	// list有自带的sort函数；
	lst.sort();
	std::unique_copy(lst.cbegin(), lst.cend(), std::back_inserter(lst4));
	for (auto& in : lst4)
		cout << in << " ";
	cout << endl;
	return 0;
}


//流迭代器：输入迭代器、输出迭代器
int mainFlow()
{
	std::vector<int>vc;
	std::istream_iterator<int>in_iter(cin);
	std::istream_iterator<int>eof;  //eof被定义为空的流迭代器
	while (in_iter != eof)
	{
		vc.push_back(*in_iter++);   //不使用自增的话程序失效，只能输入一个字符
	}
	cout << "结束" << endl;  //使用CTRL+ Z 停止输入
	return 0;
}

void printR(const std::vector<int>& vc)
{
	for (const int& item : vc)
		cout << item << " ";
	cout << endl;
}

int mainCopyRepalce()
{
	//C10T29();
	//C10T30();
	
	//测试C10T33:
	/*
	std::string inFileName = "C:\\Users\\Administrator\\Desktop\\3.txt";
	std::string outOddFileName = "C:\\Users\\Administrator\\Desktop\\4.txt";
	std::string outEvenFileName = "C:\\Users\\Administrator\\Desktop\\5.txt";
	C10T33(inFileName, outOddFileName, outEvenFileName);
	*/
	funcReverseIter();
	std::vector<int>a, b, c, d, orgin = { 1, 2, 3, 4 ,2, 3, 5, 6, 7,8, 9, 10 };
	std::copy(orgin.begin(), orgin.end(), std::back_inserter(a));
	cout << "a: ";
	printR(a);
	std::copy_if(orgin.begin(), orgin.end(), std::back_inserter(b), [](const int& a) {return a > 5; });
	cout << "b: ";
	printR(b);
	std::replace(orgin.begin(), orgin.end(), 3, 13);
	cout << "orgin: ";
	printR(orgin);
	std::replace_copy_if(a.begin(), a.end(), std::back_inserter(d), [](const int& a) {return a > 5; }, 30);
	cout << "d: ";
	printR(d);
	return 0;
}

int mainList()
{
	//list,forward_list特有的方法
	std::list<int>lst = { 1, 2, 3, 4, 5, 6, 8, 10, 13 };
	std::list<int>lst2 = { 1, 2, 3, 4, 5, 6, 9/*, 8, 10, 13, 10*/ };
	std::forward_list<int>flst = { 1, 2, 3, 4, 5,6, 8, 10, 13, 10 };
	//std::forward_list<int>flst2(lst); 不能用list初始化forward_list
	lst.merge(lst2);   //lst内的元素必须要有序，否则报错
	for (int& item : lst)
		cout << item << " ";
	cout << endl;
	cout << lst2.size() << endl;   //merge之后lst2内的元素将全部被删除

	std::list<int>nlst = { 1, 2, 2, 3, 5, 6, 3, 5, 9, 8 ,3 ,4, 3, 5, 6, 7, 7, 9, 8 };
	nlst.sort();
	nlst.unique();    //list以及forward_list提供的unique以及merge等函数会去除多余的元素，如unique中的重复元素以及meige中的被merge的链表中的元素
	for (int& item : nlst)
		cout << item << " ";
	cout << endl;
	return 0;
}