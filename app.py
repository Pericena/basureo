from flask import Flask, render_template, jsonify
import serial
import threading

app = Flask(__name__)

arduino_msg = "Esperando datos..."

def leer_serial():
    global arduino_msg
    try:
        arduino = serial.Serial('COM3', 9600)  # Cambia COM3 por el puerto real
        while True:
            linea = arduino.readline().decode('utf-8').strip()
            if linea:
                arduino_msg = linea
    except:
        arduino_msg = "No se pudo conectar al Arduino"

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/mensaje")
def mensaje():
    return jsonify({"mensaje": arduino_msg})

if __name__ == "__main__":
    hilo = threading.Thread(target=leer_serial)
    hilo.daemon = True
    hilo.start()
    app.run(debug=True)
