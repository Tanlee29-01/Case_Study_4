#include "DataTypes.h"
#include <iostream>
#include <iomanip>
using namespace std;

/*
============================
 --- Cài đặt Time ---
============================
*/
Time::Time(int h, int minu) : Hours(h), Minutes(minu)
{
}

bool Time::operator<(const Time& other) const
{
	if (Hours != other.Hours)
	{
		return Hours < other.Hours;
	}
	return Minutes < other.Minutes;
}

bool Time::operator>(const Time& other) const
{
	return other < *this;
}

bool Time::operator==(const Time& other) const
{
	return Hours == other.Hours && Minutes == other.Minutes;
}



Time::~Time()
{
}

ostream& operator<<(ostream& os, const Time& t)
{
	os << setfill('0') << setw(2) << t.Hours << ":"
		<< setfill('0') << setw(2) << t.Minutes;
	return os;
}

/*
============================
 --- Cài đặt LopHoc ---
============================
*/
void Class::show_infor() const
{
   cout << "  - Ma mon:    " << Sub_id << "\n"
		<< "  - Ten mon:   " << Sub_name << "\n"
		<< "  - Thoi gian: " << Start_Time << "\n"
		<< "  - Giang vien: " << Teacher_name << "\n"
		<< "  - So tin chi: " << Credits << endl;
}

Class::Class(string id, string name, Time t, string tch_name, int cre) 
	  : Sub_id(id), Sub_name(name), Start_Time(t), Teacher_name(tch_name), Credits(cre) {}

Class::~Class()
{
}
