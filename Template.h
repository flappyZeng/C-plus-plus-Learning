#pragma once
#include<vector>
#include<memory>
#include<ostream>

//类模板: 类模板不存在自动推导，因此实例化时必须提供参数列表
// 重要一点 ：模板的定义与实现都要在头文件中
template<typename T> class BlobPtr;
template<typename T> class Blob;
//这里不知名的报错
template<typename T> bool operator==(const Blob<T>& lhs, const Blob<T>& rhs);


template<typename T>
class Blob {
public:
	friend class BlobPtr<T>;
	//这里我下面把<T>去掉了
	friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
	typedef T value_type;
	//下面哪个typedef的作用是什么？
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
	BlobPtr<T>& incr();  //增加指针计数，即将指针后移
	bool operator!=(const BlobPtr p) {return this->curr != p.curr;}
	T& operator*() const 
	{
		auto p = check(curr, "dereference past end.");
		return (*p)[curr];
	}
	//在模板类中的定义中，可以省略<T>
	BlobPtr<T>& operator++();
	BlobPtr<T>& operator--();

	std::size_t get_curr() const { return curr; }
private:
	std::size_t curr;
	std::weak_ptr<std::vector<T> >wptr;
	std::shared_ptr<std::vector<T> > check(std::size_t sz, const std::string&) const;
};


//类可以将另一个模板的每个实例声明为自己的友元
template <typename T> class Pal;
class C {
	friend class Pal<C>;
	template<typename T> friend class Pal2;
};
template < typename T> class C2 {
	friend class Pal<T>;
	template<typename X> friend class Pal2; //使用了与类模板本身不同的模板参数
	friend class Pal3;
};

//可以将模板参数声明为友元 C++ 11
template<typename Type> class Bar {
	friend Type;
};


//一个类可以包含自身是模板的成员函数，但是这种自带模板的成员函数不能是虚函数

//一个本身不是模板类但是成员函数是模板函数的类：
/*
一段一模一样不知道为什么报错的代码
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

//只重载了（）运算符的类，可调用类
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
// 调用上述类成员
/*
double *p = new double;
DebugDelete d;
d(p);  //自动推到T的类型为double，函数模板可以自动推到，但是类模板不行

//结合智能指针的用法：
shared_ptr<int, DebugDeltete> p(new int, DebugDelter());  //shared_ptr的第二个参数可以传递用户指定的删除器

*/

//定义在类模板外的函数必须以template开头
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
	// TODO: 在此处插入 return 语句
}

template<typename T>
inline BlobPtr<T>& BlobPtr<T>::operator--()
{
	--* this;
	return *this;
	// TODO: 在此处插入 return 语句
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

//使用extern template declaration 声明可以防止编译器在多个文件中定义相同的模板，避免造成内存的浪费
