from flask import Flask, jsonify, render_template, request
import serial
import threading
import json

app = Flask(__name__)
arduino_data = {"distancia": 0, "detecto": 0, "servo": 0, "botellas": 0}

# Simulación o conexión real al puerto serie
def leer_serial():
    global arduino_data
    try:
        arduino = serial.Serial('COM3', 9600)  # O Linux: '/dev/ttyUSB0'
        while True:
            linea = arduino.readline().decode('utf-8').strip()
            if linea.startswith("{") and linea.endswith("}"):
                try:
                    arduino_data.update(json.loads(linea))
                except json.JSONDecodeError:
                    pass
    except serial.SerialException:
        print("No se pudo conectar al puerto serial")

@app.route("/datos")
def datos():
    return jsonify(arduino_data)

@app.route("/update_botellas", methods=["POST"])
def update_botellas():
    global arduino_data
    data = request.get_json()
    if "cantidad" in data:
        arduino_data["botellas"] = data["cantidad"]
    return jsonify(success=True, cantidad=arduino_data["botellas"])

@app.route("/")
def dashboard():
    return render_template("dashboard.html")

if __name__ == "__main__":
    hilo_serial = threading.Thread(target=leer_serial)
    hilo_serial.daemon = True
    hilo_serial.start()
    app.run(debug=True)
