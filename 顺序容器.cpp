//����vector ,deque(˫�˶���)��list��˫������)��
//forward_list(��������)��array(�̶���С����)��string

#include<iostream>
#include<vector>
#include<list>
#include<array>
#include<queue>
#include<string>
#include<forward_list>

using std::cin;
using std::cout;
using std::endl;


void testOrderCap()
{
	std::vector<int>vc(10, 5);  //vector
	std::list<int>ls(10, 5); //list, list�Լ�forward_listû���������
	std::forward_list<int>fls(10, 5); // û��size()��������֧�ַ��������
	std::deque<int>dq(10, 5);  //˫�˶���
	std::array<int, 10>arr{ 1, 2, 3 }; //������û���������ʼ��Ϊ0�������ſ����б��ʼ���� �����ܴ�С����
	std::string s(10, 's');
	std::list< std::deque<int> >dqls;
	//for (auto& item : dq)
		//cout << item << endl;
	std::vector<int>::iterator iter = vc.begin();
	while (iter < vc.end())  //����������Ҫ��ͬһ����������
	{
		cout << *iter << " ";
		iter++;
	}
	std::vector<int>::reference it = vc[0]; // ����
	cout << endl;

}

void special_act()
{
	std::forward_list<int>fls(10, 0);
	std::forward_list<int>::iterator it = fls.end();
	//it--����forward_list�ĵ��������ܵݼ���
	fls.insert_after(fls.before_begin(), 1);
	fls.emplace_after(fls.begin(),1);
	fls.emplace_front(100);
	fls.erase_after(fls.begin());
	for (auto f : fls)
		cout << f << endl;

}

void test_queue()
{
	std::string  s;
	std::deque<std::string>dq;
	std::list<std::string>ls;
	while (cin >> s)
	{
		ls.push_back(s);
		dq.push_back(s);
	}

	std::deque<std::string>::iterator qiter = dq.begin();
	for (; qiter != dq.end(); ++qiter)
		cout << *qiter << " ";
	cout << endl;

	std::list<std::string>::iterator liter = ls.begin();
	for (; liter != ls.end(); ++liter)
	{
		cout << *liter << " ";
	}
	cout << endl;
}

void  copeListToQueue(std::list<int>& ls, std::deque<int>& qo, std::deque<int>& qe)
{
	for (auto& i : ls)
	{
		if (i % 1)
			qo.push_back(i);
		else
			qe.push_back(i);
	}
}
void vec_test()
{
	std::vector<int>a(10, 1);
	std::vector<int>b(5, 2);
	std::vector<int>c(7, 4);
	a = b;                    //���������b�滻��a��aԭ�е����ݽ���Ĩȥ��
	a = {1, 2, 3 ,4, 5, 6};
	a.swap(c);				  //����b��c�ڵ�Ԫ��
	c.assign(b.begin(), b.end());  //��c�ڵ�Ԫ���滻Ϊb������Ԫ�أ�
	c.assign({ 1, 2, 3, 4, 5 });   //�滻c
	c.assign(10, 6); //c��Ԫ���滻Ϊ10��6��
	//��������һ�㲻������array�Լ���������
	for (auto& num : a)
		cout << num << endl;
}

void test_capacity()
{
	std::vector<int>vc;
	for (int i = 0; i < 100; ++i)
	{
		vc.push_back(i);
		cout << vc.size() << " " << vc.capacity() << endl;
		//capacity:  10 -> 13 -> 19 -> 28 -> 42 -> 63 -> 94 -> 141
	}
}

void C9T39()
{
	std::vector<std::string> svec;
	svec.reserve(1024);
	cout << svec.size() << " " << svec.capacity() << endl;
	std::string word;
	while (cin >> word)
	{
		svec.push_back(word);
	}
	cout << svec.size() << " " << svec.capacity() << endl;
	svec.resize(svec.size() + svec.size() / 2);
	cout << svec.size() << " " << svec.capacity() << endl;
}

void C9T41()
{
	std::vector<char>vcch = { 'H', 'e', 'l','l','o', ' ', 'w','o', 'r', 'l', 'd' };
	std::string s(vcch.begin() ,vcch.end());
	cout << s << endl;
}

void C9T43(std::string& s, std::string oldVal , std::string newVal)
{
	size_t len = oldVal.size();
	std::string::iterator it = s.begin();
	for (; it != s.end(); ++it)
	{
		if (s.substr(it - s.begin(), len) == oldVal)
		{
			//ʹ��replace --> s.replace(it, it + len, newVal);
			s.erase(it, it + len);
			s.insert(it - s.begin(), newVal);
		}

	}
}

std::string C9T45(const std::string& name,const std::string& pre,const std::string& last)
{
	std::string ret(name);
	ret.insert(0, pre);
	//ret.insert(ret.end() - ret.begin(), last);
	ret.append(last);
	return ret;
}

std::vector<std::string> findNumWord(const std::string& str)
{
	std::string nums = "01234568789";
	std::string num;
	std::string word;
	std::string::size_type pos = 0;
	while ((pos = str.find_first_of(nums, pos)) != std::string::npos)
	{
		num += str[pos];
		pos++;
	}
	pos = 0;
	while ((pos = str.find_first_not_of(nums, pos)) != std::string::npos)
	{
		word += str[pos];
		pos++;
	}
	return { num, word };
}

std::string C9T49(const std::string& word)
{
	//std::string up("bdfhkl");
	//std::string down("gjpqy");
	std::string except("bdfhklgjpqy");
	std::string::size_type max_pos = -1;
	std::string::difference_type len = 0;
	std::string::size_type pos = 0, newpos = 0;
	while((newpos = word.find_first_of(except, pos + 1)) != std::string::npos)
	{
		if (static_cast<int>(newpos - pos - 1) > len)
		{
			max_pos = pos + 1;
			len = newpos - pos - 1;
		}
		//cout << pos << " " << newpos << endl;
		pos = newpos;
	}
	//cout << max_pos << " " << len << endl;
	if (max_pos != -1)
		return word.substr(max_pos, len);
	else
		return "";
}

int mainSeq()
{
	//C9T39();
	//C9T41();
	//test_capacity();
	//special_act();
	//testOrderCap();

	/*
	std::string s = "thosssthoththofdsfskf";
	std::string oldval = "tho";
	std::string newval = "though";
	C9T43(s, oldval, newval);
	cout << s << endl;
	*/
	//cout << C9T45("Ming", "Mr.", "Li") << endl;
	//cout << std::string::npos << endl;  //unsigned int ֵ����ʾINT_MAX * 2 - 1
	
	//auto vec = findNumWord("ab2c3d7R4E6");
	//for (auto& v : vec)
	//	cout << v << " ";
	//cout << endl;
	cout << C9T49("dfaaaaaaaaaayy");
	return 0;
}