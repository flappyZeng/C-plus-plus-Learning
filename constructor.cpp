#include"Base.h"

using namespace std;

class A {
private:
	int x; 
	int y;
	int order;
public:
	//���������Ĺ��캯��
	A(int ord): x(0), y(0), order(ord) { cout <<order <<  " ���ò��������Ĺ��캯��" << endl; }
	//��ͨ���캯��
	A(int a, int b, int ord) : x(a), y(b), order(ord) { cout <<order <<  " ������ͨ���캯��" << endl; }

	//�������캯��
	A(const A& a) : x(a.x), y(a.y), order(a.order + 1) { cout <<order << " ���ÿ������캯��" << endl; }

	//���ƹ��캯��
	A& operator=(const A& a)
	{
		x = a.x;
		y = a.y;
		order = a.order + 1;
		cout <<order <<  " ���ÿ������ƺ���" << endl;
		return *this;
	}

	//��������
	~A()
	{
		cout << order << " ";
		cout << "������������" << endl;
	}

	inline int getX() { return x; }
	inline int getY() { return y; }

};

class Numbers {
public:
	int mysn;
	Numbers() : mysn(0) {};
	Numbers(const Numbers& s) = default;  //��ʽ��֪���������ɺϳɰ汾�ĸ��ƹ��캯��
	Numbers& operator=(const Numbers&) = delete;  //��ֹ��ֵ���㣬����Ϊɾ����
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
	HasPtr& operator=(const HasPtr& hp) {  //����Ҫ�ǵ�ɾ��ԭ������ps��ָ�����Դ��
		++*hp.use;
		if (-- * use == 0)
		{
			delete ps;
			delete use;
		}

		num = hp.num;
		//delete ps;  ������delete ps����Ϊ����hp��this��ͬһ������Ļ��������ͻ����
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

	//���ڷ�������Դ���࣬����swap������һ�ֺ���Ҫ���Ż��ֶ�
	friend void swap(HasPtr& lhs, HasPtr& rhs);
	friend bool operator<(const HasPtr& lhs, const HasPtr& rhs);
	/*
	//����ȫ�汾�ĸ�ֵ������ʽ��ʹ�ÿ���������
	HasPtr& operator=(HasPtr hp)  //�������ֵ
	{
		swap(*this, hp); //hp��һ����ʱ�ڴ棬������hpָʾ�ľ���ԭ��thisָ��ָ����ڴ棬��������ʱ���������ڴ�ᱻ�Զ�����
		return *this;
	}
	*/
	/*
	bool operator<(const HasPtr& hp)
	{
		cout << "���ñȽ����������" << endl;
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
	//�ڲ�����ϵͳ�ṩ��swap����
	cout << "����HasPtr���ص�swap����" << endl;
	using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.num, rhs.num);
}

bool operator<(const HasPtr& lhs, const HasPtr& rhs)
{
	cout << "���ñȽ����������" << endl;
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
	//std::swap(lhs.h, rhs.h);   �������ǵ����˱�׼�����õ�swap������������HasPtr�����swap����
	using std::swap;
	swap(lhs.h, rhs.h);  //�����ӵ��õľ���HasPtr�����swap������
}
class TreeNode {
private:
	string value;
	int count;
	TreeNode* left;
	TreeNode* right;

public:
	//Ĭ�Ϲ��캯��
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
	int size = 33;  // С��33ʱʹ��ϵͳ�Դ���swap������ʹ�����ص�swap
	for (int i = size - 1; i >= 0; --i)
	{
		hpv.emplace_back(HasPtr(to_string(i), i));
	}
	sort(hpv.begin(), hpv.end());
	for (int i = 0; i < size; ++i)
		hpv[i].print(cout);
	return 0;

}