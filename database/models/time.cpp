#include "time.h"
#include <QTime>

Time::Time(const QString &time) {
  QDateTime parsed = QDateTime::fromString(time);
  // collect the data
  QDate _date = parsed.date();
  day = _date.day();
  month = _date.month();
  year = _date.year();
  // collect the time
  QTime _time = parsed.time();
  hour = _time.hour();
  minute = _time.minute();
  second = _time.second();
}

int Time::Day() const { return day; }

int Time::Month() const { return month; }

int Time::Year() const { return year; }

void Time::setDay(int new_day) { day = new_day; }

void Time::setMonth(int new_month) { month = new_month; }

void Time::setYear(int new_year) { year = new_year; }

int Time::Hour() const { return hour; }

int Time::Minute() const { return minute; }

int Time::Second() const { return second; }

void Time::setHour(int new_hour) { hour = new_hour; }

void Time::setMinute(int new_minute) { minute = new_minute; }

void Time::setSecond(int new_second) { second = new_second; }
