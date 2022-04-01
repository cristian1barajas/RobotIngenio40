#define ENABLE_A 13
#define ENABLE_B 12

const int freq = 5000;
const int pwmChannel = 0;
const int resolution = 8;

bool flagPwmMotor1 = false;
bool flagPwmMotor2 = false;
bool flagPwmMotor3 = false;
bool flagPwmMotor4 = false;

void setupPWM() {
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(ENABLE_A, pwmChannel);
  ledcAttachPin(ENABLE_B, pwmChannel);
}