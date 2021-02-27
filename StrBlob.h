#ifndef STRBLOB_H
#define STRBLOB_H

#pragma once
#include"Base.h"
#include<memory>

class StrBlobPtr;

class StrBlob {
public:
	friend class StrBlobPtr;
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();   //无参数构造函数
	StrBlob(std::initializer_list<std::string> il); //构造函数

	size_type size()  const { return data->size(); } //返回元素个数
	bool empty() const { return data->empty(); }

	void push_back(const std::string& s) { data->push_back(s); }
	void pop_back();

	//元素的访问
	std::string& front();
	std::string& back();

	StrBlobPtr begin();
	StrBlobPtr end();

private:
	std::shared_ptr<std::vector<std::string>>data;
	void check(size_type i, const std::string& msg) const;
};


class StrBlobPtr {
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob& a, size_t sz = 0) :wptr(a.data), curr(sz) {}
	std::string& deref() const;
	StrBlobPtr& incr();  //增加指针计数，即将指针后移
	bool operator!=(const StrBlobPtr p)
	{
		return this->curr != p.curr;
	}

	size_t get_curr() const { return curr; }
private:
	std::size_t curr;
	std::weak_ptr<std::vector<std::string> >wptr;
	std::shared_ptr<std::vector<std::string> > check(std::size_t sz, const std::string&) const;
};


// initializer_list<TypeName>

#endif // STRBOLOB_H

