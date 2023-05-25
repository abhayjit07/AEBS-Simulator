#include <Servo.h> //servo motor library

const int trigPin = 4; // DEFINE Trigger pin
const int echoPin = 5; // DEFINE Echo pin

long duration; // variable for travel time
int distance;  // variable for distance

Servo servo; // naming the servo motor, it declares an object of servo class.

int potPina = 0;   // potentiometer connected to Analog pin 0
int val_0;         // variable to read the value from the analog pin 0,(the brake value applied)
int val_max = 179; // variable to hold maximum value of the servo motor

int potPinb = 1; // potentiometer connected to A1
int val_speed;   // variable to read the value from the analog pin 1,(the carspeed given)

// LED pin
int led = 8;  //LED corresponding to EBS is connected to digital pin 8.
int manual_led = 9; //LED corresponding to manual braking is connected to digital pin 9.
int warning_led = 11;

void setup()
{
    //This block of code is executed once , this mainly contains statements
    //that set the pin modes on the Arduino to OUTPUT and INPUT.
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    servo.attach(10);            // servo pin
    pinMode(led, OUTPUT);        // led as output
    pinMode(manual_led, OUTPUT); // manual led as output
    Serial.begin(9600);          // Serial communication to see the results on serial monitor
}

void loop()
{
  // This block of code is executed repeatedly.The program starts from '{' and
  //runs till '}' , then jumps back again to the starting. It continues to loop 
  //until we stop the simulation.
  
    digitalWrite(trigPin, LOW); // Trig pin is clear.
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH); // Generating the ultrasound wave
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // reading the travel time
    duration = pulseIn(echoPin, HIGH); // reads the travel time of ultrasonic wave and 
                                       // stores it in variable duration.
    distance = duration * 0.034 / 2;   // calculates the distance based on travel time 
                                       // and stores it in variable distance.
    // Printing the distance in the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    // servo motor controlled by the potentiometer
    val_0 = analogRead(potPina);         // reads the value of the
                                         // potentiometer (value between
                                         // 0 and 1023)
    val_0 = map(val_0, 0, 1023, 0, 179); // scale it to use it with
                                         // the servo (value between 0 and 179)
                                         // sets the servo position according
                                         // to the scaled value
    // waits for the servo to get there
    Serial.print("Val_0: ");
    Serial.print(val_0); // val_0 = braking force or servo rotation given manually.
    Serial.print("; ");

    val_speed = analogRead(potPinb);             // reads the value of the
                                                 // potentiometer (value between
                                                 // 0 and 1023)
    val_speed = map(val_speed, 0, 1023, 0, 100); // scale it to use it with
                                                 // as the speed (value between 0 and 100)

    Serial.print("CarSpeed: ");
    Serial.print(val_speed); // val_speed = Carspeed
    Serial.print("; ");

    switch (val_speed) // CarSpeed
    {

    // 1.5m = (0.15m) obstacle distance and speed of 5 Kmh
    case 1 ... 5: 
      //The below if block operates the warning LED , if the obstacle is detected it blinks the
      //warning LED from a certain offset distance and prompts the driver to apply manual brake.
        if(distance<=16.5 && distance>15 && val_speed<=5)
        {
          digitalWrite(warning_led,HIGH);
          delay(300);                     //Warning LED Blinks
          digitalWrite(warning_led,LOW);
          delay(300);
        }
      
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS NOT APPLIED
        // The  else if block below is executed If the obstacle comes within braking distance and 
        //still the manual brake is not applied, then the EBS led lights up and EBS is applied
        else if (distance <= 15 && val_0 == 0 && val_speed <= 5)
        {
            digitalWrite(warning_led, LOW);      //Stops warning LED
            digitalWrite(led, HIGH);             //Lights EBS LED
            servo.write(val_max);
        }
      
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS APPLIED BUT NOT TO THE MAXIMUM
        else if (distance <= 15 && val_0 > 0 && val_speed <= 5)
        {
            digitalWrite(warning_led, LOW);      //Stops warning LED
            //The for loop  below makes sure the servo rotates to its maximum value
            //In other words the brake is applied fully by EBS.
            for (int i = val_0; i <= val_max; i++)
            {
                servo.write(val_max); // servo to 179 degrees
            }
          
            // The following if block checks if the manual brake is applied to its maximum or not.
            //If yes, the Manual LED lights up.
            if (val_0 == 179)
            {
                digitalWrite(manual_led, HIGH);   //Lights Manual LED
            }
            //If no, then the else block below is executed , both Digital and Manual LED lights up.
            else
            {
                digitalWrite(led, HIGH);           //Lights EBS LED     
                digitalWrite(manual_led, HIGH);     //Lights Manual LED        
            }
        }
        //If the obstacle is far away then the code stays in the following else condition.
        else
        {
            servo.write(val_0);
            digitalWrite(led, LOW);
            digitalWrite(manual_led, LOW);        //All three LEDs remain OFF.
            digitalWrite(warning_led, LOW);
        }
        break;

    // 6m = (0.4m)obstacle distance and speed of 15 Kmh
    case 6 ... 15:
      //The below if block operates the warning LED , if the obstacle is detected it blinks the
      //warning LED from a certain offset distance and prompts the driver to apply manual brake.
        if(distance<=44 && distance>40 && val_speed<=15)
        {
          digitalWrite(warning_led,HIGH);
          delay(300);
          digitalWrite(warning_led,LOW);
          delay(300);
        }
         // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS NOT APPLIED
      // The  else if block below is executed If the obstacle comes within braking distance and 
        //still the manual brake is not applied, then the EBS led lights up and EBS is applied
        else if (distance <= 40 && val_0 == 0 && val_speed <= 15)
        {
            digitalWrite(warning_led, LOW);            
            digitalWrite(led, HIGH);
            servo.write(val_max);
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS APPLIED BUT NOT TO THE MAXIMUM
        else if (distance <= 40 && val_0 > 0 && val_speed <= 15)
        {
            digitalWrite(warning_led, LOW);   
          //The for loop  below makes sure the servo rotates to its maximum value
            //In other words the brake is applied fully by EBS.
            for (int i = val_0; i <= val_max; i++)
            {
                servo.write(val_max); // servo to 179 degrees
            }
            
            // The following if block checks if the manual brake is applied to its maximum or not.
            //If yes, the Manual LED lights up.
            if (val_0 == 179)
            {
                digitalWrite(manual_led, HIGH);
             }
            //If no, then the else block below is executed , both Digital and Manual LED lights up.
            else
            {
                digitalWrite(led, HIGH);                
                digitalWrite(manual_led, HIGH);                
            }
        }
        //If the obstacle is far away then the code stays in the following else condition.
        else
        {
            servo.write(val_0);
            digitalWrite(led, LOW);
            digitalWrite(manual_led, LOW);
            digitalWrite(warning_led, LOW);          
        }
        break;

    // 15m = (0.9m)obstacle distance and speed of 30 Kmh
    case 16 ... 30: 
      //The below if block operates the warning LED , if the obstacle is detected it blinks the
      //warning LED from a certain offset distance and prompts the driver to apply manual brake.
        if(distance<=99 && distance>90 && val_speed<=30)
        {
          digitalWrite(warning_led,HIGH);
          delay(300);
          digitalWrite(warning_led,LOW);
          delay(300);
        }
      // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS NOT APPLIED
      // The  else if block below is executed If the obstacle comes within braking distance and 
        //still the manual brake is not applied, then the EBS led lights up and EBS is applied
        else if (distance <= 90 && val_0 == 0 && val_speed <= 30)
        {
            digitalWrite(warning_led,LOW);
            digitalWrite(led, HIGH);
            servo.write(val_max);
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS APPLIED BUT NOT TO THE MAXIMUM
        else if (distance <= 90 && val_0 > 0 && val_speed <= 30)
        {
            digitalWrite(warning_led,LOW);
          //The for loop  below makes sure the servo rotates to its maximum value
            //In other words the brake is applied fully by EBS.
            for (int i = val_0; i <= val_max; i++)
            {
                servo.write(val_max); // servo to 179 degrees
            }
            // The following if block checks if the manual brake is applied to its maximum or not.
            //If yes, the Manual LED lights up.
            if (val_0 == 179)
            {
                digitalWrite(manual_led, HIGH);
                
            }
            //If no, then the else block below is executed , both Digital and Manual LED lights up.
            else
            {
                digitalWrite(led, HIGH);               
                digitalWrite(manual_led, HIGH);
               
            }

        }
        //If the obstacle is far away then the code stays in the following else condition.
        else
        {
            servo.write(val_0);
            digitalWrite(led, LOW);
            digitalWrite(warning_led,LOW);
            digitalWrite(manual_led,LOW);
        }
        break;

        // 25m = (1.30m)obstacle distance and speed of 45 Kmh

    case 31 ... 45:
      //The below if block operates the warning LED , if the obstacle is detected it blinks the
      //warning LED from a certain offset distance and prompts the driver to apply manual brake.
        if(distance<=143 && distance>130 && val_speed<=45)
        {
          digitalWrite(warning_led,HIGH);
          delay(300);
          digitalWrite(warning_led,LOW);
          delay(300);
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS NOT APPLIED
      // The  else if block below is executed If the obstacle comes within braking distance and 
        //still the manual brake is not applied, then the EBS led lights up and EBS is applied
        if (distance <= 130 && val_0 == 0 && val_speed <= 45)
        {
            digitalWrite(warning_led,LOW);
            digitalWrite(led, HIGH);
            servo.write(val_max);
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS APPLIED BUT NOT TO THE MAXIMUM
        else if (distance <= 130 && val_0 > 0 && val_speed <= 45)
        {   digitalWrite(warning_led, LOW); 
         //The for loop  below makes sure the servo rotates to its maximum value
            //In other words the brake is applied fully by EBS.
            for (int i = val_0; i <= val_max; i++)
            {
                servo.write(val_max); // servo to 179 degrees
            }
            // The following if block checks if the manual brake is applied to its maximum or not.
            //If yes, the Manual LED lights up.
            if (val_0 == 179)
            {
                digitalWrite(manual_led, HIGH);
              
            }
            //If no, then the else block below is executed , both Digital and Manual LED lights up.
            else
            {
                digitalWrite(led, HIGH);
                
                digitalWrite(manual_led, HIGH);
                
            }
 
        }
        //If the obstacle is far away then the code stays in the following else condition.
        else
        {
            servo.write(val_0);
            digitalWrite(led, LOW);
            digitalWrite(warning_led,LOW);
            digitalWrite(manual_led,LOW);
        }
        break;

    // 38m =(1.7m)obstacle distance and speed of 60 Kmh
    case 46 ... 60:
      //The below if block operates the warning LED , if the obstacle is detected it blinks the
      //warning LED from a certain offset distance and prompts the driver to apply manual brake.
      if(distance<=187 && distance>170 && val_speed<=60)
      {
          digitalWrite(warning_led,HIGH);
          delay(300);
          digitalWrite(warning_led,LOW);
          delay(300);
               
      }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS NOT APPLIED
      // The  else if block below is executed If the obstacle comes within braking distance and 
        //still the manual brake is not applied, then the EBS led lights up and EBS is applied
        if (distance <= 170 && val_0 == 0 && val_speed <= 60)
        {
            digitalWrite(warning_led,LOW);
            digitalWrite(led, HIGH);
            servo.write(val_max);
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS APPLIED BUT NOT TO THE MAXIMUM
        else if (distance <= 170 && val_0 > 0 && val_speed <= 60)
        {
            digitalWrite(warning_led,LOW);
          //The for loop  below makes sure the servo rotates to its maximum value
            //In other words the brake is applied fully by EBS.
            for (int i = val_0; i <= val_max; i++)
            {
                servo.write(val_max); // servo to 179 degrees
            }

            // The following if block checks if the manual brake is applied to its maximum or not.
            //If yes, the Manual LED lights up.
            if (val_0 == 179)
            {
                digitalWrite(manual_led, HIGH);                
            }
            //If no, then the else block below is executed , both Digital and Manual LED lights up.
            else
            {
                digitalWrite(led, HIGH);               
                digitalWrite(manual_led, HIGH);                
            }

        }
        //If the obstacle is far away then the code stays in the following else condition.
        else
        {
            servo.write(val_0);
            digitalWrite(led, LOW);
            digitalWrite(warning_led,LOW);
            digitalWrite(manual_led,LOW);        
        }
        break;

    // 54m = (2.1m)obstacle distance and speed of 75 Kmh
    case 61 ... 75:
      //The below if block operates the warning LED , if the obstacle is detected it blinks the
      //warning LED from a certain offset distance and prompts the driver to apply manual brake.
        if(distance<=231 && distance>210 && val_speed<=75)
        {
          digitalWrite(warning_led,HIGH);
          delay(300);
          digitalWrite(warning_led,LOW);
          delay(300);               
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS NOT APPLIED
      // The  else if block below is executed If the obstacle comes within braking distance and 
        //still the manual brake is not applied, then the EBS led lights up and EBS is applied
        else if (distance <= 210 && val_0 == 0 && val_speed <= 75)
        {
            digitalWrite(warning_led,LOW);
            digitalWrite(led, HIGH);
            servo.write(val_max);
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS APPLIED BUT NOT TO THE MAXIMUM
        else if (distance <= 210 && val_0 > 0 && val_speed <= 75)
        {
            digitalWrite(warning_led, LOW); 
          //The for loop  below makes sure the servo rotates to its maximum value
            //In other words the brake is applied fully by EBS.
            for (int i = val_0; i <= val_max; i++)
            {
                servo.write(val_max); // servo to 179 degrees
            }
            // The following if block checks if the manual brake is applied to its maximum or not.
            //If yes, the Manual LED lights up.
            if (val_0 == 179)
            {
                digitalWrite(manual_led, HIGH);
                
            }
            //If no, then the else block below is executed , both Digital and Manual LED lights up.
            else
            {
                digitalWrite(led, HIGH);                
                digitalWrite(manual_led, HIGH);                
            }
        }
        //If the obstacle is far away then the code stays in the following else condition.
        else
        {
            servo.write(val_0);
            digitalWrite(led, LOW);
            digitalWrite(manual_led, LOW);
            digitalWrite(warning_led, LOW);
        }
        break;

    // 72m  = (2.5m)obstacle distance and speed of 90 Kmh
    case 76 ... 90:
      //The below if block operates the warning LED , if the obstacle is detected it blinks the
      //warning LED from a certain offset distance and prompts the driver to apply manual brake.
        if(distance<=275 && distance>250 && val_speed<=90)
        {
          digitalWrite(warning_led,HIGH);
          delay(300);
          digitalWrite(warning_led,LOW);
          delay(300);               
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS NOT APPLIED
      // The  else if block below is executed If the obstacle comes within braking distance and 
        //still the manual brake is not applied, then the EBS led lights up and EBS is applied
        if (distance <= 250 && val_0 == 0 && val_speed <= 90)
        {
            digitalWrite(warning_led,LOW);
            digitalWrite(led, HIGH);
            servo.write(val_max);
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS APPLIED BUT NOT TO THE MAXIMUM
        else if (distance <= 250 && val_0 > 0 && val_speed <= 90)
        {
            digitalWrite(warning_led, LOW); 
          //The for loop  below makes sure the servo rotates to its maximum value
            //In other words the brake is applied fully by EBS.
            for (int i = val_0; i <= val_max; i++)
            {
                servo.write(val_max); // servo to 179 degrees
            }
            // The following if block checks if the manual brake is applied to its maximum or not.
            //If yes, the Manual LED lights up.
            if (val_0 == 179)
            {
                digitalWrite(manual_led, HIGH);
             }
             //If no, then the else block below is executed , both Digital and Manual LED lights up.
            else
            {
                digitalWrite(led, HIGH);
                digitalWrite(manual_led, HIGH);
              }

        }
        //If the obstacle is far away then the code stays in the following else condition.
        else
        {
            servo.write(val_0);
            digitalWrite(led, LOW);
            digitalWrite(warning_led,LOW);
            digitalWrite(manual_led,LOW);
        }
        break;

    // 86m = (3.0m)obstacle distance and speed of 100 Kmh
    case 91 ... 100:
      //The below if block operates the warning LED , if the obstacle is detected it blinks the
      //warning LED from a certain offset distance and prompts the driver to apply manual brake.
        if(distance<=325 && distance>300 && val_speed<=100)
        {
          digitalWrite(warning_led,HIGH);
          delay(300);
          digitalWrite(warning_led,LOW);
          delay(300);               
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS NOT APPLIED
      // The  else if block below is executed If the obstacle comes within braking distance and 
        //still the manual brake is not applied, then the EBS led lights up and EBS is applied
        else if (distance <= 300 && val_0 == 0 && val_speed <= 100)
        {
            digitalWrite(warning_led,LOW);
            digitalWrite(led, HIGH);
            servo.write(val_max);
        }
        // SIMULATING AUTOMATIC BRAKE SYSTEM IF THE BRAKE IS APPLIED BUT NOT TO THE MAXIMUM
        else if (distance <= 300 && val_0 > 0 && val_speed <= 100)
        {
            digitalWrite(warning_led,LOW);
          //The for loop  below makes sure the servo rotates to its maximum value
            //In other words the brake is applied fully by EBS.
            for (int i = val_0; i <= val_max; i++)
            {
                servo.write(val_max); // servo to 179 degrees
            }
            // The following if block checks if the manual brake is applied to its maximum or not.
            //If yes, the Manual LED lights up.
            if (val_0 == 179)
            {
                digitalWrite(manual_led, HIGH);
                
            }
            //If no, then the else block below is executed , both Digital and Manual LED lights up.
            else
            {
                digitalWrite(led, HIGH);
                
                digitalWrite(manual_led, HIGH);
                
            }

        }
        //If the obstacle is far away then the code stays in the following else condition.
        else
        {
            servo.write(val_0);
            digitalWrite(led, LOW);
            digitalWrite(warning_led,LOW);
            digitalWrite(manual_led,LOW);
        }
        break;
    //If the carspeed is zero the the it falls in the default case.
    default:
        servo.write(val_0);
        digitalWrite(warning_led,LOW);
        digitalWrite(manual_led,LOW);
        break;
    }
}
