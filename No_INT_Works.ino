#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const byte ledPin = 13;
const byte buzzPin = 3;

//const byte interruptPin = 2;
volatile byte state = LOW;

void setup () {
  Serial.begin(9600);

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
pinMode(ledPin, OUTPUT);
pinMode(buzzPin, OUTPUT);
//pinMode(interruptPin, INPUT_PULLUP);
  
  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}


void loop () {

    
    //noInterrupts();
    
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

if (now.second() > 30){
  
  digitalWrite(ledPin, HIGH);
Buzz();
//  state = !state;

//  attachInterrupt(digitalPinToInterrupt(interruptPin) , blinky, CHANGE);
}
else{
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzPin, LOW);
  }

    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");

    Serial.println();
    delay(1000);
}
void Buzz(){
  digitalWrite(buzzPin, HIGH);
  delay(500);
  digitalWrite(buzzPin, LOW);
  delay(500);
  digitalWrite(buzzPin, HIGH);
  delay(500);
  digitalWrite(buzzPin, LOW);
  delay(500);
  digitalWrite(buzzPin, HIGH);
  delay(500);
  digitalWrite(buzzPin, LOW);
  delay(500);
  digitalWrite(buzzPin, HIGH);
  delay(500);
  digitalWrite(buzzPin, LOW);
  delay(500);
  }
//void blinky() {
//  state = !state;
//}
