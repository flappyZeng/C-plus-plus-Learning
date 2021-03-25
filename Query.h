#pragma once
#include"TextQuery.h"
class WordQuery;
class Query;
/*

			  WordQuery
           ↗ 
Query_base → NotQuery      AndQuery
		   ↘             ↗
			  BinaryQuery
						  ↘	
							OrQuery
*/  
//Query_base
class Query_base {
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;

private:
	virtual QueryResult eval(const TextQuery&) const = 0;
	virtual std::string rep() const = 0;
};


//Query
class Query
{
	//构造友元函数的原因是因为需要访问Query的私有构造函数
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const std::string& s);
	QueryResult eval(const TextQuery& t) const { return q->eval(t); }
	std::string rep() const { return q->rep(); }
	
private:
	Query(std::shared_ptr<Query_base>query):q(query) {};
	std::shared_ptr<Query_base>q;
};


//WordQuery
class WordQuery : public Query_base {
public:
	friend class Query;
	WordQuery(const std::string& s) : query_word(s) { /*std::cout << "调用WordQuery的构造函数" << std::endl; */};
	QueryResult eval(const TextQuery& t) const { return t.query(query_word); }
	std::string rep() const { return query_word; }
	std::string query_word;
};


//NotQuery
class NotQuery : public Query_base {
public:
	friend Query operator~(const Query& );
	NotQuery(const Query& q) : query(q) {};
	std::string rep() const { return "~(" + query.rep() + ")"; }
	QueryResult eval(const TextQuery&) const;

	Query query;
};
inline Query operator~(const Query& operand)
{
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}


//BinaryQuery
//也是一个抽象基类，因为其继承了Query_base的纯虚函数eval而没有实现
class BinaryQuery : public Query_base {
protected:
	Query lhs, rhs;
	std::string opSym;

	BinaryQuery(const Query& l, const Query& r, std::string s) :
		lhs(l), rhs(r), opSym(s) {}
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
};


//AndQuery
class AndQuery : public BinaryQuery {
public:
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query& l, const Query& r):BinaryQuery(l, r, "&") {}
	QueryResult eval(const TextQuery&) const;
	//不需要重新定义rep；
};
inline Query operator&(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}


//OrQuery
class OrQuery : public BinaryQuery {
public:
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query& l, const Query& r) :BinaryQuery(l, r, "|") {}
	QueryResult eval(const TextQuery&) const;
	//不需要重新定义rep；
};
inline Query operator|(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
std::ostream& operator<<(std::ostream& os, const Query& query);



