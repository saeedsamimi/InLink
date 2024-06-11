#ifndef TIME_H
#define TIME_H
#include <QString>

class Time {
public:
  Time() = default;
  Time(const QString &time);

  /* date getters */

  int Day() const;
  int Month() const;
  int Year() const;

  /* date setters */

  void setDay(int new_day);
  void setMonth(int new_month);
  void setYear(int new_year);

  /* time getters */

  int Hour() const;
  int Minute() const;
  int Second() const;

  /* time setters */

  void setHour(int new_hour);
  void setMinute(int new_minute);
  void setSecond(int new_second);

private:
  int day = 0;
  int month = 0;
  int year = 0;
  int hour = 0;
  int minute = 0;
  int second = 0;
};

#endif // TIME_H
