#include <Ultrasonic.h>
#include <Servo.h>

Servo myservo;
Ultrasonic ultrasonic(2, 3);  // Trig: pin 2, Echo: pin 3

const int ledRojo = 5;
const int ledVerde = 4;
int distance;
bool abierto = false;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(0);  // Tapa cerrada

  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, LOW);
}

void loop() {
  distance = ultrasonic.read();

  // Enviar datos al dashboard
  Serial.print("{\"distancia\": ");
  Serial.print(distance);
  Serial.print(", \"detecto\": ");
  Serial.print((distance > 1 && distance <= 30) ? 1 : 0);
  Serial.print(", \"servo\": ");
  Serial.print(abierto ? 80 : 0);
  Serial.println("}");

  // Si se detecta algo a menos de 30 cm y la tapa está cerrada
  if (distance > 1 && distance <= 30 && !abierto) {
    abierto = true;

    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledVerde, HIGH);
    myservo.write(80);  // Abrir tapa
    delay(3000);        // Tiempo para botar la basura
  }

  // Esperar hasta que ya no haya nada cerca y la tapa esté abierta
  if (abierto && distance > 30) {
    myservo.write(0);  // Cerrar tapa
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledVerde, LOW);
    abierto = false;
  }

  delay(100);
}
