#include <Ultrasonic.h> 
#include <Servo.h>

Servo myservo;  
Ultrasonic ultrasonic(2, 3); // TRIG pin 2, ECHO pin 3
int distance;

// Pines de los LEDs
int led1 = 6;  // LED que parpadea cuando detecta basura
int led2 = 7;  // LED secundario (opcional)

void setup() {
  myservo.attach(9);  // Servo en pin 9
  Serial.begin(9600);
  myservo.write(0);   // Posición inicial del servo (cerrado)

  // Configurar los LEDs como salida
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void loop() {
  distance = ultrasonic.read(); // Lee la distancia en cm

  // Serial.print("Distancia: ");
  // Serial.print(distance);
  // Serial.println(" cm");

    // Reemplaza los prints del loop por esto
  Serial.print("{\"distancia\": ");
  Serial.print(distance);
  Serial.print(", \"detecto\": ");
  Serial.print((distance > 1 && distance <= 20) ? 1 : 0);
  Serial.print(", \"servo\": ");
  Serial.print((distance > 1 && distance <= 20) ? 80 : 0);
  Serial.println("}");


  // Verificar si hay un objeto válido cerca (evitar lecturas erróneas como 0)
  if (distance > 1 && distance <= 20) {
    Serial.println("Basura detectada a menos de 20 cm");

    // Abrir tapa con el servo
    myservo.write(80);  // Abre la tapa

    // Parpadear LED en pin 6
    digitalWrite(led1, HIGH);
    delay(250);
    digitalWrite(led1, LOW);
    delay(250);

    // Encender LED secundario (opcional)
    digitalWrite(led2, HIGH);

    // Esperar a que el objeto desaparezca
    while (ultrasonic.read() <= 20) {
      delay(100);  // Espera activa hasta que ya no haya basura
    }

    // Cerrar la tapa
    myservo.write(0);
    Serial.println("Objeto retirado. Tapa cerrada.");

    // Apagar LEDs
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  } else {
    // No hay objeto: asegúrate de que el servo y los LEDs estén en estado de reposo
    myservo.write(0);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }

  delay(100);  // Pequeña pausa antes de la siguiente lectura
}