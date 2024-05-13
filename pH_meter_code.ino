//After calibrating the PH-4502C, assemble all the components and upload this code.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
  
float calibration_value = 21.34; 
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

float ph_act; //for OLED display

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  //Welcome Screen
  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(20, 0);        // position to display
  oled.println("pH Meter");     // text to display
  oled.display();               // show on OLED
}

void loop() {
  for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6;
 float ph_act = -5.70 * volt + calibration_value; 

 oled.clearDisplay();
 oled.setTextSize(2);          // text size
 oled.setTextColor(WHITE);     // text color
 oled.setCursor(20, 0);        // position to display
 oled.println("pH Value");     // text to display
 oled.display();               // show on OLED
 
 oled.setTextSize(3);
 oled.setCursor(30,30); 
 oled.print(ph_act);
 oled.display();
}


 