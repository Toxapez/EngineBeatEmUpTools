#include "Date.h"

inline std::tm localtime_xp(std::time_t timer)
{
    std::tm bt {};
#if defined(__unix__)
    localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
    localtime_s(&bt, &timer);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(&timer);
#endif
    return bt;
}

Date Date::GetCurrent() {

	auto bt = localtime_xp(std::time(0));
	
	Date d;
	d.year = 1900 + bt.tm_year;
	d.month = bt.tm_mon + 1;
	d.day = bt.tm_mday;
	
	d.hour = bt.tm_hour;
	d.minute = bt.tm_min;
	d.second = bt.tm_sec;
	return d;
}
