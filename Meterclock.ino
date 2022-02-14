// (c) Joost van Stuijvenberg
//
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "DS1307.h"

#define MODE_NORMAL         0
#define MODE_METERS_MIN     1
#define MODE_METERS_MAX     2

#define LED1  5
#define LED2  6
#define LED3  7
#define LED1VALUE 135
#define LED2VALUE 63
#define LED3VALUE 135
#define METER1  9
#define METER2  10
#define METER3  11
#define BUTTON1 12
#define BUTTON2 13

DS1307 clock;
Adafruit_BMP280 bmp280;

  int mode;
  int led1value;
  int led2value;
  int led3value;

void setHours(int hours)
{
  double meter = (((double)hours / 40) * 255);
  analogWrite(METER1, meter);
}

void setMinutes(int minutes)
{
  double meter = ((double)minutes / 60) * 255;
  analogWrite(METER2, meter);  
}

void setSeconds(int seconds)
{
  double meter = ((double)seconds / 60) * 255;
  analogWrite(METER3, meter);  
}

void setup() {
  //clock.begin();
  //clock.fillByYMD(2022,1,12);//Jan 19,2013
  //clock.fillByHMS(15,45,00);//15:28 30"
  //clock.fillDayOfWeek(WED);//Saturday
  //clock.setTime();
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(METER1, OUTPUT);
  pinMode(METER2, OUTPUT);
  pinMode(METER3, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  mode = MODE_NORMAL;

  if (!bmp280.begin())
  {
    while(1);
  }
}

void loop() {  

    for (int s = 0; s < 590; s++)
    {         
      // Hours pointer shows temperature in degrees Celcius.
      double t = bmp280.readTemperature();
      clock.getTime();
      int hours = clock.hour;
      if (mode == MODE_NORMAL)
        setHours(hours);
      if (mode == MODE_METERS_MIN)
        setHours(0);
      if (mode == MODE_METERS_MAX)
        setHours(40);
  
      // Minutes pointer shows atmospheric pressure.
      double p = bmp280.readPressure() / 100000.0;
      double meter2 = p * 127;
      int minutes = clock.minute;
      if (mode == MODE_NORMAL)
        setMinutes(minutes);
      if (mode == MODE_METERS_MIN)
        setMinutes(0);
      if (mode == MODE_METERS_MAX)
        setMinutes(60);

      // Seconds pointer gradually increases.
      double meter3 = (s / 10) * (255 / 60);
      int seconds = clock.second;
      if (mode == MODE_NORMAL)
        setSeconds(seconds);
      if (mode == MODE_METERS_MIN)
        setSeconds(0);
      if (mode == MODE_METERS_MAX)
        setSeconds(60);

      if (mode == MODE_NORMAL)
      {
        led1value = LED1VALUE;
        led2value = 0;
        led3value = 0;
      }

      if (mode == MODE_METERS_MIN)
      {
        led1value = 0;
        led2value = LED2VALUE;
        led3value = 0;
      }

      if (mode == MODE_METERS_MAX)
      {
        led1value = 0;
        led2value = 0;
        led3value = LED3VALUE;
      }

      analogWrite(LED1, led1value);
      analogWrite(LED2, led2value);
      analogWrite(LED3, led3value);


      if (digitalRead(BUTTON1) == false)
      {
        while (!digitalRead(BUTTON1));
        if (mode == MODE_NORMAL)
          mode = MODE_METERS_MIN;
        else if (mode == MODE_METERS_MIN)
          mode = MODE_METERS_MAX;
        else if (mode == MODE_METERS_MAX)
          mode = MODE_NORMAL;
      }
  
      if (digitalRead(BUTTON2) == false)
      {
      }
      
      delay(100);
    }
}
