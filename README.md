# Air Quality Monitoring System

This repository contains code for an air quality monitoring system using Arduino. The system collects data from various sensors and sends it to a Python script via serial communication. The Python script saves the received data to a CSV file for further analysis.

## Hardware Requirements

- Arduino Mega (or any compatible board)
- MICS-VZ-89TE VOC and CO2 sensor
- DHT11 Temperature and Humidity sensor
- PMS5003 Particulate Matter sensor
- Breadboard and jumper wires

## Software Requirements

- Arduino IDE
- Python 3.x
- Python libraries: `pyserial`, `csv`

## Setup

1. Connect the sensors to the Arduino board as per their respective datasheets.
2. Upload the Arduino script (`air_quality_monitor.ino`) to the board using the Arduino IDE.
3. Connect the Arduino board to the computer via USB.
4. Update the USB port in the Python script (`serial_to_csv.py`) to match your system.
5. Run the Python script (`serial_to_csv.py`) to start collecting and saving data to the CSV file.

## Usage

The system continuously measures air quality parameters and sends the data to the Python script, which saves it to a CSV file named `test2.15_data.csv`. The saved data includes temperature, humidity, VOC, CO2, and particulate matter (PM1.0, PM2.5, PM10) levels.

Ensure that the Arduino board is connected to the computer, and the Python script is running to collect and save the data.

## Troubleshooting

- Check the USB port and update the Python script accordingly.
- Ensure all connections are secure and the sensors are functioning correctly.
- If the Python script is not receiving data, try resetting the Arduino board.
