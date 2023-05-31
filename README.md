# Automatic Brake System with Servo Motor

This project implements an Automatic Brake System using an Arduino board and a servo motor. The system uses an ultrasonic sensor to detect obstacles and applies the brakes automatically when necessary. It also includes a manual brake option controlled by a potentiometer.

## Components Used

- Arduino board
- Servo motor
- Ultrasonic sensor
- Potentiometer
- LEDs (EBS LED, Manual LED, Warning LED)

## Circuit Connections

- Connect the Trig pin of the ultrasonic sensor to digital pin 4 of the Arduino.
- Connect the Echo pin of the ultrasonic sensor to digital pin 5 of the Arduino.
- Connect the control pin of the servo motor to digital pin 10 of the Arduino.
- Connect the potentiometer for brake control to analog pin 0 of the Arduino.
- Connect the potentiometer for car speed control to analog pin 1 of the Arduino.
- Connect the EBS LED to digital pin 8 of the Arduino.
- Connect the Manual LED to digital pin 9 of the Arduino.
- Connect the Warning LED to digital pin 11 of the Arduino.

## Usage

1. Upload the code to the Arduino board using the Arduino IDE.
2. Open the serial monitor to view the distance readings and other debug information.
3. Adjust the potentiometer for brake control to set the braking force or servo rotation manually.
4. Adjust the potentiometer for car speed control to set the car speed.
5. Observe the behavior of the system based on the distance readings and speed settings.

## Operation

- The ultrasonic sensor measures the distance to the obstacle and displays it on the serial monitor.
- The code contains different speed ranges and corresponding obstacle distances.
- If the obstacle is within the braking distance and the manual brake is not applied, the EBS LED lights up, and the servo motor applies the brakes gradually.
- If the manual brake is applied but not to the maximum, the EBS LED remains on, and the servo motor applies the remaining force to reach maximum braking.
- If the manual brake is applied to the maximum, the Manual LED lights up along with the EBS LED.
- If the obstacle is far away or the car speed is outside the defined ranges, the servo motor position is set based on the manual brake setting, and all LEDs are turned off.
