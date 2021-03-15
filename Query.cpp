#include "Query.h"
#include<iterator>

std::ostream& operator<<(std::ostream& os, const Query& query)
{
	return os << query.rep();
	// TODO: 在此处插入 return 语句
}

Query::Query(const std::string& s) : q(new WordQuery(s)) { }//std::cout << "调用Query的构造函数" << std::endl; };

QueryResult OrQuery::eval(const TextQuery& text) const
{
	//分别获取对应lhs，rhs文件行号的迭代器
	auto right = rhs.eval(text), left = lhs.eval(text);
	//构造shared_ptr存储left对应的set
	auto ret_lines = std::make_shared<std::set<line_no> >(left.begin(), left.end());
	//将right中的存储的行号插入对应的set
	ret_lines->insert(right.begin(), right.end());
	//构建一个新的queryResult并返回
	return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult NotQuery::eval(const TextQuery& text) const
{
	auto result = query.eval(text);
	auto ret_lines = std::make_shared < std::set<line_no>>();
	auto beg = result.begin(), end = result.end();
	auto sz = result.get_file()->size();
	for (std::size_t n = 0; n < sz; ++n)
	{
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}

QueryResult AndQuery::eval(const TextQuery& text) const
{
	auto left = lhs.eval(text), right = rhs.eval(text);
	auto ret_lines = std::make_shared<std::set<line_no> >();
	//标准库求交集的函数 set_intersection;
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), ret_lines, left.get_file());
}
