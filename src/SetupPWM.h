#define ENABLE_A 13
#define ENABLE_B 12
#define ENABLE_C 14
#define ENABLE_D 27

#define INPUT_1 26 
#define INPUT_2 25
#define INPUT_3 33
#define INPUT_4 32
#define INPUT_5 5
#define INPUT_6 18
#define INPUT_7 3
#define INPUT_8 1

const int freq = 5000;
const int pwmChannel0 = 0;
const int pwmChannel1 = 1;
const int pwmChannel2 = 2;
const int pwmChannel3 = 3;
const int resolution = 8;

bool flagPwmEnableA = false;
bool flagPwmEnableB = false;
bool flagPwmEnableC = false;
bool flagPwmEnableD = false;

void setupPWM() {
  ledcSetup(pwmChannel0, freq, resolution);
  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);
  ledcSetup(pwmChannel3, freq, resolution);
  ledcAttachPin(ENABLE_A, pwmChannel0);
  ledcAttachPin(ENABLE_B, pwmChannel1);
  ledcAttachPin(ENABLE_C, pwmChannel2);
  ledcAttachPin(ENABLE_D, pwmChannel3);
}

void setupInputsDriver() {
  pinMode(INPUT_1, OUTPUT);
  digitalWrite(INPUT_1, LOW);
  pinMode(INPUT_2, OUTPUT);
  digitalWrite(INPUT_2, LOW);
  pinMode(INPUT_3, OUTPUT);
  digitalWrite(INPUT_3, LOW);
  pinMode(INPUT_4, OUTPUT);
  digitalWrite(INPUT_4, LOW);
  pinMode(INPUT_5, OUTPUT);
  digitalWrite(INPUT_5, LOW);
  pinMode(INPUT_6, OUTPUT);
  digitalWrite(INPUT_6, LOW);
  pinMode(INPUT_7, OUTPUT);
  digitalWrite(INPUT_7, LOW);
  pinMode(INPUT_8, OUTPUT);
  digitalWrite(INPUT_8, LOW);
}

void forwardDirection() {
  digitalWrite(INPUT_1, HIGH);
  digitalWrite(INPUT_3, HIGH);
  digitalWrite(INPUT_5, HIGH);
  digitalWrite(INPUT_7, HIGH);
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
    {
      ledcWrite(pwmChannel0, dutyCycle);
      ledcWrite(pwmChannel1, dutyCycle);
      ledcWrite(pwmChannel2, dutyCycle);
      ledcWrite(pwmChannel3, dutyCycle);
    }
}

void backwardDirection() {
  digitalWrite(INPUT_2, HIGH);
  digitalWrite(INPUT_4, HIGH);
  digitalWrite(INPUT_6, HIGH);
  digitalWrite(INPUT_8, HIGH);
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
    {
      ledcWrite(pwmChannel0, dutyCycle);
      ledcWrite(pwmChannel1, dutyCycle);
      ledcWrite(pwmChannel2, dutyCycle);
      ledcWrite(pwmChannel3, dutyCycle);
    }
}

void leftDirection() {

}

void rightDirection() {

}

void stopEmergency() {
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
    {
      ledcWrite(pwmChannel3, dutyCycle);
    }
  digitalWrite(INPUT_1, LOW);
  digitalWrite(INPUT_2, LOW);
  digitalWrite(INPUT_3, LOW);
  digitalWrite(INPUT_4, LOW);
  digitalWrite(INPUT_5, LOW);
  digitalWrite(INPUT_6, LOW);
  digitalWrite(INPUT_7, LOW);
  digitalWrite(INPUT_8, LOW);
}

void testingPWM() {
  
    
}