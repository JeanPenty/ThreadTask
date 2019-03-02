/*
* 文件名称：Jean_Time.h
* 文件标识：
* 摘　　要：时间类
* 功    能：统一日历时间和间隔时间
*/
#ifndef	__JEAN_TIME_H__
#define	__JEAN_TIME_H__

#pragma once
#include "Jean_Base.h"

namespace JeanUtility
{

	class CJeanTime
	{
	public:

		CJeanTime();

		// No copy constructor and assignment operator necessary. The
		// automatically generated copy constructor and assignment
		// operator do the right thing.

		static CJeanTime now();
		static CJeanTime makeTime(int year, int month, int day,
			int hour, int minute, int second, int milliSecond);
		static CJeanTime seconds(int64);
		static CJeanTime milliSeconds(int64);

		int64 toSeconds() const;
		int64 toMilliSeconds() const;

		std::string toDateTime() const;
		std::string toDateTimeAccuracy() const;

		void reset()
		{
			_msec = 0;
		}

		CJeanTime operator-() const
		{
			return CJeanTime(-_msec);
		}

		CJeanTime operator-(const CJeanTime& rhs) const
		{
			return CJeanTime(_msec - rhs._msec);
		}

		CJeanTime operator+(const CJeanTime& rhs) const
		{
			return CJeanTime(_msec + rhs._msec);
		}

		CJeanTime& operator+=(const CJeanTime& rhs)
		{
			_msec += rhs._msec;
			return *this;
		}

		CJeanTime& operator-=(const CJeanTime& rhs)
		{
			_msec -= rhs._msec;
			return *this;
		}

		bool operator<(const CJeanTime& rhs) const
		{
			return _msec < rhs._msec;
		}

		bool operator<=(const CJeanTime& rhs) const
		{
			return _msec <= rhs._msec;
		}

		bool operator>(const CJeanTime& rhs) const
		{
			return _msec > rhs._msec;
		}

		bool operator>=(const CJeanTime& rhs) const
		{
			return _msec >= rhs._msec;
		}

		bool operator==(const CJeanTime& rhs) const
		{
			return _msec == rhs._msec;
		}

		bool operator!=(const CJeanTime& rhs) const
		{
			return _msec != rhs._msec;
		}

		double operator/(const CJeanTime& rhs) const
		{
			return (double)_msec / (double)rhs._msec;
		}

		CJeanTime& operator*=(int rhs)
		{
			_msec *= rhs;
			return *this;
		}

		CJeanTime operator*(int rhs) const
		{
			CJeanTime t;
			t._msec = _msec * rhs;
			return t;
		}

		CJeanTime& operator/=(int rhs)
		{
			_msec /= rhs;
			return *this;
		}

		CJeanTime operator/(int rhs) const
		{
			CJeanTime t;
			t._msec = _msec / rhs;
			return t;
		}

		CJeanTime& operator*=(int64 rhs)
		{
			_msec *= rhs;
			return *this;
		}

		CJeanTime operator*(int64 rhs) const
		{
			CJeanTime t;
			t._msec = _msec * rhs;
			return t;
		}

		CJeanTime& operator/=(int64 rhs)
		{
			_msec /= rhs;
			return *this;
		}

		CJeanTime operator/(int64 rhs) const
		{
			CJeanTime t;
			t._msec = _msec / rhs;
			return t;
		}

		CJeanTime& operator*=(double rhs)
		{
			_msec = static_cast<int64>(static_cast<double>(_msec) * rhs);
			return *this;
		}

		CJeanTime operator*(double rhs) const
		{
			CJeanTime t;
			t._msec = static_cast<int64>(static_cast<double>(_msec) * rhs);
			return t;
		}

		CJeanTime& operator/=(double rhs)
		{
			_msec = static_cast<int64>(static_cast<double>(_msec) / rhs);
			return *this;
		}

		CJeanTime operator/(double rhs) const
		{
			CJeanTime t;
			t._msec = static_cast<int64>(static_cast<double>(_msec) / rhs);
			return t;
		}

	private:

		CJeanTime(int64);

		int64 _msec;//毫秒
	};

} // End namespace JeanUtility

#endif //__JEAN_TIME_H__
