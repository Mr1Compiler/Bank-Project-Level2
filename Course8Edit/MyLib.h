#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <iomanip>
using namespace std;


namespace MyLib
{
	int ReadNumber()
	{
		int Num;

		cout << "Enter A Number ? ";
		cin >> Num;

		return Num;
	}

	short ReadYear()
	{
		int Year;

		cout << "Enter A Number ? ";
		cin >> Year;

		return Year;
	}

	short ReadMonth()
	{
		short Month;

		cout << "\nPleace Enter A Month ? ";
		cin >> Month;

		return Month;
	}

	short ReadDay()
	{
		short Day;

		cout << "\nPleace Enter A Day ? ";
		cin >> Day;

		return Day;
	}


	string NumberToText(int Number)
	{
		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] =
			{ "", "One","Two","Three","Four","Five","Six","Seven", "Eight","Nine","Ten",
				"Eleven","Twelve","Thirteen","Fourteen", "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"
			};

			return arr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = {
				"","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"
			};

			return arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return NumberToText(Number / 100) + " Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return NumberToText(Number / 1000) + " Thousands " + NumberToText(Number % 10000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return NumberToText(Number / 1000000) + " Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return "One Billion " + NumberToText(Number % 1000000000);
		}

		else
		{
			return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}
	}

	bool isLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0 || Year % 400 == 0);
	}

	short NumberOfDaysInAYear(short Year)
	{
		return isLeapYear(Year) ? 366 : 365;
	}

	short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}

	int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}

	short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month>12)
			return  0;

		short days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
	}

	short NumberOfHoursInAMonth(short Year, short Month)
	{
		return NumberOfDaysInAMonth(Year, Month) * 24;
	}

	int NumberOfMinutesInAMonth(short Year, short Month)
	{
		return NumberOfHoursInAMonth(Year, Month) * 60;
	}

	int NumberOfSecondsInAMonth(short Year, short Month)
	{
		return NumberOfMinutesInAMonth(Year, Month) * 60;
	}

	short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// Gregorian://0:sun, 1:Mon, 2:Tue...etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder];
	}

	string MonthShortName(short MonthNumber)
	{
		string Months[12] = { "Jan", "Feb", "Mar",
							  "Apr", "May", "Jun",
							  "Jul", "Aug", "Sep",
							  "Oct", "Nov", "Dec" };

		return (Months[MonthNumber - 1]);
	}

	void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;

		int current = DayOfWeekOrder(1, Month, Year);

		NumberOfDays = NumberOfDaysInAMonth(Month, Year);

		printf("\n  _______________%s_______________\n\n",
			MonthShortName(Month).c_str());


		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i;

		for (i = 0; i < current; i++)
			printf("     ");


		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j); if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}


		printf("\n  _________________________________\n");

	}

	short NumberOfDaysFromTheBeginingOfTheYear(short Year, short Month, short Day)
	{
		short TotalDays = 0;

		for (int i = 1; i < Month; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}

	struct stDate
	{
		short Year;
		short Month;
		short Day;
	};

	stDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{
		stDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.Month, Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	stDate ReadFullDate()
	{
		stDate Date;
		Date.Day = ReadDay();
		Date.Month = ReadMonth();
		Date.Year = ReadYear();
		return Date;
	}

	stDate DateAddDays(short Days, stDate Date)
	{
		short RemainingDays = Days + NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);

		short MonthDays = 0;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Month = 1;
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

	bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
	{
		return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}

	bool IsDate1EqualDate2(stDate Date1, stDate Date2)
	{
		return  (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}

	bool IsLastDayInMonth(stDate Date)
	{
		return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
	}

	bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	stDate IncreaseDateByOneDay(stDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}

		else
		{
			Date.Day++;
		}

		return Date;
	}

	stDate GetSystemDate()
	{
		stDate Date;

		time_t t = time(0);
		tm* now = localtime(&t);

		Date.Year = now->tm_year + 1900;
		Date.Month = now->tm_mon + 1;
		Date.Day = now->tm_mday;

		return Date;
	}

	void SwapDates(stDate& Date1, stDate& Date2)
	{
		stDate TempDate;

		TempDate.Year = Date1.Year;
		TempDate.Month = Date1.Month;
		TempDate.Day = Date1.Day;

		Date1.Year = Date2.Year;
		Date1.Month = Date2.Month;
		Date1.Day = Date2.Day;

		Date2.Year = TempDate.Year;
		Date2.Month = TempDate.Month;
		Date2.Day = TempDate.Day;
	}

	int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{ //Swap Dates    
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++; Date1 = IncreaseDateByOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
	}


	stDate IncreaseDateByOneWeek(stDate Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	stDate IncreaseDateByXWeeks(short Weeks, stDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	stDate IncreaseDateByOneMonth(stDate Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}


	stDate IncreaseDateByXDays(short Days, stDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	stDate IncreaseDateByXMonths(short Months, stDate Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}


	stDate IncreaseDateByOneYear(stDate Date)
	{
		Date.Year++;
		return Date;
	}

	stDate IncreaseDateByXYears(short Years, stDate Date)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	stDate IncreaseDateByXYearsFaster(short Years, stDate Date)
	{
		Date.Year += Years; 
		return Date;
	}

	stDate IncreaseDateByOneDecade(stDate Date)
	{
		Date.Year += 10;
		return Date;
	}

	stDate IncreaseDateByXDecades(short Decade, stDate Date)
	{
		for (short i = 1; i <= Decade * 10; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	stDate IncreaseDateByXDecadesFaster(short Decade, stDate Date)
	{
		Date.Year += Decade * 10;
		return Date;
	}


	stDate IncreaseDateByOneCentury(stDate Date)
	{
		Date.Year += 100;
		return Date;
	}

	stDate IncreaseDateByOneMillennium(stDate Date)
	{
		Date.Year += 1000;
		return Date;
	}

	short DayOfWeekOrder(stDate Date)
	{
		short a, y, m;
		a = (14 - Date.Month) / 12;
		y = Date.Year - a;
		m = Date.Month + (12 * a) - 2;
		// Gregorian://0:sun, 1:Mon, 2:Tue...etc
		return (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	string DayShortName(short DayOfWeekOrder)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayNames[DayOfWeekOrder];
	}


	bool IsEndOfWeek(stDate Date)
	{
		return DayOfWeekOrder(Date) == 6;
	}

	bool IsWeekEnd(stDate Date)
	{
		short DayIndex = DayOfWeekOrder(Date);

		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsBussinessDay(stDate Date)
	{
		return !IsWeekEnd(Date);
	}

	short DayUntilTheEndOfWeek(stDate Date)
	{
		return 6 - (DayOfWeekOrder(Date));
	}

	short DayUntilTheEndOfMonth(stDate Date1)
	{
		stDate EndOfMontDate;
		EndOfMontDate.Day = NumberOfDaysInAMonth(Date1.Month, Date1.Year);
		EndOfMontDate.Month = Date1.Month;
		EndOfMontDate.Year = Date1.Year;

		return GetDifferenceInDays(Date1, EndOfMontDate, true);
	}

	short DayUntilTheEndOfYear(stDate Date1)
	{
		stDate EndOfYearDate;
		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date1.Year;

		return GetDifferenceInDays(Date1, EndOfYearDate, true);
	}

	short CalculateVacatoinDays(stDate DateFrom, stDate DateTo)
	{
		short Days = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBussinessDay(DateFrom))
				Days++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return Days;
	}

	stDate CalculateVacationReturnDate(stDate DateFrom, short VacationDays)
	{

		short WeekEndCounter = 0;


		while (IsWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{

			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DateFrom;
	}

	bool IsDate1AfterDate2(stDate Date1, stDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	enum enDateCompare
	{
		Before = -1,
		Equal = 0,
		After = 1
	};

	struct stPeriod
	{
		stDate StartDate;
		stDate EndDate;
	};

	
	enDateCompare CompareDates(stDate Date1, stDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;


		else if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;


		else
			return enDateCompare::After;
	}

	bool IsOverlapPeriods(stPeriod Period1, stPeriod Period2)
	{
		if (
			CompareDates(Period2.EndDate, Period1.StartDate) == enDateCompare::Before
			||
			CompareDates(Period2.StartDate, Period1.EndDate) == enDateCompare::After
			)
			return false;

		else
			return true;
	}

	short PeriodLengthInDays(stPeriod Period, bool IncludeEndDate = false)
	{
		return GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDate);
	}

	bool isDateInPeriod(stDate Date, stPeriod Period)
	{
		return !(CompareDates(Date, Period.StartDate) == enDateCompare::Before
			||
			CompareDates(Date, Period.EndDate) == enDateCompare::After);
	}

	int CountOverlapDays(stPeriod Period1, stPeriod Period2)
	{
		int Period1Length = PeriodLengthInDays(Period1, true);
		int Period2Length = PeriodLengthInDays(Period2, true);
		int OverlapDays = 0;

		if (!IsOverlapPeriods(Period1, Period2))
			return 0;

		if (Period1Length < Period2Length)
		{
			while (IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
			{
				if (isDateInPeriod(Period1.StartDate, Period2))
					OverlapDays++; Period1.StartDate = IncreaseDateByOneDay(Period1.StartDate);
			}
		}

		else
		{
			while (IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
			{
				if (isDateInPeriod(Period2.StartDate, Period1))
					OverlapDays++; Period2.StartDate = IncreaseDateByOneDay(Period2.StartDate);
			}
		}
		return OverlapDays;

	}

	//bool IsValidDate(stDate Date)
//{
//	return Date.Day > NumberOfDaysInAMonth(Date.Month, Date.Year) ? false : (Date.Month > 12) ? false : true;
//}

	bool IsValidDate(stDate Date)
	{
		if (Date.Day < 1 || Date.Day>31)
			return false;

		if (Date.Month < 1 || Date.Month>12)
			return false;

		if (Date.Month == 2)
		{
			if (isLeapYear(Date.Year))
			{
				if (Date.Day > 29)
					return false;
			}
			else
			{
				if (Date.Day > 28)
					return false;
			}
		}

		short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

		if (Date.Day > DaysInMonth)
			return false;

		return true;
	}

	string ReplaceWordInString(string S1, string StringToReplace, string sRepalceTo)
	{
		short pos = S1.find(StringToReplace);

		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, StringToReplace.length(), sRepalceTo);
			pos = S1.find(StringToReplace);//find next  
		}

		return S1;
	}

	vector<string> SplitString(string S1, string Delim)
	{
		vector<string> vString;
		string sWord;
		short pos = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			while ((pos = S1.find(Delim)) != std::string::npos)
			{
				sWord = S1.substr(0, pos);

				if (sWord != "")
				{
					vString.push_back(sWord);
				}
				S1.erase(0, pos + Delim.length());
			}
		}
		if (S1 != "")
		{
			vString.push_back(S1);
		}
		return vString;
	}

	stDate StringToDate(string strDate)
	{
		stDate Date;
		vector<string> vDate;

		vDate = SplitString(strDate, "/");

		Date.Day = stoi(vDate[0]);
		Date.Month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);

		return Date;
	}

	string DateToString(stDate Date)
	{
		return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string FormateDate(stDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDateString = "";

		FormattedDateString = ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
		FormattedDateString = ReplaceWordInString(FormattedDateString, "mm", to_string(Date.Month));
		FormattedDateString = ReplaceWordInString(FormattedDateString, "yyyy", to_string(Date.Year));

		return  FormattedDateString;
	}
}
