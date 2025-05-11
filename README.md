# IoT Solar Panel Tracker

An IoT-based solution that optimizes solar energy absorption by automatically adjusting solar panels' orientation using a tracking system. The system includes real-time monitoring of energy parameters for efficient energy utilization.

## Overview

This project utilizes an Arduino Mega, LDR sensors, a motor driver, and a linear actuator to track the sun's movement from east to west, ensuring optimal energy absorption. The monitoring system is implemented using an ESP32 with a PZEM-017 energy monitoring module to measure the solar panel's voltage, current, and energy usage in real-time.

## Project Images

![image](https://github.com/user-attachments/assets/286fc18f-26ed-4e2e-a78e-867e91933e06)


---

## IoT Configuration

![image](https://github.com/user-attachments/assets/37ec57f0-f7e4-48f3-af6f-cd74e9b6a3e5)


---

## Tech Stack

- ![Arduino Mega](https://img.shields.io/badge/Arduino%20Mega-00979D?logo=arduino&logoColor=white)
- ![LDR Sensor](https://img.shields.io/badge/LDR%20Sensor-F8C300?logo=arduino&logoColor=white)
- ![Motor Driver](https://img.shields.io/badge/Motor%20Driver-BTS7960-FF4500?logo=raspberrypi&logoColor=white)
- ![Linear Actuator](https://img.shields.io/badge/Linear%20Actuator-808080?logo=raspberrypi&logoColor=white)
- ![ESP32](https://img.shields.io/badge/ESP32-3C99DC?logo=espressif&logoColor=white)
- ![PZEM-017](https://img.shields.io/badge/PZEM017-4682B4?logo=arduino&logoColor=white)

## Features

- **Automated Solar Panel Tracking**: Adjusts panel orientation based on sunlight direction using 2 LDR sensors, an Arduino Mega, and a motor driver.
- **Real-Time Energy Monitoring**: Monitors solar panel energy consumption using the ESP32 and PZEM-017 module, with current, voltage, and energy data displayed in real-time.
- **Energy Optimization**: Enhances energy absorption efficiency by tracking the sun's movement.
- **IoT Integration**: Provides remote monitoring capabilities with the ESP32 and can send data to the cloud for visualization.

## Setup

### Tracking System (Arduino Mega)

1. **LDR Sensors**: Use two LDR (Light Dependent Resistor) sensors to detect sunlight and determine the panel's optimal position.
2. **Motor Driver**: The BTS7960 motor driver controls the linear actuator to move the solar panel.
3. **Linear Actuator**: Moves the solar panel to track the sun from east to west.

### Monitoring System (ESP32)

1. **PZEM-017 Energy Monitoring Module**: Measures the solar panel's current, voltage, and energy consumption in real-time.
2. **ESP32**: Used to process the data from the PZEM-017 module and send it to a cloud server or display the information locally.

### Software

1. **Arduino IDE**: Program the Arduino Mega for solar panel tracking with the LDR sensors and motor driver.
2. **ESP32 Code**: Upload the code for the ESP32 to handle energy monitoring and data transmission using the PZEM-017 module.

### Wiring

1. **Arduino Mega**: 
   - Connect the LDR sensors to analog input pins.
   - Interface the BTS7960 motor driver with the Arduino to control the linear actuator.
   - Connect the motor driver to control the actuator movement.

2. **ESP32**:
   - Connect the PZEM-017 module to the ESP32 via UART or RS485 for real-time energy monitoring.

## Monitoring System

The system includes real-time monitoring of solar panel parameters:

- **Current and Voltage Readings**: Sent from the PZEM-017 energy monitoring module via the ESP32.
- **Energy Monitoring**: Displays energy data for real-time visualization.
- **Data Logging**: Records energy data for future analysis and optimization.
