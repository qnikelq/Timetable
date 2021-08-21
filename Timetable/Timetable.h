#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <set>

using namespace std;

const string preferCompany = "Posh";

struct Time
{
public:
	int hour;
	int minute;
	Time();
	Time(int inhour, int inminute);
};

class Info
{
public:
	// конструктор с аргументами
	Info(Time inDeparture, Time inArrival, string inName);
	friend bool operator<(const Info& i1, const Info& i2);
	friend void outSet(const set<Info>& inSet, const string& filename);
	Time getDepartureTime() const; // вернуть время отправления
	Time getArrivalTime() const; // вернуть время прибытия
	string getCompanyName() const; // вернуть имя компании
private:
	Time departure;
	Time arrival;
	string companyName;
};

// перегруженный < для Time
bool operator<(const Time& t1, const Time& t2);

// перегруженный > для Time
bool operator>(const Time& t1, const Time& t2);

// перегруженный == для Time
bool operator==(const Time& t1, const Time& t2);

// перегруженный < для Info
bool operator<(const Info& i1, const Info& i2); // оператор для сортировки при заполнении set

// функция определения объекта Info параметрами полученными из строки
Info infCreate(const string& line);

// функция нахождения объекта с тем же временем отправления
set< Info >::iterator findDepTime(const Time& soughtTime, const set <Info>& setForSearch);

// функция нахождения объекта с тем же временем прибытия
set< Info >::iterator findArrivTime(const Time& soughtTime, const set <Info>& setForSearch);

// функция создания и заполнения объектами контейнера set 
set<Info> setCreate(const string& filename);

// функция вывода полей объектов контейнера в файл
void outSet(const set<Info>& inSet, const string& filename);