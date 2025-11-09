#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Time
{
public:
	int Hours;
	int Minutes;

	Time(int h = 0,int minu = 0);
	~Time();
	//Cài đặt toán tử <
	bool operator<(const Time& other) const;
	//Cài đặt toán tử >
	bool operator>(const Time& other) const;// Có thể không cần cũng đc
	//Cài đặt toán tử bằng
	bool operator==(const Time& other) const;
	//Bổ trợ chi việc in ra ví dụ 8:50 thay vì 8:5
	friend ostream& operator<<(ostream& os, const Time& t);
	
};

class Class
{
public:
	string Sub_id;
	string Sub_name;
	Time Start_Time;
	string Teacher_name;
	int Credits;

	Class(string id,string name,Time t, string tch_name,int cre);
	~Class();
	void show_infor() const;
	
};