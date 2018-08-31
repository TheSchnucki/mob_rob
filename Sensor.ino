#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>

float accelX, accelY, accelZ;
float accelBiasX, accelBiasY, accelBiasZ;
double accelRoll = 0.0;

float gyroX = 0.0, gyroY = 0.0, gyroZ = 0.0;
float gyroBiasX = 0.0, gyroBiasY = 0.0, gyroBiasZ = 0.0;
float gyroRoll = 0.0, gyroRate = 0.0;

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

void displayAccelSensorDetails(void)
{
  sensor_t accelSensor;
  accel.getSensor(&accelSensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(accelSensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(accelSensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(accelSensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(accelSensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(accelSensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(accelSensor.resolution); Serial.println(" m/s^2");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(100);
}

void displayGyroSensorDetails(void)
{
  sensor_t gyroSensor;
  gyro.getSensor(&gyroSensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(gyroSensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(gyroSensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(gyroSensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(gyroSensor.max_value); Serial.println(" rad/s");
  Serial.print  ("Min Value:    "); Serial.print(gyroSensor.min_value); Serial.println(" rad/s");
  Serial.print  ("Resolution:   "); Serial.print(gyroSensor.resolution); Serial.println(" rad/s");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void initSensor(void)
{
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  // ACCEL Block
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");

  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }

  displayAccelSensorDetails();

  //GYRO Block
  Serial.println("Gyroscope Test"); Serial.println("");
  
  /* Enable auto-ranging */
  gyro.enableAutoRange(true);
  
  /* Initialise the sensor */
  if(!gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.println("Ooops, no L3GD20 detected ... Check your wiring!");
    while(1);
  }
  
  displayGyroSensorDetails();

  showAccelData();
  showGyroData();
  

  biasValues();
  getAccelRoll();
}

// get initial values as bias
void biasValues() {

  //gettin a mean value from 100 measurements
  for(int i = 0; i<100; i++) {

    getAccelData();
    accelBiasX += accelX;
    accelBiasY += accelY;
    accelBiasZ += accelZ;
    
    getGyroData();
    gyroBiasX += gyroX;
    gyroBiasY += gyroY;
    gyroBiasZ += gyroZ;
  }

  Serial.println();
  
  accelBiasX = accelBiasX / 100;
  accelBiasY = accelBiasY / 100;
  accelBiasZ = accelBiasZ / 100;

  gyroBiasX = gyroBiasX / 100;
  gyroBiasY = gyroBiasY / 100;
  gyroBiasZ = gyroBiasZ / 100;
  
  // Log output
  Serial.print("Accel Bias  ");
  Serial.print("X: "); Serial.print(accelBiasX); Serial.print("  ");
  Serial.print("Y: "); Serial.print(accelBiasY); Serial.print("  ");
  Serial.print("Z: "); Serial.print(accelBiasZ); Serial.print("  ");

  Serial.println();

  Serial.print("Gyro Bias  ");
  Serial.print("X: "); Serial.print(gyroBiasX); Serial.print("  ");
  Serial.print("Y: "); Serial.print(gyroBiasY); Serial.print("  ");
  Serial.print("Z: "); Serial.print(gyroBiasZ); Serial.print("  ");

  Serial.println();

  delay(100);
}

// unfinished
void startValues() {
  sensors_event_t accelEvent;

  for(int i = 1; i<100; i++) {
    accel.getEvent(&accelEvent);
    accelRoll = (atan2(accelEvent.acceleration.y - accelBiasY,
                      -(accelEvent.acceleration.z - accelBiasZ)) + PI) * RAD_TO_DEG;
  }
  
}

void getAccelData(void){
  /* Get a new sensor event */ 
  sensors_event_t accelEvent; 
  gyro.getEvent(&accelEvent);

  accelX = accelEvent.acceleration.x;
  accelY = accelEvent.acceleration.y;
  accelZ = accelEvent.acceleration.z;
}

double getAccelRoll(void){
  /* Get a new sensor event */ 
  sensors_event_t accelEvent; 
  gyro.getEvent(&accelEvent);

  accelRoll = (atan2(accelEvent.acceleration.y, -accelEvent.acceleration.z)+PI)*RAD_TO_DEG;

  if (accelRoll <= 360 && accelRoll >=180){
    accelRoll = accelRoll - 360;
  }

  return accelRoll;
}

void getGyroData(void){
  /* Get a new sensor event */ 
  sensors_event_t gyroEvent; 
  gyro.getEvent(&gyroEvent);

  gyroX = gyroEvent.gyro.x;
  gyroY = gyroEvent.gyro.y;
  gyroZ = gyroEvent.gyro.z;
}

double getGyroRoll(void){
  getGyroData();

  gyroRate = -(gyroX-gyroBiasX)*0,07;
  gyroRoll += gyroRate * (micros()-timer/1000000);

  return gyroRoll;
}

void showAccelData(void)
{
  /* Get a new sensor event */
  sensors_event_t accelEvent;
  accel.getEvent(&accelEvent);

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(accelEvent.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(accelEvent.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(accelEvent.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
}

void showGyroData(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t gyroEvent; 
  gyro.getEvent(&gyroEvent);
 
  /* Display the results (speed is measured in rad/s) */
  Serial.print("X: "); Serial.print(gyroEvent.gyro.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(gyroEvent.gyro.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(gyroEvent.gyro.z); Serial.print("  ");
  Serial.println("rad/s ");
}
