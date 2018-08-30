#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>

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

  /* Note: You can also get the raw (non unified values) for */
  /* the last data sample as follows. The .getEvent call populates */
  /* the raw values used below. */
  //Serial.print("X Raw: "); Serial.print(accel.raw.x); Serial.print("  ");
  //Serial.print("Y Raw: "); Serial.print(accel.raw.y); Serial.print("  ");
  //Serial.print("Z Raw: "); Serial.print(accel.raw.z); Serial.println("");
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
