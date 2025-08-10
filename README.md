# flood-risk-predictor
Flood risk detection system using ATMEGA328P and ultrasonic sensors to measure water level changes and predict flood risk.

# Flood Risk Predictor

A microcontroller-based system to detect and predict flood risk by monitoring the rate of change of water levels.

## Overview
This project uses an **ATMEGA328P** microcontroller with **ultrasonic sensors** to measure water levels in real time. By calculating the rate at which the water level changes, the system can predict potential flood conditions and alert users.

## Features
- Real-time water level measurement
- Calculates rate of change for flood prediction
- Simple hardware setup
- Low-cost, easily deployable system

## Hardware Used
- ATMEGA328P Microcontroller (Arduino Uno compatible)
- 16MHz Crystal Oscillator (For Clock Signal)
- 5V Voltage Regulator
- Ultrasonic Sensors (HC-SR04)
- DotBoard, Connection Wires, and power supply

## Software & Libraries
- Arduino IDE
- HC-SR04 Library

## How It Works
1. Ultrasonic sensor measures the distance to the water surface.
2. ATMEGA328P calculates water level changes over time.
3. If the change exceeds a threshold, the system predicts a possible flood.
4. Output is displayed/triggered via serial monitor and alert mechanism.

## Getting Started
1. Open `flood_risk_predictor.ino` in Arduino IDE.
2. Select **Arduino Uno** as the board and the correct COM port.
3. Upload the code to the ATMEGA328P.
4. Connect ultrasonic sensors according to the pin definitions in the code.
5. Open the Serial Monitor to view results.

## Demonstration
- [Demo Video](<iframe src="https://www.linkedin.com/embed/feed/update/urn:li:ugcPost:7315611456283045888" height="981" width="504" frameborder="0" allowfullscreen="" title="Embedded post"></iframe>)

## License
This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.
