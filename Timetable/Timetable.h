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
	// ����������� � �����������
	Info(Time inDeparture, Time inArrival, string inName);
	friend bool operator<(const Info& i1, const Info& i2);
	friend void outSet(const set<Info>& inSet, const string& filename);
	Time getDepartureTime() const; // ������� ����� �����������
	Time getArrivalTime() const; // ������� ����� ��������
	string getCompanyName() const; // ������� ��� ��������
private:
	Time departure;
	Time arrival;
	string companyName;
};

// ������������� < ��� Time
bool operator<(const Time& t1, const Time& t2);

// ������������� > ��� Time
bool operator>(const Time& t1, const Time& t2);

// ������������� == ��� Time
bool operator==(const Time& t1, const Time& t2);

// ������������� < ��� Info
bool operator<(const Info& i1, const Info& i2); // �������� ��� ���������� ��� ���������� set

// ������� ����������� ������� Info ����������� ����������� �� ������
Info infCreate(const string& line);

// ������� ���������� ������� � ��� �� �������� �����������
set< Info >::iterator findDepTime(const Time& soughtTime, const set <Info>& setForSearch);

// ������� ���������� ������� � ��� �� �������� ��������
set< Info >::iterator findArrivTime(const Time& soughtTime, const set <Info>& setForSearch);

// ������� �������� � ���������� ��������� ���������� set 
set<Info> setCreate(const string& filename);

// ������� ������ ����� �������� ���������� � ����
void outSet(const set<Info>& inSet, const string& filename);