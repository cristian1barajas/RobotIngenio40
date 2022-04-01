#include "Adafruit_VL53L0X.h"
#include "SetupNeopixel.h"

// Distancia de referencia en mm
#define DISTANCE 50

// Direcciones I2C para sensores presentes
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33

// Ajuste de pines shutdown
#define SHT_LOX1 15
#define SHT_LOX2 2
#define SHT_LOX3 4
#define SHT_LOX4 16

// Objetos vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

// Medición de los sensores
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;

// Datos enteros de los sensores
int lox1_distance = 0;
int lox2_distance = 0;
int lox3_distance = 0;
int lox4_distance = 0;

// Banderas para ajustar parpadeo Neopixel
bool flag1_distance = false;
bool flag2_distance = false;
bool flag3_distance = false;
bool flag4_distance = false;

void setID()
{
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);

  // Serial.println(F("All in reset mode...(pins are low)"));
  // Serial.println(F("Starting..."));
  // Todos los sensores se reinician
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  delay(10);
  // Todos los sensores se habilitan
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  // Activando LOX1 y reiniciando LOX2 LOX3 y LOX4
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);

  // Iniciando LOX1
  if (!lox1.begin(LOX1_ADDRESS))
  {
    // Serial.println(F("Failed to boot first VL53L0X"));
    while (1)
      ;
  }
  delay(10);

  // Activando LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // Iniciando LOX2
  if (!lox2.begin(LOX2_ADDRESS))
  {
    // Serial.println(F("Failed to boot second VL53L0X"));
    while (1)
      ;
  }

  // Activando LOX3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  // Iniciando LOX3
  if (!lox3.begin(LOX3_ADDRESS))
  {
    // Serial.println(F("Failed to boot third VL53L0X"));
    while (1)
      ;
  }

  // Activando LOX4
  digitalWrite(SHT_LOX4, HIGH);
  delay(10);

  // Iniciando LOX4
  if (!lox4.begin(LOX4_ADDRESS))
  {
    // Serial.println(F("Failed to boot fourth VL53L0X"));
    while (1)
      ;
  }
}