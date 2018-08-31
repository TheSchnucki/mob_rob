
#define runEvery(t) for (static long _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))

uint32_t timer;

double rollAngle;

void setup() {
  initMotors();
  initSensor();

}

void loop() {
  runEvery(10){
    RollAngle = 0.98 * (RollAngle + getGyroRoll())) + 0.02 * (getAccelRoll());
    timer = microns();

    
  }

}
