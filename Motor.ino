// Pin-out for L298N
int ENA = 9;
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int ENB = 10;

void initMotors() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void driveForward (int testSpeed) {
  analogWrite (ENA, testSpeed);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite (ENB, testSpeed); 
}

void driveBackward(int testSpeed) {
  analogWrite (ENA, testSpeed);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite (ENB, testSpeed);
  
}

