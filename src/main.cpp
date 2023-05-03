#include <Arduino.h>
#include <SetupPWM.h>
#include <SetupDistanceSensors.h>
#include "BluetoothSerial.h"

#define MAX_CHARS 3

char charVector[MAX_CHARS];
int charIndex = 0;
bool isReading = false;
char myChar;

String stringPWM = "";

BluetoothSerial SerialBT;
TaskHandle_t Task1;

void readAllSensors();
void Task1code(void *pvParameters);
void validationPWM();

void setup()
{
  disableCore1WDT();
  disableCore0WDT();
  SerialBT.begin("Bot3.0");

  xTaskCreatePinnedToCore(
      Task1code, /* Task function. */
      "Task1",   /* name of task. */
      10000,     /* Stack size of task */
      NULL,      /* parameter of the task */
      1,         /* priority of the task */
      &Task1,    /* Task handle to keep track of created task */
      0);        /* pin task to core 0 */

  setupInputsDriver();
  setupPWM();

  // Serial.begin(9600);
  // Serial.println("Iniciando Bot");
}

void loop()
{
  if (SerialBT.available())
  {
    myChar = SerialBT.read();
    if (myChar == '#') // "60"
    {
      isReading = !isReading;
      charIndex = 0;
    }
    else if (isReading && charIndex < MAX_CHARS)
    {
      charVector[charIndex] = myChar;
      charIndex++;
    }

    if (myChar == '#' && !isReading)
    {
      for (int i = 0; i < MAX_CHARS; i++)
      {
        stringPWM = stringPWM + charVector[i];
        charVector[i] = 0;
      }
      valuePWM = stringPWM.toInt();
      Serial.println(stringPWM.toInt());
      stringPWM = "";
    }

    switch (myChar)
    {
    case 'U':
      forwardDirection();
      break;
    case 'D':
      backwardDirection();
      break;
    case 'L':
      leftDirection();
      break;
    case 'R':
      rightDirection();
      break;
    case 'S':
      stopSlowly();
      break;
    case 'X':
      stopEmergency();
      break;
    default:
      stopEmergency();
      break;
    }
  }
}

void Task1code(void *pvParameters)
{
  setID();
  for (;;)
  {
    readAllSensors();
  }
}

void readAllSensors()
{
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  lox3.rangingTest(&measure3, false);
  lox4.rangingTest(&measure4, false);

  // ******************************* Sensor 1 ***************************** //
  if (measure1.RangeStatus != 4)
  {
    lox1_distance = measure1.RangeMilliMeter;

    if (lox1_distance < DISTANCE && flag1_distance == false && myChar == 'U')
    {
      stopEmergencyBreakForward();
      flag1_distance = true;
    }

    if (lox1_distance < DISTANCE && flag1_distance == false && myChar == 'S')
    {
      stopEmergencyBreakForwardLow();
      flag1_distance = true;
    }

    if (lox1_distance > DISTANCE)
    {
      flag1_distance = false;
    }
  }

  // ******************************* Sensor 2 ***************************** //
  if (measure2.RangeStatus != 4)
  {
    lox2_distance = measure2.RangeMilliMeter;

    if (lox2_distance < DISTANCE && flag2_distance == false && myChar == 'D')
    {
      stopEmergencyBreakBackward();
      flag2_distance = true;
    }

    if (lox2_distance < DISTANCE && flag2_distance == false && myChar == 'S')
    {
      stopEmergencyBreakBackwardLow();
      flag2_distance = true;
    }

    if (lox2_distance > DISTANCE)
    {
      flag2_distance = false;
    }
  }

  // ******************************* Sensor 3 ***************************** //
  if (measure3.RangeStatus != 4)
  {
    lox3_distance = measure3.RangeMilliMeter;
    if (lox3_distance < DISTANCE)
    {
      flagPwmEnableC = true;
    }
    else
    {
      flagPwmEnableC = false;
    }
    if (lox3_distance < DISTANCE && flag3_distance == false)
    {
      stopEmergency();
      flag3_distance = true;
    }
    else
    {
      flag3_distance = false;
    }
  }
  else
  {
    flag3_distance = false;
  }

  // ******************************* Sensor 4 ***************************** //
  if (measure4.RangeStatus != 4)
  {
    lox4_distance = measure4.RangeMilliMeter;
    if (lox4_distance < DISTANCE)
    {
      flagPwmEnableD = true;
    }
    else
    {
      flagPwmEnableD = false;
    }
    if (lox4_distance < DISTANCE && flag4_distance == false)
    {
      stopEmergency();
      flag4_distance = true;
    }
    else
    {
      flag4_distance = false;
    }
  }
  else
  {
    flag4_distance = false;
  }

  // Serial.println("A: " + String(lox1_distance) + " B: " + String(lox2_distance) + " C: " + String(lox3_distance) + " D: " + String(lox4_distance));
}