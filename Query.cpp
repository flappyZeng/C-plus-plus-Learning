#include "Query.h"
#include<iterator>

std::ostream& operator<<(std::ostream& os, const Query& query)
{
	return os << query.rep();
	// TODO: �ڴ˴����� return ���
}

Query::Query(const std::string& s) : q(new WordQuery(s)) { }//std::cout << "����Query�Ĺ��캯��" << std::endl; };

QueryResult OrQuery::eval(const TextQuery& text) const
{
	//�ֱ��ȡ��Ӧlhs��rhs�ļ��кŵĵ�����
	auto right = rhs.eval(text), left = lhs.eval(text);
	//����shared_ptr�洢left��Ӧ��set
	auto ret_lines = std::make_shared<std::set<line_no> >(left.begin(), left.end());
	//��right�еĴ洢���кŲ����Ӧ��set
	ret_lines->insert(right.begin(), right.end());
	//����һ���µ�queryResult������
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
	//��׼���󽻼��ĺ��� set_intersection;
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), ret_lines, left.get_file());
}
