/* To calibrate the pH sensor, you have to connect the PH-4502C to Aruduino Uno, then upload this code. 
After uploading the code, use one of the copper wire terminals wrapped around the BNC connector and 
another terminal connected to the BNC connector. On the serial monitor, you will see the reading voltage. 
If the voltage is now 2.5V, using a screwdriver, adjust the potentiometer near the BNC connector.
The calibration must be done before assembling the other components.
*/

#define OFFSET 

int pH_Value;
float Voltage;

void setup() 
{
  Serial.begin(9600);
  pinMode(pH_Value, INPUT);
}

void loop() 
{
  pH_Value = analogRead (A0);
  Voltage = pH_Value * (5.0/1023.0);
  Serial.println(Voltage);
  delay(500);
}
