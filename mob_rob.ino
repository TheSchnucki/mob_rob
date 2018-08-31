
#define runEvery(t) for (static long _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))

uint32_t timer;

void setup() {
  initMotors();
  initSensor();

}

void loop() {
  //driveForward (50);
  showAccelData();
  showGyroData();

  delay(1000);

}
