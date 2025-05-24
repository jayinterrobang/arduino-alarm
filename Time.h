#include <Arduino.h>

class Time {
  private:

  public:
    // Is always in the range of [0,24)
    int hours = 0;
    // Is always in the range of [0,60)
    int minutes = 0;

    /**
     * Default constructor for the Time class
     *
     * @param h the starting hours of the clock
     * @param m the starting minutes of the clock
     */
    Time(int h, int m) : hours(h), minutes(m) {} 

    /**
     * Static function that, given two Time instances, checks if they have the same hour and minute values.
     * The order of the parameters will not change the result.
     * 
     * @param timeA the first Time instance to be compared
     * @param timeB the second Time instance to be compared
     */
    static bool areTimesEqual(Time timeA, Time timeB);

    /**
     * Adds a certain amount of hours to the current time. Already adjusts for when the hours
     * goes outside the range of [0,24)
     *
     * @param amount the amount of hours to be added
     */
    void incrementHours(int amount);

    /**
     * Adds a certain amount of minutes to the current time. Already adjusts for when the minutes
     * goes outside the range of [0,60). Calls incrementHours.
     *
     * @param amount the amount of minutes to be added
     */
    void incrementMinutes(int amount);

    /**
     * Get the current time as a string, in the format of:
     * ##:## [AM/PM]
     * where both the hours AND minutes have 2 digits, with a leading zero if necessary
     *
     * @returns the current time as a string
     */
    String getCurrentTimeString();
};