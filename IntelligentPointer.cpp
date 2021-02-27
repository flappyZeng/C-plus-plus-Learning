#include"Base.h"
#include<list>
#include<fstream>
#include"StrBlob.h"
#include<iterator>

using namespace std;;

//智能指针包括shared_ptr 、 unique_ptr 、 weak_ptr

//shared_ptr允许多个指针指向同一个对象
//unique_ptr则“独占”所指向的对象
//weak_ptr 是一种伴随类，是一种弱引用， 指向share_ptr所管理的对象

//三种智能指针都在 头文件memory中 
#include<memory>  //提供shared_ptr, unique_ptr, weak_ptr, 内部还包含allocator类

//share_ptr
void shared_ptrTest()
{
	string s = "abc";
	shared_ptr<string>ps = make_shared<string>(s);  //不能直接用&s初始化,括号内可以匹配string任意一个构造函数
	shared_ptr<list<int> >pli;  //智能指针shared_ptr

	auto p = ps.get();  //返回ps对应的指针；
	cout << *p << endl;

	auto r = make_shared<int>(42);
	auto q = make_shared<int>(43);
	r = q;
	cout << q.use_count() << endl;  //返回q的引用计数，这里是2，可能比较慢，一般用于调试

	//shared_ptr<int>p1 = new int(1024); 报错，无法完成内置指针类型到只能指针类型的隐式转换
	shared_ptr<int>p2(new int(1024));  //可行，必须直接初始化

}


vector<int>* getVector(vector<int>::size_type size)
{
	return new vector<int>(size);
}

void getValues(vector<int>* vc)
{
	int size = vc->size();
	for (int i = 0; i < size; ++i)
		cin >> (*vc)[i];
}

void showVc(vector<int>* vc)
{
	int size = vc->size();
	for (int i = 0; i < size; ++i)
		cout << (*vc)[i];
	cout << endl;
	delete vc;
}

//IntelligentPointer
shared_ptr<vector<int>> getVectorSP(vector<int>::size_type size)
{
	return make_shared<vector<int> >(size);
}

void getValueSP(shared_ptr<vector<int>> vc)
{
	int size = vc->size();
	for (int i = 0; i < size; ++i)
		cin >> (*vc)[i];
}

void showVcSP(shared_ptr<vector<int> > vc)
{
	int size = vc->size();
	for (int i = 0; i < size; ++i)
		cout << (*vc)[i] << " ";
	cout << endl;

}

bool b() {
	int *p = new int;
	cout << p << endl;
	return p; //p是内存中的一个地址，一定是不等于0的，因此bool(p) = 1;
}

int mainPTR()
{
	//shared_ptrTest();
	auto p1 = new auto(10);
	//auto p2 = new auto{1, 2, 3}; 推断不出来

	const string* pcs = new const string;  //隐式初始化 *pcs = "";
	const int* pci = new const int();  //隐式初始化  *pci = 0;
	const string* pcs2 = new const string("abc"); //显式初始化

	int* p3 = new int;   //如果分配失败，抛出异常std::bad_alloc
	int* p2 = new(nothrow)int;  //如果分配失败，就返回空指针

	cout << *pcs2 << " " << *pci << endl;

	vector<int>* vc = getVector(10);
	getValues(vc);
	showVc(vc);

	shared_ptr<vector<int> >Spvc = getVectorSP(10);
	getValueSP(Spvc);
	showVcSP(Spvc);

	bool p = b();
	cout << p << endl;

	return 0;
}

void process(shared_ptr<int>ptr)
{
	cout << ptr.use_count() << endl;
}

//智能指针的好处
void f()
{
	shared_ptr<int>sp(new int(42));
	//some codes which might induces a exception;
}

void f1()
{
	int* p = new int(42);
	//some codes which might induces a exception;
	delete p;
}

//上述的f和f1在发生异常是，智能指针会自动delete内存，因此内存得到释放。
//但是，对于常规指针，异常后因为不能执行delete，会导致内存得不到释放，可能造成内存泄露



//C12T14
struct destination
{
	int dist;
	destination() :dist(0) {};
	destination(int d) :dist(d) {};
};
struct connection
{
	int point;
	connection() :point(0) {};
	connection(int pt) : point(pt) {};
	connection(destination* d) : point(d->dist) {};
};
connection connect(destination*d)
{
	return connection(d);
};
void disconnect(connection c)
{
	return;
}
void f(destination& d)
{
	connection c = connect(&d);
}

void end_connection(connection* p) { disconnect(*p); }

void f1(destination& d)
{
	connection c = connect(&d);
	shared_ptr<connection>p(&c, end_connection);
}

void f2(destination& d)
{
	connection c = connect(&d);
	shared_ptr<connection>p(&c, [](connection* p) {disconnect(*p); });
}

//weak_ptr
//weak_ptr和shared_ptr共享对象，但是不增加shared_ptr的引用计数
//必须用shared_ptr初始化weak_ptr对象；
void weakPtrTest()
{
	shared_ptr<int>p(new int(42));
	weak_ptr<int>wp(p);
	cout << p.use_count() << endl;  //输出是1；
	//因为weak_ptr伴随着shared_ptr.因此shared_ptr被回收时，weak_ptr可能指向空内存，因此不能直接访问对象

	weak_ptr<int>wp2 = wp; //可以用weak_ptr赋值给另一个weak_ptr;
	cout << wp.use_count() << endl;  //1
	cout << wp.expired() << endl; //p的use_count()为0，则返回true,否则返回false;
	shared_ptr<int>newp = wp.lock();  //wp.lock的作用，如果wp.expired()为true,则返回空的shared_ptr，否则返回一个指向wp的shared_ptr

	weak_ptr<int>wp3(shared_ptr<int>(new int(43)));
	//unique_ptr<int>newup(wp3);    //不能使用weak_ptr初始化unique_ptr；

	//可以用weak_ptr初始化shared_ptr;
	shared_ptr<int>sp2(wp3);
}

int mainUniquePtr()
{
	shared_ptr<int>p(new int(42));
	cout << p.use_count() << endl;
	process(p);
	cout << p.use_count() << endl;

	unique_ptr<int>p2(new int(42));
	auto p3 = p2.release();  //p3是个常规指针
	//shared_ptr<int>p5(p3);
	unique_ptr<int>p4(p3);  //可以用来初始化新的unique_ptr;接管，p3的内存被释放
	cout << *p4 << endl;
	
	//cout << p5.use_count() << endl;
	//unique_ptr<int>newp(p4); 直接报错

	//int* p6 = p4; //不能拷贝；
	//delete p6;  //更无法删除

	//可行
	int* p7 = p4.release();
	delete p7;
	
	return 0;
}

unique_ptr<string> mergeStr(const string a, const string b)
{
	return unique_ptr<string>(new string(a + b));
}

unique_ptr<char[]> merChars(char* a, char* b, int lena, int lenb)
{
	int len = lena + lenb;
	unique_ptr<char[]>ret(new char[len]);
	for (int i = 0; i < lena; ++i)
		ret[i] = a[i];
	for (int i = lena; i < len; ++i)
		ret[i] = b[i - lena];
	return ret;
}

void testStrBlob()
{
	StrBlob sb;

	ifstream input("C:\\Users\\Administrator\\desktop\\words.txt", fstream::in);

	/*
	istream_iterator<string>in_itr(input), eof;
	while (in_itr != eof)
	{
		sb.push_back(*in_itr++);
	}
	*/

	string s;
	while (getline(input, s))
	{
		sb.push_back(s);
	}

	StrBlobPtr sbpbegin = sb.begin();
	StrBlobPtr sbpend = sb.end();


	while (sbpbegin != sbpend)
	{
		cout << sbpbegin.deref() << endl;
		sbpbegin.incr();
	}
}

int mainCharArr()
{
	int* p = new int[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9,10 }; //c++ 11新特征
	//char arr[0]  这个是错误的
	char* p2 = new char[0]; // 这个是可行的，但是指针只能+0 -0,且 不能解引用；

	//只有unique_ptr定义了下标运算，shared_ptr未定义下标，只能通过get函数返回常规指针后操作
	unique_ptr<int []>up(new int[10]);
	unique_ptr<int[]>pup(p);  //使用内置指针初始化
	shared_ptr<int []>sp(new int[10], [](int* p) { delete[]p; }); //shared_ptr不支持动态数组的直接管理，必须传递相应的析构函数(删除器)
	unique_ptr<vector<int> >vup(new vector<int>(10, 1));
	up[3] = 5;  //可行
	(*vup)[3] = 5;

	auto pn = mergeStr("abc", "cde");
	cout <<  *pn << endl;
	char* a = new char[3] {'a', 'b', 'c'};
	char* b = new char[3] {'c', 'd', 'e'};
	auto pc = merChars(a, b, 3, 3);
	for (int i = 0; i < 6; ++i)
		cout << pc[i];

	return 0;
}
void C12T26()
{
	allocator<string>alloc;
	auto p = alloc.allocate(10);
	string s;
	auto q = p;
	while (cin >> s && q != p + 10)
	{
		alloc.construct(q++, s);
	}
	const size_t sz = q - p;
	while (q != p)
	{
		alloc.destroy(--q);
	}
	alloc.deallocate(p, 10);
}
int mainAllocator() {
	allocator<int>a;  //将内存分配和对象构造分开来
	a.allocate(10);  //分配10个int对象的内存，（未构造)

	allocator<string>alloc;
	auto const p = alloc.allocate(10);  //allocate返回一个对应类型的指针

	auto q = p;
	alloc.construct(q);		   //*q = ""
	cout << *q << endl;
	q++;
	alloc.construct(q, 5, 'c');  //*q = "ccccc"
	cout << *q << endl;
	q++;
	alloc.construct(q,  "hi");   //*q = "hi"
	cout << *q << endl;
	q++;
	cout << alloc.max_size() << endl;
	while (q != p)
	{
		alloc.destroy(--q);    //回收内存
	}
	alloc.deallocate(p, 10);
	// vector<int, allocator<int> > ==  vector<int>

	vector<int>vi{ 1, 2, 3, 4, 5, 6 };
	allocator<int>alloc2;
	auto p1 = alloc2.allocate(vi.size() * 2);
	auto q1 = uninitialized_copy(vi.begin(), vi.end(), p1);
	auto q2 = uninitialized_fill_n(q1, vi.size(), 42);

	return 0;
}