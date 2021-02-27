#include"Base.h"
#include<map>  //map、multimap
#include<set>  //set、multiset
#include<iterator>
#include<fstream>
#include<unordered_map>
#include<cctype> //tolower函数以及ispunc函数  判断是不是符号
#include<unordered_set>
#include<utility>  //pair ，为什么不需要include也可以用pair
#include"Sales_data.h"

using namespace std;

bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs)
{
	return lhs.isbn() < rhs.isbn();
}

void wordCount()
{
	map<string, int>count;
	set<string>words;
	istream_iterator<string>in_iter(cin), eof;
	while (in_iter != eof)
	{
		if (words.find(*in_iter) != words.end())
		{
			count[*in_iter] ++;
		}
		else
		{
			count[*in_iter] = 1;
			words.emplace(*in_iter); 
		}
			
		in_iter++;
	}
	for (auto& item : count)
		cout << item.first << " " << item.second << endl;
}

void wordsCount()
{
	string word;
	const string inFileName = "C:\\Users\\Administrator\\Desktop\\words.txt";
	set<string>except = { "The", "but", "And", "Or", "An", "A", "the", "but", "and", "or", "an", "a" };
	map<string, size_t>word_count;
	ifstream in(inFileName);
	istream_iterator<string>in_iter(in), eof;
	ostream_iterator<string>out_iter(cout, " ");
	ostream_iterator<size_t>out_count_iter(cout, "\n");
	while (in_iter != eof)
	{
		word = *in_iter++;
		
		string::iterator it_str = word.begin();
		for (; it_str != word.end(); ++it_str)
		{
			if (isalpha(*it_str))
				*it_str = tolower(*it_str);
		}
		word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());

		if (except.find(word) == except.end())
		{
			word_count[word] ++;
		}
	}
	
	word_count.erase(word_count.begin());
	
	for (pair<const string, size_t>& pr : word_count)
	{
		*out_iter++ = pr.first;
		*out_count_iter++ = pr.second;
	}
	map<string, size_t>::iterator item = word_count.begin();
}

void pairTest()
{
	vector<pair<string, int> >pr_save;
	string temps;
	int tempi;
	while (cin >> temps >> tempi)
	{
		//pr_save.emplace_back(make_pair(temps, tempi));
		pair<string, int>pr(temps, tempi);
		pair<string, int>pr2 = { temps, tempi };
		pair<string, int>pr3 = make_pair(temps, tempi);
		pr_save.push_back(pr2);
	}
}

//关联容器中的类型别名
void TypeDefName()
{
	set<string>::key_type v1; //v1是一种string类型
	set<string>::value_type v2; //v2也是一种string类型
	map<string, int>::key_type v3; //v3是一种string类型
	map<string, int>::mapped_type v4 = 0; //v4是一种int类型

	//重要的区分
	map<string, int>::value_type v5; // v5是一种pair<const string, int>类型！！1

	map<int, vector<int> >::key_type v6 = 0;  //int类型
	map<int, vector<int> >::mapped_type v7; // vector<int>类型
	map<int, vector<int> >::value_type v8; // pair<const int, vector<int>>类型
}

void Iterator()
{
	set<int>st = { 1, 2, 3, 4, 5, 6, 7,8, 9, 10 };
	// set不能使用push_back;
	for (auto it = st.begin(); it != st.end(); ++it)
	{
		cout << *it << " ";
		//*it = 10;  这是错误的，set的迭代器都是const的，不可改变
	}

	map<int, int>mp = { {1, 2}, {3, 4}, {5, 6}, {7, 8} };
	for (auto it = mp.begin(); it != mp.end(); ++it)
	{
		cout << (*it).first << " " << (*it).second << endl;
		//it->first = 10; 这是错误的，map的迭代器不可以改变键值
		it->second = 20;  //但是可以改变value
	}
		
}

void C11T17()
{
	vector<string>vs1 = { "sdfs", "fdsfs", "fsdf", "sdfs ", "fsdf" };
	vector<string>vs2;

	multiset<string>ss1 = { "sdfs", "fdsfs", "fsdf", "sdfs ", "fsdf" };
	multiset<string>ss2;

	copy(vs1.begin(), vs1.end(), inserter(ss2, ss2.end()));
	//copy(vs1.begin(), vs1.end(), back_inserter(ss2)); //报错， set不能使用inserter,因为需要调用push_back
	copy(ss1.begin(), ss1.end(), inserter(vs2, vs2.end()));
	copy(ss1.begin(), ss1.end(), back_inserter(vs2));

	for (auto item : vs2)
		cout << item << " ";
	cout << endl;

	for (auto item : ss2)
		cout << item << " ";
	cout << endl;
}

void C11T19()
{
	multiset < Sales_data,  bool(*)(const Sales_data &,  const Sales_data & rhs) > bookstoref(compareIsbn);
	multiset<Sales_data, decltype(compareIsbn)* >bookstore(compareIsbn);  //自定义排序函数，传入函数指针
	decltype(compareIsbn) s;
	multiset<Sales_data>::iterator item = bookstore.begin();
}

void C11T27(const string& Auther)
{
	//T28
	map<string, int>mp = { {"aaa", 1}, {"dad", 2} };
	map<const string, int>::iterator ret = mp.find("daa");
	
	//T29
	//返回对应容器的end()迭代器

	//T30
	//pos返回一个pair类型的值，--> pair< multimap<const string, string>::iterator first, multimap<const string, string>::iterator second>  [first,second)分别表示的对应的寻找到的元素的区间范围
	//每一个first指向一个multimap<string, string>::value_type的元素，first->second表示对应的键值

	//T31
	multimap<string, string>AutherandBooks = { {"Harry","BEBE"}, {"Bob", "SIDN"}, {"Harry", "SSFF"}, {"Cindy", "Diisi"} };
	//auto ret = AutherandBooks.find(Auther);
	decltype(AutherandBooks.find(Auther)) it = AutherandBooks.begin();
	int count = AutherandBooks.count(Auther);
	if(count)
	{
		AutherandBooks.erase(Auther);
	}

	//T35  map下标操作和insert操作的区别
	mp["aaa"] = 3;   //会修改键值
	mp.insert({ "aaa", 3 });  //不会修改键值


}
size_t hasher(const Sales_data& sd)
{
	return hash<string>()( sd.isbn() );
}
bool eqOp(const Sales_data& lhs, const Sales_data& rhs)
{
	return lhs.isbn() == rhs.isbn();
}

//无序关系容器
void unordered_container()
{
	unordered_map<int, int>mp = { {1, 2}, {2 , 3}, {3, 4}, {4, 5}, {5, 6} };
	cout << mp.bucket_count() << endl;
	cout << mp.max_bucket_count() << endl;
	cout << mp.bucket_size(1) << endl;
	cout << mp.bucket(100000) << endl;

	for (auto it = mp.begin(mp.bucket(3)); it != mp.end(mp.bucket(3)); ++it)  //遍历3所在的桶的元素
		cout << it->first << " " << it->second << endl;
	cout << mp.load_factor() << endl;  //每个桶的平均元素数量，double
	cout << mp.max_load_factor() << endl;  //平均桶大小，当mp.load_factor接近该值时，会增加桶的数量  --> 1
	mp.rehash(100); //重新存储,使得mp.bucket_count >= n 且bucket_count > size/ max_load_factor

	using SD_multiset = unordered_multiset<Sales_data, decltype(hasher)*, decltype(eqOp)*>;
	SD_multiset bookstore(42, hasher, eqOp);  //定义桶大小， hash函数以及比较函数
	bookstore.insert(Sales_data("123"));
	bookstore.insert(Sales_data("456"));
	bookstore.insert(Sales_data("123"));
	for (auto& item : bookstore)
		print(cout, item);
 }

int mainmp()
{
	//wordsCount();
	pair<int, int>pr;   //定义在头文件utility中
	//C11T17();
	map<int, int>mp;
	vector<pair<int, int> >vcp = { { {1, 2}, {3, 4}, {5, 6}, {7, 8} } };
	mp.insert(vcp.begin(), vcp.begin() + 3);
	mp.emplace(make_pair(1, 2 ));
	for (pair<const int, int>& item : mp)
		cout << item.first << " " << item.second << endl;
	
	//如果存在，则什么都不干，而不是更新mapped_value值
	auto it = mp.insert({ 1, 2 });  //插入值的迭代器与是否插入成功组成的pair --> pair< pair<const int, int>::iterator, bool>
	auto it1 = mp.insert({ 1, 2 });
	cout << it.first ->first << " "  << it.second << endl;
	cout << it1.first -> first << " "  << it1.second << endl;

	map<string, vector<int> >mpsv;
	auto ret = mpsv.insert({ "myword", {1, 2} });
	//ret.first->first = "abc";  //map是不能更改键值的
	try {
		cout << mpsv.at("myword")[0] << endl;  //masv.at()返回的是一个mapped_type对象，也就是对应的键值
	}catch(exception error)
	{
		cout << error.what() << endl;
	}
	
	const map< string, int>cmpsi;  //const类型的map就不能插入或者使用at以及下标操作了
	const map<string, int>cmpsi2 = { {"abc", 1}, {"cde", 2}, {"efg", 3} };
	//cmpsi2["abc"] = 1 ，这个操作不允许;
	cout << cmpsi2.at("cde") << endl;  //允许

	map<int, int>test = { {1, 2}, {2, 3}, {3, 4}, {4, 5} };
	auto retii = test.find(2);   //返回对应值的迭代器
	cout << retii->first << " " << retii->second << endl;
	auto retii2 = test.count(2);  //返回int值
	cout << retii2 << endl;
	auto retii3 = test.lower_bound(3);  //返回第一个大于等于3的元素的迭代器
	cout << retii3->first << " " << retii3->second << endl;
	auto retii4 = test.upper_bound(3);  //返回第一个大于3的元素的迭代器
	cout << retii4->first << " " << retii4->second << endl;
	auto retii5 = test.equal_range(3); //返回一个迭代器区间[a, b)，表示等于k的元素的范围
	cout << "retii5的返回值： " << endl;
	cout << retii5.first->first <<" " <<  retii5.first->second << endl;
	cout << retii5.second->first <<" " <<  retii5.second->second << endl;
	return 0;
}

int mainMAP()
{
	string name;
	string value;
	/*while (cin >> name && getline(cin, value))  //这样子会有一个空格
	{
		cout << "name:" << name << endl;
		cout << "value:" << value << endl;
	}
	*/
	unordered_container();
	return 0;
}