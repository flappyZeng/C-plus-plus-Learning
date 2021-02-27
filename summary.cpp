#include<iostream>
#include"TextQuery.h"

using namespace std;

int mainCountWord()
{
	ifstream in_file("C:\\Users\\Administrator\\Desktop\\words.txt");
	runQueries(in_file);
	return 0;
}