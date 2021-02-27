#include"Base.h"

using namespace std;

class A {
private:
	int x; 
	int y;
	int order;
public:
	//不带参数的构造函数
	A(int ord): x(0), y(0), order(ord) { cout <<order <<  " 调用不带参数的构造函数" << endl; }
	//普通构造函数
	A(int a, int b, int ord) : x(a), y(b), order(ord) { cout <<order <<  " 调用普通构造函数" << endl; }

	//拷贝构造函数
	A(const A& a) : x(a.x), y(a.y), order(a.order + 1) { cout <<order << " 调用拷贝构造函数" << endl; }

	//复制构造函数
	A& operator=(const A& a)
	{
		x = a.x;
		y = a.y;
		order = a.order + 1;
		cout <<order <<  " 调用拷贝复制函数" << endl;
		return *this;
	}

	//析构函数
	~A()
	{
		cout << order << " ";
		cout << "调用析构函数" << endl;
	}

	inline int getX() { return x; }
	inline int getY() { return y; }

};

class Numbers {
public:
	int mysn;
	Numbers() : mysn(0) {};
	Numbers(const Numbers& s) = default;  //显式告知编译器生成合成版本的复制构造函数
	Numbers& operator=(const Numbers&) = delete;  //阻止赋值运算，定义为删除的
};

void f(Numbers s) { cout << s.mysn << endl; }

class Employee {
public:
	using NameType = string;
	using IDType = size_t;
	
private:
	NameType name;
	IDType ID;
	static IDType StartID;

public:
	Employee() : ID(StartID++) {}
	Employee(const NameType& inpName) : name(inpName), ID(StartID++) {}
	Employee(const Employee& E) = delete;
	Employee& operator=(const Employee& E) = delete;
};
Employee::IDType Employee::StartID = 0;

class HasPtr {
private:
	int  num;
	string* ps;
	size_t* use;
public:
	HasPtr(const string& s = std::string(), const int cnt = 0) : ps(new string(s)), num(cnt), use(new size_t(1)) {}
	HasPtr(const HasPtr& hp) : num(hp.num), ps(new string(*hp.ps)), use(hp.use) { ++* use; }
	HasPtr& operator=(const HasPtr& hp) {  //这里要记得删除原来类中ps所指向的资源；
		++*hp.use;
		if (-- * use == 0)
		{
			delete ps;
			delete use;
		}

		num = hp.num;
		//delete ps;  不能先delete ps，因为加入hp和this是同一个对象的话下面语句就会出错；
		ps = hp.ps;
		use = hp.use;
		return *this;
	}
	~HasPtr()
	{
		if (-- * use == 0)
		{
			delete ps;
			delete use;
		}
		
	}

	//对于分配了资源的类，定义swap函数是一种很重要的优化手段
	friend void swap(HasPtr& lhs, HasPtr& rhs);
	friend bool operator<(const HasPtr& lhs, const HasPtr& rhs);
	/*
	//更安全版本的赋值运算表达式，使用拷贝并交换
	HasPtr& operator=(HasPtr hp)  //传入的是值
	{
		swap(*this, hp); //hp是一块临时内存，交换后，hp指示的就是原来this指针指向的内存，函数结束时，该区域内存会被自动销毁
		return *this;
	}
	*/
	/*
	bool operator<(const HasPtr& hp)
	{
		cout << "调用比较运算符重载" << endl;
		return num < hp.num;
	}
	*/
	ostream& print(ostream& os)
	{
		os << num << " " << *ps << endl;
		return os;
	}
};

inline void swap(HasPtr& lhs, HasPtr& rhs)
{
	//内部调用系统提供的swap函数
	cout << "调用HasPtr重载的swap函数" << endl;
	using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.num, rhs.num);
}

bool operator<(const HasPtr& lhs, const HasPtr& rhs)
{
	cout << "调用比较运算符重载" << endl;
	return lhs.num < rhs.num;
}
class Foo {
private:
	HasPtr h;
public:
	Foo() : h(HasPtr()) {}
	friend void swap(Foo& lhs, Foo& rhs);
};

inline void swap(Foo& lhs, Foo& rhs)
{
	//std::swap(lhs.h, rhs.h);   这样子是调用了标准库内置的swap函数，而不算HasPtr定义的swap函数
	using std::swap;
	swap(lhs.h, rhs.h);  //这样子调用的就是HasPtr定义的swap函数。
}
class TreeNode {
private:
	string value;
	int count;
	TreeNode* left;
	TreeNode* right;

public:
	//默认构造函数
	TreeNode(const string& s = "", int cnt = 0, TreeNode * left = nullptr, TreeNode * right = nullptr) : value(s), count(cnt), left(left), right(right) {}
	TreeNode(TreeNode& node) : value(node.value), count(node.count), left(node.left), right(node.right) {}
	TreeNode& operator=(TreeNode& node)
	{
		auto newl = new TreeNode(*node.left);
		auto newr = new TreeNode(*node.right);
		value = node.value;
		count = node.count;
		delete left;
		delete right;
		left = newl;
		right = newr;
		return *this;
	}
	~TreeNode()
	{
		delete left;
		delete right;
	}
};

class BinStrTree {
private:
	TreeNode* root;
public:
	BinStrTree() :root(nullptr) {};
	BinStrTree(BinStrTree& p) : root(p.root) {}
	BinStrTree& operator=(BinStrTree& node) {
		if (node.root == root)
			return *this;
		delete root;
		root = node.root;
		return *this;
	}

	~BinStrTree()
	{
		root->~TreeNode();
	}
};
void useA(A a)
{
	//cout << a.getX() << " " << a.getY() << endl;
}

void testA()
{
	A a(1);
	cout << endl;
	A b(a);
	cout << endl;
	A c = b;
	cout << endl;
	A d(1, 2, 4);
	cout << endl;
	A e = { 1, 2, 5 };
	cout << endl;
	useA(a);

	A* p = new A(2, 3, 6);
	cout << a.getX() << endl;
	delete p;
}

int mainCons()
{
	vector<HasPtr>hpv;
	int size = 33;  // 小于33时使用系统自带的swap，否则使用重载的swap
	for (int i = size - 1; i >= 0; --i)
	{
		hpv.emplace_back(HasPtr(to_string(i), i));
	}
	sort(hpv.begin(), hpv.end());
	for (int i = 0; i < size; ++i)
		hpv[i].print(cout);
	return 0;

}