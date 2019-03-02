#include "stdafx.h"
#include "Jean_Time.h"

#ifdef JEAN_WIN32
#include <sys/timeb.h>
#include <time.h>
#endif

namespace JeanUtility
{
	CJeanTime::CJeanTime() :
	_msec(0)
	{
	}

	CJeanTime
	CJeanTime::now()
	{
	#ifdef JEAN_WIN32
		struct _timeb tb;
		_ftime(&tb);
	#endif
		return CJeanTime(static_cast<int64>(tb.time) * JEAN_INT64(1000) + tb.millitm);
	}

	CJeanTime CJeanTime::makeTime(int year, int month, int day,
					  int hour, int minute, int second, int milliSecond)
	{
		struct tm tmLocal;
		memset(&tmLocal, 0, sizeof(tmLocal));
		tmLocal.tm_sec = second;
		tmLocal.tm_min = minute;
		tmLocal.tm_hour = hour;
		tmLocal.tm_mday = day;
		tmLocal.tm_mon = month - 1;
		tmLocal.tm_year = year - 1900;
		time_t elapSecond  = mktime(&tmLocal);

		return CJeanTime(static_cast<int64>(elapSecond) * JEAN_INT64(1000) + milliSecond);
	}

	CJeanTime CJeanTime::seconds(int64 t)
	{
		return CJeanTime(t * JEAN_INT64(1000));
	}

	CJeanTime CJeanTime::milliSeconds(int64 t)
	{
		return CJeanTime(t);
	}

	int64 CJeanTime::toSeconds() const
	{
		return _msec / 1000;
	}

	int64 CJeanTime::toMilliSeconds() const
	{
		return _msec;
	}

	std::string CJeanTime::toDateTime() const
	{
		time_t time = static_cast<long>(_msec / 1000);

		struct tm* t;
	#ifdef JEAN_WIN32
		t = localtime(&time);
	#endif

		char buf[32];
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);

		std::ostringstream os;
		os << buf;
		return os.str();
	}

	std::string CJeanTime::toDateTimeAccuracy() const
	{
		time_t time = static_cast<long>(_msec / 1000);

		struct tm* t;
	#ifdef JEAN_WIN32
		t = localtime(&time);
	#endif

		char buf[32];
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);

		std::ostringstream os;
		os << buf << ".";
		os.fill('0');
		os.width(3);
		os << static_cast<long>(_msec %1000);
		return os.str();
	}

	CJeanTime::CJeanTime(int64 usec) :
	_msec(usec)
	{
	}
}
