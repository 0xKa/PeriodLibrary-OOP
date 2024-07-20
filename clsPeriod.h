//all funcs from course 8
#pragma once
#include <iostream>
#include "clsDate.h";

using namespace std;

class clsPeriod
{
private:
	clsDate _StartDate;
	clsDate _EndDate;

public:
	clsPeriod()
	{
		_StartDate = clsDate(1, 1, 1900);
		_EndDate = clsDate::GetSystemDate();
	}

	void SetStartDate(clsDate SetStartDate)
	{
		_StartDate = SetStartDate;
	}
	clsDate GetSetStartDate()
	{
		return _StartDate;
	}
	__declspec(property(get = GetSetStartDate, put = SetStartDate)) clsDate StartDate;
	
	void SetEndDate(clsDate EndDate)
	{
		_EndDate = EndDate;
	}
	clsDate GetEndDate()
	{
		return _EndDate;
	}
	__declspec(property(get = GetEndDate, put = SetEndDate)) clsDate EndDate;

	static void Print(clsPeriod Period)
	{
		cout << "Period Start Date: " << clsDate::DateToString(Period.StartDate) << endl;
		cout << "Period End Date  : " << clsDate::DateToString(Period.EndDate) << endl;
	}
	void Print()
	{
		Print(*this);
	}

	static bool IsOverlapPeriods(clsPeriod Period1, clsPeriod Period2)
	{
		//short easy solution
		if (clsDate::CompareDates(Period1.EndDate, Period2.StartDate) == clsDate::enBefore
			||
			clsDate::CompareDates(Period2.EndDate, Period1.StartDate) == clsDate::enBefore)
			return false; //don't overlap
		else
			return true; //overlap
	}
	bool IsOverlapWith(clsPeriod Period2)
	{
		return IsOverlapPeriods(*this, Period2);
	}

	static short GetPeriodLength(clsPeriod Period, bool IncludeEndDay = false)
	{
		return clsDate::GetDiffrenceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
	}
	short Length(bool IncludeEndDay = false)
	{
		return GetPeriodLength(*this, IncludeEndDay);
	}

	static bool IsDateWithinPeriod(clsPeriod Period, clsDate Date)
	{
		return !(clsDate::CompareDates(Date, Period.StartDate) == clsDate::enBefore || clsDate::CompareDates(Date, Period.EndDate) == clsDate::enAfter);
	}
	bool IsDateWithinPeriod(clsDate Date)
	{
		return IsDateWithinPeriod(*this, Date);
	}

	static int CountOverlapDaysInPeriods(clsPeriod Period1, clsPeriod Period2)
	{
		int Period1Length = GetPeriodLength(Period1, true);
		int Period2Length = GetPeriodLength(Period2, true);
		int OverlapDaysCounter = 0;
		if (IsOverlapPeriods(Period1, Period2) == false)
			return OverlapDaysCounter; //return 0
		if (Period1Length < Period2Length)
		{
			while (clsDate::IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
			{
				if (IsDateWithinPeriod(Period2, Period1.StartDate))
					OverlapDaysCounter++;
				Period1.StartDate = clsDate::AddOneDay(Period1.StartDate);//I changed this line
			}
		}
		else
		{
			while (clsDate::IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
			{
				if (IsDateWithinPeriod(Period1, Period2.StartDate))
					OverlapDaysCounter++;
				Period2.StartDate = clsDate::AddOneDay(Period1.StartDate);//I changed this line
			}
		}
		return OverlapDaysCounter;
	}
	int CountOverlapDaysWith(clsPeriod Period2)
	{
		return CountOverlapDaysInPeriods(*this, Period2);
	}

};

