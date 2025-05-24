#include <LiquidCrystal_PCF8574.h>
#include "Button.h"
#include "Time.h"

// PINS
byte VRx = A1;
byte VRy = A0;
byte sw = 10;
byte buzz = 6;

Button button = Button(sw, 10);
LiquidCrystal_PCF8574 lcd(0x27);

const int buffer = 200;

// CURRENT MODE ENUM
enum Mode {
  DISPLAY_MODE, 
  CHANGE_TIME_MODE,
  SET_ALARM_MODE,
  ALARM_MODE
} currentMode = DISPLAY_MODE;

// TIMERS
unsigned long long int nextMin = 60000,
time = 0,
lastChange = 0;

Time currentTime = Time(0,0);
Time alarmTime = Time(0,0);
bool hasAlarm = false;

void displayTime(Time& timeToDisplay) {
  lcd.setCursor(4,0);
  lcd.print(timeToDisplay.getCurrentTimeString());
}

void updateDisplay() {
  if (button.justReleased) {
    lcd.clear();
  }
  
  if (currentMode == DISPLAY_MODE) {
    displayTime(currentTime);
  } if (currentMode == CHANGE_TIME_MODE) {
    displayTime(currentTime);
    lcd.setCursor(2,1);
    lcd.print("CHANGE TIME..");
  } else if (currentMode == SET_ALARM_MODE) {
    displayTime(alarmTime);
    lcd.setCursor(2,1);
    lcd.print("SET ALARM..");
  } else if (currentMode == ALARM_MODE) {
    if ((time >> 9) % 2 == 0) {
      displayTime(currentTime);
      lcd.setCursor(1,1);
      lcd.print("TAP TO SNOOZE");
    } else { 
      lcd.clear();
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.setBacklight(255);
  lcd.home();
  lcd.clear();

  updateDisplay();
  
  pinMode(sw, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);

  Serial.begin(9600);
}

void displayMode() {
  // Early return if there's an alarm
  // This prevents a case where an alarm is triggered at the same time the user changes modes
  if (hasAlarm && Time::areTimesEqual(currentTime, alarmTime)) {
    currentMode = ALARM_MODE;
    return;
  }

  if (time > nextMin) {
    nextMin += 60000;
    currentTime.incrementMinutes(1);
    updateDisplay();
  }

  if (button.justReleased) {
    if (button.holdTime <= 500) {
      currentMode = SET_ALARM_MODE;
    } else {
      currentMode = CHANGE_TIME_MODE;
    }
  }
}

void setAlarmMode() {
  // testing
  if (time - lastChange > buffer) {
    if (analogRead(VRy) < 100) {
      lastChange = time;
      alarmTime.incrementMinutes(1);
    }

    if (analogRead(VRy) > 1000) {
      lastChange = time;
      alarmTime.incrementMinutes(-1);
    }

    // to the right
    if (analogRead(VRx) > 1000) {
      lastChange = time;
      alarmTime.incrementHours(1);
    }

    // to the left
    if (analogRead(VRx) < 100) {
      lastChange = time;
      alarmTime.incrementHours(-1);
    }
  }

  if (button.justReleased) {
    // logic for setting the alarm
    hasAlarm = true;
    currentMode = DISPLAY_MODE;
  }

  updateDisplay();
}

void alarmMode() {
  if ((time >> 9) % 2 == 0) {
    digitalWrite(buzz, HIGH);
  } else { 
    digitalWrite(buzz, LOW); 
  }

  if (button.justReleased) {
    if (button.holdTime < 500) {
      // SNOOZE! hasalarm is still true.
      alarmTime.incrementMinutes(5);
    } else {
      hasAlarm = false;
    }

    currentMode = DISPLAY_MODE;
    digitalWrite(buzz, LOW); 
  }

  updateDisplay();
}

void changeTimeMode() {
  // testing
  if (time - lastChange > buffer) {
    if (analogRead(VRy) < 100) {
      lastChange = time;
      currentTime.incrementMinutes(1);
    }

    if (analogRead(VRy) > 1000) {
      lastChange = time;
      currentTime.incrementMinutes(-1);
    }

    // to the right
    if (analogRead(VRx) > 1000) {
      lastChange = time;
      currentTime.incrementHours(1);
    }

    // to the left
    if (analogRead(VRx) < 100) {
      lastChange = time;
      currentTime.incrementHours(-1);
    }
    
  }

  if (button.justReleased) {
    nextMin = time + 60000;
    currentMode = DISPLAY_MODE;
  }
  updateDisplay();
}

void loop() {
  time = millis();

  button.update();
  // button.print_debug();

  switch (currentMode) {
    case DISPLAY_MODE:
      displayMode();
      break;
    case CHANGE_TIME_MODE:
      changeTimeMode();
      break;
    case SET_ALARM_MODE:
      setAlarmMode();
      break;
    case ALARM_MODE:
      alarmMode();
      break;
  }
}
