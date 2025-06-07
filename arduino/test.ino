#include <Ultrasonic.h>
#include <Servo.h>

Servo myservo;  
Ultrasonic ultrasonic(2, 3);
int distance;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  myservo.write(0);
}

void loop() {
  // Pass INC as a parameter to get the distance in inches
  distance = ultrasonic.read();
  if (distance <= 30){            // 30 es la distancia de su preferencia para detectar los objetos o personas acercandose a la caneca
    myservo.write(80);
    delay(4000);
    myservo.write(0);
  }
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(100);
}