#include <Arduino.h>
#include <SetupPWM.h>
#include <SetupDistanceSensors.h>

void readAllSensors();

void setup()
{
  disableCore1WDT();

  strip.Begin();
  strip.Show();

  setID();
}

void loop()
{
  readAllSensors();
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
      flagPwmMotor1 = true;
    }
    else
    {
      flagPwmMotor1 = false;
    }
    if (lox1_distance < DISTANCE && flag1_distance == false)
    {
      highPixels1();
      flag1_distance = true;
    }
    else
    {
      lowPixels1();
      flag1_distance = false;
    }
  }
  else
  {
    lowPixels1();
    flag1_distance = false;
  }

  // ******************************* Sensor 2 ***************************** //
  if (measure2.RangeStatus != 4)
  {
    lox2_distance = measure2.RangeMilliMeter;
    if (lox2_distance < DISTANCE)
    {
      flagPwmMotor2 = true;
    }
    else
    {
      flagPwmMotor2 = false;
    }
    if (lox2_distance < DISTANCE && flag2_distance == false)
    {
      highPixels2();
      flag2_distance = true;
    }
    else
    {
      lowPixels2();
      flag2_distance = false;
    }
  }
  else
  {
    lowPixels2();
    flag2_distance = false;
  }

  // ******************************* Sensor 3 ***************************** //
  if (measure3.RangeStatus != 4)
  {
    lox3_distance = measure3.RangeMilliMeter;
    if (lox3_distance < DISTANCE)
    {
      flagPwmMotor3 = true;
    }
    else
    {
      flagPwmMotor3 = false;
    }
    if (lox3_distance < DISTANCE && flag3_distance == false)
    {
      highPixels3();
      flag3_distance = true;
    }
    else
    {
      lowPixels3();
      flag3_distance = false;
    }
  }
  else
  {
    lowPixels3();
    flag3_distance = false;
  }

  // ******************************* Sensor 4 ***************************** //
  if (measure4.RangeStatus != 4)
  {
    lox4_distance = measure4.RangeMilliMeter;
    if (lox4_distance < DISTANCE)
    {
      flagPwmMotor4 = true;
    }
    else
    {
      flagPwmMotor4 = false;
    }
    if (lox4_distance < DISTANCE && flag4_distance == false)
    {
      highPixels4();
      flag4_distance = true;
    }
    else
    {
      lowPixels4();
      flag4_distance = false;
    }
  }
  else
  {
    lowPixels4();
    flag4_distance = false;
  }
}
