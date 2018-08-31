
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
