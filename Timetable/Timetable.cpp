#include "Timetable.h"

using namespace std;
Time::Time()
{
	hour = 0;
	minute = 0;
}

Time::Time(int inhour, int inminute)
{
	hour = inhour;
	minute = inminute;
}

Info::Info(Time inDeparture, Time inArrival, string inName) :
	departure(inDeparture),
	arrival(inArrival),
	companyName(inName)
{ }

Time Info::getDepartureTime() const // вернуть время отправления
{
	return departure;
}

Time Info::getArrivalTime() const // вернуть время прибытия
{
	return arrival;
}

string Info::getCompanyName() const // вернуть имя компании
{
	return companyName;
}


// перегруженный < для Time
bool operator<(const Time& t1, const Time& t2)
{
	if (t1.hour == t2.hour)
	{
		return (t1.minute < t2.minute) ? true : false;
	}
	return (t1.hour < t2.hour) ? true : false;
}

// перегруженный > для Time
bool operator>(const Time& t1, const Time& t2)
{
	if (t1.hour == t2.hour)
	{
		return (t1.minute > t2.minute) ? true : false;
	}
	return (t1.hour > t2.hour) ? true : false;
}

// перегруженный == для Time
bool operator==(const Time& t1, const Time& t2)
{
	return ((t1.hour == t2.hour) && (t1.minute == t2.minute)) ? true : false;
}

// перегруженный < для Info
bool operator<(const Info& i1, const Info& i2) // оператор для сортировки при заполнении set
{
	if (i1.companyName == i2.companyName)
	{
		return (i1.departure < i2.departure) ? true : false;
	}
	return (i1.companyName == preferCompany && i2.companyName != preferCompany) ? true : false;
}

// функция определения объекта Info параметрами полученными из строки
Info infCreate(const string& line)
{
	int departureHour;
	int departureMin;
	int arrivalHour;
	int arrivalMin;
	char companyName[50];
	sscanf(line.c_str(), "%s\t%d:%d\t%d:%d", companyName, &departureHour, &departureMin, &arrivalHour, &arrivalMin);
	Info inf = Info(Time(departureHour, departureMin), Time(arrivalHour, arrivalMin), companyName);
	return inf;
}

set< Info >::iterator findDepTime(const Time& soughtTime, const set <Info>& setForSearch)
{
	for (auto it = setForSearch.begin(); it != setForSearch.end(); )
	{
		Time departure = it->getDepartureTime();
		if (departure == soughtTime)
		{
			return it;
		}
		else
		{
			it++;
		}
	}
	return setForSearch.end();
}

set< Info >::iterator findArrivTime(const Time& soughtTime, const set <Info>& setForSearch)
{
	for (auto it = setForSearch.begin(); it != setForSearch.end(); )
	{
		Time arrival = it->getArrivalTime();
		if (arrival == soughtTime)
		{
			return it;
		}
		else
		{
			it++;
		}
	}
	return setForSearch.end();
}


set<Info> setCreate(const string& filename)
{
	ifstream fileToRead;
	fileToRead.open(filename);
	set<Info> infoSet;
	string line;
	if (fileToRead.is_open())
	{
		while (getline(fileToRead, line))
		{
			Info newInf = infCreate(line);
			Time newDepTime = newInf.getDepartureTime();
			Time newArrivTime = newInf.getArrivalTime();
			string newCompName = newInf.getCompanyName();
			if ((((newArrivTime.hour) * 60 + newArrivTime.minute) - ((newDepTime.hour) * 60 + newDepTime.minute)) > 60)
			{
				continue;
			}
			set< Info >::iterator iter = findDepTime(newDepTime, infoSet);
			if (iter != infoSet.end())
			{
				Info inf = *iter;
				if ((newArrivTime < inf.getArrivalTime()) || (newArrivTime == inf.getArrivalTime() && newCompName == preferCompany && inf.getCompanyName() != preferCompany))
				{
					infoSet.erase(iter);
					infoSet.emplace(newInf);
				}
				continue;
			}
			iter = findArrivTime(newArrivTime, infoSet);
			if (iter != infoSet.end())
			{
				Info inf = *iter;
				if (newDepTime > inf.getDepartureTime())
				{
					infoSet.erase(iter);
					infoSet.emplace(newInf);
				}
				continue;
			}
			infoSet.emplace(newInf);
		}
	}
	fileToRead.close();
	return infoSet;
}

// функция вывода полей объектов контейнера в файл
void outSet(const set<Info>& inSet, const string& filename)
{
	ofstream fileToWrite;
	fileToWrite.open(filename, std::ios::out);
	string lastCompanyName = inSet.begin()->companyName; // для вывода пробельной строки между разными компаниями
	for (Info inf : inSet)
	{
		if (lastCompanyName != inf.companyName)
		{
			fileToWrite << endl;
		}
		char s[100];
		sprintf(s, "%s\t%02d:%02d\t%02d:%02d", (inf.companyName).c_str(), inf.departure.hour, inf.departure.minute, inf.arrival.hour, inf.arrival.minute);
		fileToWrite << s << endl;
		lastCompanyName = inf.companyName;
	}
	fileToWrite.close();
}