#pragma once
#include<vector>
#include<memory>
#include<ostream>

//��ģ��: ��ģ�岻�����Զ��Ƶ������ʵ����ʱ�����ṩ�����б�
// ��Ҫһ�� ��ģ��Ķ�����ʵ�ֶ�Ҫ��ͷ�ļ���
template<typename T> class BlobPtr;
template<typename T> class Blob;
//���ﲻ֪���ı���
template<typename T> bool operator==(const Blob<T>& lhs, const Blob<T>& rhs);


template<typename T>
class Blob {
public:
	friend class BlobPtr<T>;
	//�����������<T>ȥ����
	friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
	typedef T value_type;
	//�����ĸ�typedef��������ʲô��
	typedef typename std::vector<T>::size_type size_type;

	Blob();
	Blob(std::initializer_list<T> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const T& t) { data->push_back(t); }
	void push_back(const T&& t) { data->push_back(std::move(t)); }
	void pop_back();
	T& front();
	T& back();
	T& operator[](size_type i);

private:
	std::shared_ptr<std::vector<T>>data;
	void check(size_type i, const std::string& msg) const;
};

template<typename T>
class BlobPtr {
public:
	BlobPtr() :curr(0) {}
	BlobPtr(Blob<T>& a, std::size_t sz = 0) :wptr(a.data), curr(sz) {}
	T& deref() const;
	BlobPtr<T>& incr();  //����ָ�����������ָ�����
	bool operator!=(const BlobPtr p) {return this->curr != p.curr;}
	T& operator*() const 
	{
		auto p = check(curr, "dereference past end.");
		return (*p)[curr];
	}
	//��ģ�����еĶ����У�����ʡ��<T>
	BlobPtr<T>& operator++();
	BlobPtr<T>& operator--();

	std::size_t get_curr() const { return curr; }
private:
	std::size_t curr;
	std::weak_ptr<std::vector<T> >wptr;
	std::shared_ptr<std::vector<T> > check(std::size_t sz, const std::string&) const;
};


//����Խ���һ��ģ���ÿ��ʵ������Ϊ�Լ�����Ԫ
template <typename T> class Pal;
class C {
	friend class Pal<C>;
	template<typename T> friend class Pal2;
};
template < typename T> class C2 {
	friend class Pal<T>;
	template<typename X> friend class Pal2; //ʹ��������ģ�屾��ͬ��ģ�����
	friend class Pal3;
};

//���Խ�ģ���������Ϊ��Ԫ C++ 11
template<typename Type> class Bar {
	friend Type;
};


//һ������԰���������ģ��ĳ�Ա���������������Դ�ģ��ĳ�Ա�����������麯��

//һ��������ģ���൫�ǳ�Ա������ģ�庯�����ࣺ
/*
һ��һģһ����֪��Ϊʲô����Ĵ���
class DebugDeleteA {
public:
	DebugDeleteA(std::ostream& s = std::cerr) :os(s) {}
	template<typename T>
	void operator() (T* p) const
	{
		os << "delete unique_ptr" << std::endl;
		delete(p);
	}
private:
	std::ostream os;
};
*/

//ֻ�����ˣ�����������࣬�ɵ�����
class Debugdelete{
public:
	Debugdelete(std::ostream& s = std::cerr) :os(s) {}
	template <typename T> 
	void operator()(T* p) const
	{
		os << "delete unique_ptr" << std::endl;
		delete(p);
	}
private:
	std::ostream& os;
};
// �����������Ա
/*
double *p = new double;
DebugDelete d;
d(p);  //�Զ��Ƶ�T������Ϊdouble������ģ������Զ��Ƶ���������ģ�岻��

//�������ָ����÷���
shared_ptr<int, DebugDeltete> p(new int, DebugDelter());  //shared_ptr�ĵڶ����������Դ����û�ָ����ɾ����

*/

//��������ģ����ĺ���������template��ͷ
template<typename T>
inline Blob<T>::Blob() :data(std::make_shared<std::vector<T> >()) {}
template<typename T>
inline Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T> >(il)) {}

template<typename T>
inline void Blob<T>::pop_back()
{
	check(0, "pop_back on empty Blob");
	data->back();
}

template<typename T>
inline T& Blob<T>::front()
{
	check(0, "front on empty Blob");
	return data->front();
}

template<typename T>
inline T& Blob<T>::back()
{
	check(0, "back on empty Blob");
	return data->back();
}

template<typename T>
inline T& Blob<T>::operator[](size_type i)
{
	check(i, "subscript out of range.");
	return (*data)[i];
}

template<typename T>
inline void Blob<T>::check(size_type i, const std::string& msg) const
{
	if (i > data->size())
		throw std::out_of_range(msg);
}


template<typename T>
inline T& BlobPtr<T>::deref() const
{
	return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::incr()
{
	check(curr, "maxium curr");
	curr++;
	return *this;
}

template<typename T>
inline BlobPtr<T>& BlobPtr<T>::operator++()
{
	BlobPtr ret = *this;
	++* this;
	return ret;
	// TODO: �ڴ˴����� return ���
}

template<typename T>
inline BlobPtr<T>& BlobPtr<T>::operator--()
{
	--* this;
	return *this;
	// TODO: �ڴ˴����� return ���
}

template<typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t sz, const std::string& msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if (sz >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}


template<typename T> 
bool operator==(const Blob<T>&lhs, const Blob<T>&rhs) {
	return equal(lhs.data.begin(), lhs.data.end(), rhs.data.begin(), rhs.data.end());
}


template<typename T>
void print(T& t)
{
	for (typename T::size_type i = 0; i <  t.size(); ++i)
		std::cout << T[i] << std::endl;
}

template<typename T>
void printItr(T& t)
{
	for (auto it = t.begin(); it != t.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

//ʹ��extern template declaration �������Է�ֹ�������ڶ���ļ��ж�����ͬ��ģ�壬��������ڴ���˷�
