import serial
import time

try:
    arduino = serial.Serial(port='COM5', baudrate=9600, timeout=1)
    time.sleep(2)
    arduino.write(b'saludo\n')
    time.sleep(1)
    if arduino.in_waiting > 0:
        print("Arduino dice:", arduino.readline().decode().strip())
    else:
        print("⚠ Arduino no respondió")
except Exception as e:
    print(f"❌ Error: {e}")
