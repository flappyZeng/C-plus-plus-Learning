#include "StrBlob.h"
#include "Template.h"

StrBlob::StrBlob(std::initializer_list<std::string> il): data(std::make_shared<std::vector<std::string> >(il)) {}

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string> >()) {}

void StrBlob::check(StrBlob::size_type i, const std::string& msg) const
{
	if (i > data->size())
		throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

std::string& StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}
void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->back();
}

std::shared_ptr<std::vector<std::string> > StrBlobPtr::check(std::size_t sz, const std::string& msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if (sz >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}

StrBlobPtr StrBlob::begin() {
	return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this, data->size());
}

std::string& StrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end ");
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
	auto ret =  check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}



