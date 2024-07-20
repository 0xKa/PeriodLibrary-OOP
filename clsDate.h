//all funcs from course 8
#pragma once
#pragma warning(disable : 4996) //needed for system date
#include <iostream>
#include <string>
#include "clsString.h";

using namespace std;

class clsDate
{
private:
	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

public:
	//defualt constructor
	clsDate() 
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}

	//parameterized constructor 1
	clsDate(string Date) 
	{
		vector <string> vDate;
		vDate = clsString::Split(Date, "/");
		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	//parameterized constructor 2
	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;

	}

	//parameterized constructor 3
	clsDate(short DayOrderInYear, short Year) 
	{
		clsDate Date1 = GetDateFromDayOrderInYear(DayOrderInYear, Year);
		_Day = Date1.Day;
		_Month = Date1.Month;
		_Year = Date1.Year;
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;
	
	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;
	
	void SetYear(short Year)
	{
		_Year = Year;
	}
	short GetYear()
	{
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	//this func name was DateToString
	static string DateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
		//return example: 6/8/2004
	}
	string GetDate()
	{
		return DateToString(*this); //*this means this/current object
	}

	static clsDate StringToDate(string Date)
	{
		clsDate Date1;
		vector <string> vDate;
		vDate = clsString::Split(Date, "/");
		Date1.Day = stoi(vDate[0]);
		Date1.Month = stoi(vDate[1]);
		Date1.Year = stoi(vDate[2]);
		return Date1;
	}

	void Print()
	{
		cout << GetDate() << endl;
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		short Year = now->tm_year + 1900;
		short Month = now->tm_mon + 1;
		short Day = now->tm_mday;
		
		return clsDate(Day, Month, Year);
	}

	static bool IsValidDate(clsDate Date)
	{
		if (Date.Day <= 0 || Date.Month <= 0 || Date.Year < 0)
			return false;
		if (Date.Month > 12)
			return false;
		if (NumberOfDaysInMonth(Date.Month, Date.Year) < Date.Day)
			return false;
		return true;
	}
	bool IsValid()
	{
		return IsValidDate(*this);
	}

	static bool isLeapYear(short Year)
	{
		return ((Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0)); // algorithm in one line
	}
	bool isLeapYear()
	{
		return isLeapYear(_Year);
	}

	static short NumberOfDaysInMonth(short Month, short Year)
	{
		short arrNumberOfDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return isLeapYear(Year) && Month == 2 ? 29 : arrNumberOfDays[Month - 1]; 
	}
	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Month, _Year);
	}

	static short DayOfWeekOrder(short y, short m, short d) 
	{
	short a = (14 - m) / 12;
	y = y - a;
	m = m + 12 * a - 2;
	return (d + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	// will return the Day Index, Sunday = 0, Monday = 1, Tuesday = 2, etc...
	}
	static short DayOfWeekOrder(clsDate Date)
	{
		//this is overload function (i changed parameter)//
		return DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(*this);
	}

	static string GetMonthShortName(short Month)
	{
		string MonthsList[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
		"Aug", "Sep", "Oct", "Nov", "Dec" };
		return MonthsList[Month - 1];
	}
	string GetMonthShortName()
	{
		return GetMonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Year, short Month)
	{
		int CurrentDay = DayOfWeekOrder(Year, Month, 1); // 1 = first day of the month
		int NumberOfDays = NumberOfDaysInMonth(Month, Year); // get number of days in that month
		printf("\n _______________________%s_______________________\n",
			GetMonthShortName(Month).c_str());
		
		cout << "\n    Sun    Mon    Tue    Wed    Thu    Fri    Sat \n";
		int i;
		for (i = 0; i < CurrentDay; i++)
			printf("       ");
		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%7d", j); //print day number
			if (++i == 7)
			{
				i = 0;
				printf("\n"); //move to the next line every 7 numbers
			}
		}
		printf("\n _________________________________________________\n");
	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Year,_Month);
	}
	
	static void PrintYearCalendar(short year)
	{
		printf("\n -------------------------------------------\n");
		printf("\n Year %d Calendar \n", year);
		printf("\n -------------------------------------------\n");
		for (int month = 1; month <= 12; month++)
		{
			PrintMonthCalendar(year, month);
			cout << endl;
		}
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	static short CalculateDaysFromTheBeginningOfYear(short day, short month, short year)
	{
		short TotalDays = day; //number of days enterd
		for (short i = 1; i < month; i++)
		{
			TotalDays += NumberOfDaysInMonth(i, year); // number of days in each month
		}
		return TotalDays;
	}
	static short CalculateDaysFromTheBeginningOfYear(clsDate Date1)
	{
		return CalculateDaysFromTheBeginningOfYear(Date1.Day, Date1.Month, Date1.Year);
	}
	short CalculateDaysFromTheBeginningOfYear()
	{
		return CalculateDaysFromTheBeginningOfYear(*this);
	}
	
	//the func used in constructor
	static clsDate GetDateFromDayOrderInYear(short DayOrder, short Year )
	{
		clsDate Date1;

		Date1.Year = Year;
		Date1.Month = 1;
		short MonthDays = 0, RemainingDays = DayOrder;
		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date1.Month, Date1.Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date1.Month++;
			}
			else
			{
				Date1.Day = RemainingDays;
				break;
			}
		}
		return Date1;
	}

	static clsDate AddDays(clsDate Date, int DaysToAdd)
	{
		short RemainingDays = DaysToAdd +
			CalculateDaysFromTheBeginningOfYear(Date.Day, Date.Month, Date.Year);
		Date.Month = 1; //start adding from the beginning of the month
		short MonthDays = 0;
		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
				if (Date.Month > 12) {
					Date.Month = 1; //restart the year
					Date.Year++;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}
	clsDate AddDays(int DaysToAdd)
	{
		return AddDays(*this, DaysToAdd);
	}

	//compare date funcs
	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{ //one line of code
		return (Date1.Year < Date2.Year) ? true : (Date1.Year > Date2.Year) ? false :
			(Date1.Month < Date2.Month) ? true : (Date1.Month > Date2.Month) ? false :
			(Date1.Day < Date2.Day) ? true : false;
	}
	bool Before(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}
	
	static bool IsDate1EqualsDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ?
			((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}
	bool Equals(clsDate Date2)
	{
		return IsDate1EqualsDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualsDate2(Date1,
			Date2));
	}
	bool After(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	enum DateCompareResults { enBefore = -1, enEqual = 0, enAfter = 1 };
	static DateCompareResults CompareDates(clsDate Date1, clsDate Date2)
	{
		return IsDate1BeforeDate2(Date1, Date2) ? enBefore : IsDate1EqualsDate2(Date1,
			Date2) ? enEqual : enAfter;
	}
	DateCompareResults CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static bool isLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
	}
	bool isLastDayInMonth()
	{
		return isLastDayInMonth(*this);
	}

	static bool isLastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool isLastMonthInYear()
	{
		return isLastMonthInYear(_Month);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate temp;
		temp.Year = Date1.Year;
		temp.Month = Date1.Month;
		temp.Day = Date1.Day;
		Date1.Year = Date2.Year;
		Date1.Month = Date2.Month;
		Date1.Day = Date2.Day;
		Date2.Year = temp.Year;
		Date2.Month = temp.Month;
		Date2.Day = temp.Day;
	}
	void SwapDates(clsDate& Date2)
	{
		SwapDates(*this, Date2);
	}

	static short GetDiffrenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int DaysCounter = 0;
		int SwapFlagValue = 1;
		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			DaysCounter++;
			Date1 = AddOneDay(Date1);
		}
		return IncludeEndDay ? ++DaysCounter * SwapFlagValue : DaysCounter *
			SwapFlagValue;
	}
	short GetDiffrenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDiffrenceInDays(*this, Date2, IncludeEndDay);
	}

	//increase date funcs

	static clsDate AddOneDay(clsDate Date)
	{
		if (isLastDayInMonth(Date))
		{
			Date.Day = 1;
			if (isLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Year++;
			}
			else
				Date.Month++;
		}
		else
			Date.Day++;
		return Date;
	}
	void AddOneDay()
	{
		AddOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date, short xDays)
	{
		for (int i = 0; i < xDays; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDays(short xDays)
	{
		 IncreaseDateByXDays(*this, xDays);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		return Date = IncreaseDateByXDays(Date, 7);
	}
	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate& Date, short xWeeks)
	{
		for (int i = 0; i < xWeeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void IncreaseDateByXWeeks(short xWeeks)
	{
		 IncreaseDateByXWeeks(*this, xWeeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (isLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
			Date.Month++;
		//importent
		//last check day in date should not exceed max days in the current month
		//example if date is 31/1/2022 increasing one month should not be 31/2/2022, 
		// it should be 28 / 2 / 2022
		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month,
			Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}
		return Date;
	}
	void IncreaseDateByOneMonth()
	{
		 IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate& Date, short xMonths)
	{
		for (int i = 0; i < xMonths; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonths(short xMonths)
	{
		 IncreaseDateByXMonths(*this, xMonths);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;
		return Date;
	}
	void IncreaseDateByOneYear()
	{
		 IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, short xYears)
	{
		for (int i = 0; i < xYears; i++)
		{
			Date.Year += xYears;
			return Date;
		}
		return Date;
	}
	void IncreaseDateByXYears(short xYears)
	{
		 IncreaseDateByXYears(*this, xYears);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year += 10;
		return Date;
	}
	void IncreaseDateByOneDecade()
	{
		 IncreaseDateByOneDecade(*this);
	}
	
	static clsDate IncreaseDateByXDecades(clsDate& Date, short xDecades)
	{
		Date.Year += (xDecades * 10);
		return Date;
	}
	void IncreaseDateByXDecades(short xDecades)
	{
		 IncreaseDateByXDecades(*this, xDecades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year += 100;
		return Date;
	}
	void IncreaseDateByOneCentury()
	{
		 IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year += 1000;
		return Date;
	}
	void IncreaseDateByOneMillennium()
	{
		 IncreaseDateByOneMillennium(*this);
	}

	//decrease date funcs

	static clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
			}
		}
		else
			Date.Day--;
		return Date;
	}
	void DecreaseDateByOneDay()
	{
		 DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, short xDays)
	{
		for (int i = 0; i < xDays; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(short xDays)
	{
		 DecreaseDateByXDays(*this, xDays);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		return Date = DecreaseDateByXDays(Date, 7);
	}
	void DecreaseDateByOneWeek()
	{
		 DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate& Date, short xWeeks)
	{
		for (int i = 0; i < xWeeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeeks(short xWeeks)
	{
		 DecreaseDateByXWeeks(*this, xWeeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
			Date.Month--;
		//importent
		//last check day in date should not exceed max days in the current month
		//example if date is 31/3/2022 decreasing one month should not be 31/2/2022,
		// it should be 28 / 2 / 2022
		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}
		return Date;
	}
	 void DecreaseDateByOneMonth()
	{
		 DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& Date, short xMonths)
	{
		for (int i = 0; i < xMonths; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonths(short xMonths)
	{
		 DecreaseDateByXMonths(*this, xMonths);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date.Year--;
		return Date;
	}
	void DecreaseDateByOneYear()
	{
		 DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, short xYears)
	{
		Date.Year -= xYears;
		return Date;
	}
	void DecreaseDateByXYears(short xYears)
	{
		 DecreaseDateByXYears(*this, xYears);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade()
	{
		 DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, short xDecades)
	{
		Date.Year -= (xDecades * 10);
		return Date;
	}
	void DecreaseDateByXDecades(short xDecades)
	{
		 DecreaseDateByXDecades(*this, xDecades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury()
	{
		 DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium()
	{
		 DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate Date)
	{
		return (DayOfWeekOrder(Date) == 6);
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		//weekends are Fri & Sat
		short DayIndex = DayOfWeekOrder(Date);
		return (DayIndex == 5 || DayIndex == 6);
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !(IsWeekEnd(Date));
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date); //substract from index 6
	}
	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		return NumberOfDaysInMonth(Date.Month, Date.Year) - Date.Day;
	}
	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		if (isLeapYear(Date.Year))
			return 366 - CalculateDaysFromTheBeginningOfYear(Date);
		else
			return 365 - CalculateDaysFromTheBeginningOfYear(Date);
	}
	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateBusinessDays(clsDate StartDate, clsDate EndDate)
	{
		short DaysCounter = 0;
		while (IsDate1BeforeDate2(StartDate, EndDate))
		{
			if (IsBusinessDay(StartDate))
				DaysCounter++;
			StartDate = AddOneDay(StartDate);
		}
		return DaysCounter;
	}
	static short CalculateVacationDays(clsDate StartDate, clsDate EndDate)
	{
		return CalculateBusinessDays(StartDate, EndDate); //vacation days is same as busniess days
	}
	short CalculateVacationDays(clsDate VacationEndDate)
	{
		return CalculateVacationDays(*this, VacationEndDate);
	}

	static clsDate CalculateVacationEndDate(clsDate StartDate, short VacationDuration)
	{
		for (int i = 0; i < VacationDuration; i++)
		{
			if (IsBusinessDay(StartDate))
				StartDate = AddOneDay(StartDate);
			else
			{
				StartDate = AddOneDay(StartDate);
				i--;
			}
		}
		return StartDate;
	}
	clsDate CalculateVacationEndDate(short VacationDuration)
	{
		return CalculateVacationEndDate(*this, VacationDuration);
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		return GetDiffrenceInDays(DateOfBirth, GetSystemDate(), true);
	}

};

