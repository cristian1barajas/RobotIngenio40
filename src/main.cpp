#include <Arduino.h>
#include <SetupPWM.h>
#include <SetupDistanceSensors.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
TaskHandle_t Task1;

void readAllSensors();
void Task1code(void *pvParameters);

void setup()
{
  disableCore1WDT();
  disableCore0WDT();

  SerialBT.begin("ESP32test");

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
}

void loop()
{
  if (SerialBT.available())
  {
    char myChar = SerialBT.read();
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
      stopEmergency();
      break;
    default:
      stopEmergency();
      break;
    }
  }
  // testingPWM();
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
    if (lox1_distance < DISTANCE)
    {
      flagPwmEnableA = true;
    }
    else
    {
      flagPwmEnableA = false;
    }
    if (lox1_distance < DISTANCE && flag1_distance == false)
    {
      stopEmergency();
      flag1_distance = true;
    }
    else
    {
      flag1_distance = false;
    }
  }
  else
  {
    flag1_distance = false;
  }

  // ******************************* Sensor 2 ***************************** //
  if (measure2.RangeStatus != 4)
  {
    lox2_distance = measure2.RangeMilliMeter;
    if (lox2_distance < DISTANCE)
    {
      flagPwmEnableB = true;
    }
    else
    {
      flagPwmEnableB = false;
    }
    if (lox2_distance < DISTANCE && flag2_distance == false)
    {
      stopEmergency();
      flag2_distance = true;
    }
    else
    {
      flag2_distance = false;
    }
  }
  else
  {
    flag2_distance = false;
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
}