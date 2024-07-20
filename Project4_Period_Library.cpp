// Project4_Period_Library / functions from course 8
#include <iostream>
#include "clsPeriod.h";
using namespace std;

int main()
{
	


	clsPeriod Period1;
	Period1.StartDate = clsDate(6, 8, 2004);
	Period1.EndDate = clsDate(31, 12, 2004);
	
	clsPeriod Period2;
	Period2.StartDate = clsDate(1, 1, 2004);
	Period2.EndDate = clsDate(1, 1, 2006);

	cout << "\nPeriod 1:\n";
	Period1.Print();

	cout << "\nPeriod 2:\n";
	Period2.Print();
	
	cout << "\nDoes Period1 & Period2 Overlap?? : " << Period1.IsOverlapWith(Period2) << endl;

	cout << "\nPeriod1 Length: " << Period1.Length() << " Days." << endl;
	cout << "Period2 Length: " << Period2.Length() << " Days." << endl;

	cout << "\nIs Date 1/1/2005 within Period2: " 
		<< Period2.IsDateWithinPeriod(clsDate(1,1,2005)) << endl;
	
	cout << "\nPeriod1 and Period2 count Overlaped days: " 
		<< Period1.CountOverlapDaysWith(Period2) << endl;



	system("pause>0");
	return 0;
}

