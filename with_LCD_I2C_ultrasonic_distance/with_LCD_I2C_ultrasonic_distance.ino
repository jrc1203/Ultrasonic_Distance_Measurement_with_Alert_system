#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//..................define pin number......................//
const int trigPin = 9;
const int echoPin = 10;
const int led = 2;
const int buzzer = 3;

//....................defines variables....................//
long duration;
int distance;

void setup() {
  Serial.begin(9600);          // Starts the serial communication
  lcd.init();                  // initialise the lcd
  //lcd.begin(16,2);
  lcd.clear();
  lcd.backlight();

//...................defines pin modes........................//
  pinMode(trigPin, OUTPUT);    // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);     // Sets the echoPin as an Input
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  //.....................Ultrasonic Sensor Code.......................//
  // Initialise and Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);        //you can also use delay(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);       // This is the duration of the transmitted sound wave
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor and lcd
  Serial.print("Distance: ");
  Serial.println(distance);
  lcd.setCursor(0,0);
  lcd.print("Distance: ");

  //........................Alert System.............................//
  if (distance > 0 && distance <= 10) { //If obstacle under 10cm led and buzzer gives warning
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer,LOW);
    delay(500);
    Serial.println("DANGER!! STOP!! Obstacle under 10cm");
    lcd.setCursor(0,1);
    lcd.print("!!DANGER!!STOP!!");
  } 
  else if (distance > 10 && distance <= 25) { //If obstacle under 25cm only led glows for warning
    digitalWrite(led, HIGH);
    Serial.println("Alert! Obstacle in front under 25cm");
    lcd.setCursor(0,1);
    lcd.print("!Alert!!WARNING!");
  } 
  else {//Otherwise both turned off
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }
  delay(200);
  lcd.clear();
}