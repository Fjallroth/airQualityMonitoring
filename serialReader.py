import csv
import serial
import time
import signal
import sys

def signal_handler(sig, frame):
    print("Keyboard Interrupt")
    sys.exit(0)

def main(usb_port, csv_filename, baud_rate=9600):
    with serial.Serial(usb_port, baud_rate) as ser:
        ser.flushInput()

        while True:
            try:
                ser_bytes = ser.readline()
                decoded_bytes = str(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
                print(decoded_bytes)
                print("\n")

                with open(csv_filename, "a") as f:
                    writer = csv.writer(f, delimiter=",")
                    print("\n\t")
                    localtime = time.asctime(time.localtime(time.time()))
                    writer.writerow([localtime, decoded_bytes])

            except KeyboardInterrupt:
                print("Keyboard Interrupt")
                break

if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main('/dev/ttyACM0', 'test_data.csv')