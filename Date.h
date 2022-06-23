#pragma once
#include <ctime>

struct Date
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	static Date GetCurrent();

	bool operator<(Date d) {
		if (year < d.year)
			return true;
		else if (month < d.month)
			return  true;
		else if (day < d.day)
			return  true;
		else if (hour < d.hour)
			return  true;
		else if (minute < d.minute)
			return  true;
		else if (second < d.second)
			return  true;
		return false;
	}

	bool operator>(Date d) {
		if (year > d.year)
			return true;
		else if (month > d.month)
			return  true;
		else if (day > d.day)
			return  true;
		else if (hour > d.hour)
			return  true;
		else if (minute > d.minute)
			return  true;
		else if (second > d.second)
			return  true;
		return false;
	}

	bool operator==(Date d) {
		return year == d.year &&
			month == d.month &&
			day == d.day &&
			hour == d.hour &&
			minute == d.minute &&
			second == d.second;
	}
};

