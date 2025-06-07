void setup() {
  Serial.begin(9600);  // Inicia el puerto serial
}

void loop() {
  Serial.println("Hola desde Arduino");
  delay(1000);  // Espera 1 segundo
}
