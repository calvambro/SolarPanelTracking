# (IoT) Solar Panel Tracker

An IoT-based solution that optimizes solar energy absorption by automatically adjusting solar panels' orientation using a tracking system. The system includes real-time monitoring of energy parameters for efficient energy utilization.

## Overview

This project utilizes Light Dependent Resistor (LDR) sensors, motor drivers, and a linear actuator to track the sun's movement from east to west, ensuring optimal energy absorption. Integrated current and voltage sensors provide real-time monitoring of energy parameters.

## ⚙️ Tech Stack

- ![Arduino IDE](https://img.shields.io/badge/Arduino-00979D?logo=arduino&logoColor=white)
- ![LDR Sensor](https://img.shields.io/badge/LDR%20Sensor-F8C300?logo=arduino&logoColor=white)
- ![Motor Driver](https://img.shields.io/badge/Motor%20Driver-FF4500?logo=raspberrypi&logoColor=white)
- ![Linear Actuator](https://img.shields.io/badge/Linear%20Actuator-808080?logo=raspberrypi&logoColor=white)
- ![Current Sensor](https://img.shields.io/badge/Current%20Sensor-FF6347?logo=arduino&logoColor=white)
- ![Voltage Sensor](https://img.shields.io/badge/Voltage%20Sensor-4682B4?logo=arduino&logoColor=white)

## Features

- **Automated Solar Panel Tracking**: Adjusts panel orientation based on sunlight direction.
- **Real-Time Energy Monitoring**: Displays current and voltage readings.
- **Energy Optimization**: Enhances energy absorption efficiency.
- **IoT Integration**: Enables remote monitoring and control.

## Setup

### Hardware

1. **LDR Sensors**: Detect sunlight intensity to determine panel orientation.
2. **Motor Driver**: Controls the movement of the linear actuator.
3. **Linear Actuator**: Adjusts the panel's position.
4. **Current Sensor**: Measures the current output from the solar panel.
5. **Voltage Sensor**: Measures the voltage output from the solar panel.

### Software

1. **Arduino IDE**: Program the microcontroller with the provided code.
2. **Upload Code**: Use the provided `.ino` files to upload to the Arduino board.

### Wiring

- Connect the LDR sensors to analog input pins.
- Interface the motor driver with the Arduino for controlling the actuator.
- Connect the current and voltage sensors to analog input pins for monitoring.

## Monitoring System

The system includes real-time monitoring of solar panel parameters:

- **Current and Voltage Readings**: Displayed on a connected display or sent to a cloud platform.
- **Data Logging**: Records energy data for analysis and optimization.
