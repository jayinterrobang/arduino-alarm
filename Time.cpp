#include "Time.h"

static bool Time::areTimesEqual(Time timeA, Time timeB) {
  if (timeA.hours != timeB.hours) return false;
  if (timeA.minutes != timeB.minutes) return false;

  return true;
}

void Time::incrementHours(int amount) {
  hours += amount;
  while (hours >= 24) hours -= 24;
  while (hours < 0) hours += 24;
}

void Time::incrementMinutes(int amount) {
  minutes += amount;

  while (minutes >= 60) {
    incrementHours(1);
    minutes -= 60;
  }

  while (minutes < 0) {
    incrementHours(-1);
    minutes += 60;
  }
}

String Time::getCurrentTimeString() {
  String timeString = String();

  // Add the current hour to the string, making sure there is a leading zero.
  if ((hours % 12) == 0) timeString += "12";
  else {
    if ((hours % 12) < 10) timeString += "0";
    timeString += String(hours % 12);
  };

  timeString += ":";

  // Add the current minute to the string, making sure there is a leading zero.
  if (minutes < 10) timeString += "0";
  timeString += String(minutes);

  if (hours < 12) timeString += " AM";
  else timeString += " PM";

  return timeString;
}