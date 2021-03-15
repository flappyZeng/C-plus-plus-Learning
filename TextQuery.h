#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>  //使用istringstream必须包含sstream头文件
#include<map>
#include<set>
#include<memory>  //提供智能指针 shared_ptr;
#include"StrBlob.h"


class TextQuery;
class TextQueryWithStrBlob;

class QueryResult {
public:
	using line_no = std::size_t;
	friend std::ostream& print(std::ostream& os, const QueryResult& query_result);
	QueryResult(std::string s, std::shared_ptr<std::set<line_no> > p, std::shared_ptr<std::vector<std::string>>f) :sought(s), lines(p), file(f) {};
	auto begin() { return lines->begin(); }
	auto end() { return lines->end(); }
	auto get_file() const { return file; }
	//QueryResult(const QueryResult& QR) : sought(QR.sought), file(QR.file), lines(QR.lines) {}
private:
	std::string sought;
	std::shared_ptr<std::vector<std::string> >file;
	std::shared_ptr<std::set<line_no>>lines;
};

class QueryResultWithSrBlob {
public:
	using line_no = std::size_t;
	friend std::ostream& print(std::ostream& os, const QueryResultWithSrBlob& query_result);
	QueryResultWithSrBlob(std::string s, std::shared_ptr<std::set<line_no> > p, std::shared_ptr<StrBlob>f) :sought(s), lines(p), file(f) {};
private:
	std::string sought;
	std::shared_ptr<StrBlob>file;
	std::shared_ptr<std::set<line_no>>lines;
};

class TextQuery {
public:
	using line_no = std::size_t;
	using filep = std::shared_ptr<std::vector<std::string>>;
	using wsetp = std::shared_ptr<std::set<line_no> >;
	using wmp = std::map<std::string, std::shared_ptr<std::set<line_no> >>;
	//TextQuery(const TextQuery& T) :file(T.file), wm(T.wm) {} 不需要，因为都是智能指针
	TextQuery(std::ifstream& infile);
	QueryResult query(const std::string& s) const;

private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no> >> wm;

};
class TextQueryWithStrBlob {
public:
	using line_no = std::size_t;
	using filep = std::shared_ptr<StrBlob>;
	using wsetp = std::shared_ptr<std::set<line_no> >;
	using wmp = std::map<std::string, std::shared_ptr<std::set<line_no> >>;
	TextQueryWithStrBlob(std::ifstream& infile);
	QueryResultWithSrBlob query(std::string& s);

private:
	std::shared_ptr<StrBlob> file;
	std::map<std::string, std::shared_ptr<std::set<line_no> >> wm;
};


std::string make_plural(size_t ctr, const std::string& word, const std::string& end);
void runQueries(std::ifstream& infile);

#endif // !TEXTQUERY_H



