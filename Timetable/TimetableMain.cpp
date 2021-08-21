#include "Timetable.h"

int main()
{
	const string inputFileName = "ININFO.TXT";
	const string outputFileName = "OUTINFO.TXT";
	set<Info> infoSet = setCreate(inputFileName);
	outSet(infoSet, outputFileName);
}