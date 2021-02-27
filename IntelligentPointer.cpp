#include"Base.h"
#include<list>
#include<fstream>
#include"StrBlob.h"
#include<iterator>

using namespace std;;

//����ָ�����shared_ptr �� unique_ptr �� weak_ptr

//shared_ptr������ָ��ָ��ͬһ������
//unique_ptr�򡰶�ռ����ָ��Ķ���
//weak_ptr ��һ�ְ����࣬��һ�������ã� ָ��share_ptr������Ķ���

//��������ָ�붼�� ͷ�ļ�memory�� 
#include<memory>  //�ṩshared_ptr, unique_ptr, weak_ptr, �ڲ�������allocator��

//share_ptr
void shared_ptrTest()
{
	string s = "abc";
	shared_ptr<string>ps = make_shared<string>(s);  //����ֱ����&s��ʼ��,�����ڿ���ƥ��string����һ�����캯��
	shared_ptr<list<int> >pli;  //����ָ��shared_ptr

	auto p = ps.get();  //����ps��Ӧ��ָ�룻
	cout << *p << endl;

	auto r = make_shared<int>(42);
	auto q = make_shared<int>(43);
	r = q;
	cout << q.use_count() << endl;  //����q�����ü�����������2�����ܱȽ�����һ�����ڵ���

	//shared_ptr<int>p1 = new int(1024); �����޷��������ָ�����͵�ֻ��ָ�����͵���ʽת��
	shared_ptr<int>p2(new int(1024));  //���У�����ֱ�ӳ�ʼ��

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
	return p; //p���ڴ��е�һ����ַ��һ���ǲ�����0�ģ����bool(p) = 1;
}

int mainPTR()
{
	//shared_ptrTest();
	auto p1 = new auto(10);
	//auto p2 = new auto{1, 2, 3}; �ƶϲ�����

	const string* pcs = new const string;  //��ʽ��ʼ�� *pcs = "";
	const int* pci = new const int();  //��ʽ��ʼ��  *pci = 0;
	const string* pcs2 = new const string("abc"); //��ʽ��ʼ��

	int* p3 = new int;   //�������ʧ�ܣ��׳��쳣std::bad_alloc
	int* p2 = new(nothrow)int;  //�������ʧ�ܣ��ͷ��ؿ�ָ��

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

//����ָ��ĺô�
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

//������f��f1�ڷ����쳣�ǣ�����ָ����Զ�delete�ڴ棬����ڴ�õ��ͷš�
//���ǣ����ڳ���ָ�룬�쳣����Ϊ����ִ��delete���ᵼ���ڴ�ò����ͷţ���������ڴ�й¶



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
//weak_ptr��shared_ptr������󣬵��ǲ�����shared_ptr�����ü���
//������shared_ptr��ʼ��weak_ptr����
void weakPtrTest()
{
	shared_ptr<int>p(new int(42));
	weak_ptr<int>wp(p);
	cout << p.use_count() << endl;  //�����1��
	//��Ϊweak_ptr������shared_ptr.���shared_ptr������ʱ��weak_ptr����ָ����ڴ棬��˲���ֱ�ӷ��ʶ���

	weak_ptr<int>wp2 = wp; //������weak_ptr��ֵ����һ��weak_ptr;
	cout << wp.use_count() << endl;  //1
	cout << wp.expired() << endl; //p��use_count()Ϊ0���򷵻�true,���򷵻�false;
	shared_ptr<int>newp = wp.lock();  //wp.lock�����ã����wp.expired()Ϊtrue,�򷵻ؿյ�shared_ptr�����򷵻�һ��ָ��wp��shared_ptr

	weak_ptr<int>wp3(shared_ptr<int>(new int(43)));
	//unique_ptr<int>newup(wp3);    //����ʹ��weak_ptr��ʼ��unique_ptr��

	//������weak_ptr��ʼ��shared_ptr;
	shared_ptr<int>sp2(wp3);
}

int mainUniquePtr()
{
	shared_ptr<int>p(new int(42));
	cout << p.use_count() << endl;
	process(p);
	cout << p.use_count() << endl;

	unique_ptr<int>p2(new int(42));
	auto p3 = p2.release();  //p3�Ǹ�����ָ��
	//shared_ptr<int>p5(p3);
	unique_ptr<int>p4(p3);  //����������ʼ���µ�unique_ptr;�ӹܣ�p3���ڴ汻�ͷ�
	cout << *p4 << endl;
	
	//cout << p5.use_count() << endl;
	//unique_ptr<int>newp(p4); ֱ�ӱ���

	//int* p6 = p4; //���ܿ�����
	//delete p6;  //���޷�ɾ��

	//����
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
	int* p = new int[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9,10 }; //c++ 11������
	//char arr[0]  ����Ǵ����
	char* p2 = new char[0]; // ����ǿ��еģ�����ָ��ֻ��+0 -0,�� ���ܽ����ã�

	//ֻ��unique_ptr�������±����㣬shared_ptrδ�����±ֻ꣬��ͨ��get�������س���ָ������
	unique_ptr<int []>up(new int[10]);
	unique_ptr<int[]>pup(p);  //ʹ������ָ���ʼ��
	shared_ptr<int []>sp(new int[10], [](int* p) { delete[]p; }); //shared_ptr��֧�ֶ�̬�����ֱ�ӹ������봫����Ӧ����������(ɾ����)
	unique_ptr<vector<int> >vup(new vector<int>(10, 1));
	up[3] = 5;  //����
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
	allocator<int>a;  //���ڴ����Ͷ�����ֿ���
	a.allocate(10);  //����10��int������ڴ棬��δ����)

	allocator<string>alloc;
	auto const p = alloc.allocate(10);  //allocate����һ����Ӧ���͵�ָ��

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
		alloc.destroy(--q);    //�����ڴ�
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