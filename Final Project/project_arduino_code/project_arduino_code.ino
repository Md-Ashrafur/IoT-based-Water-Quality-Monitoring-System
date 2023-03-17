/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
const int sensor=A0; // Assigning analog pin A1 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
byte degree_symbol[8] = 
              {
                0b00111,
                0b00101,
                0b00111,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };
void setup()
{
  //pinMode(kPinTemp, INPUT);
  pinMode(sensor,INPUT); // Configuring pin A1 as input
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.createChar(1, degree_symbol);
  lcd.setCursor(0,0);
  lcd.print(" IoT Based Water ");
  lcd.setCursor(0,1);
  lcd.print("Quality Monitoring System");
 delay(1000);
  lcd.clear();

//Displaying Name
 lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Md. Ashrafur Rahman ");
  lcd.setCursor(0,1);
  lcd.print("2017-1-60-125");
  delay(1500);
  lcd.clear();

  
//Displaying Name
 lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Md. Sabbir Hossain ");
  lcd.setCursor(0,1);
  lcd.print("2017-1-60-112");
  delay(1500);
  lcd.clear();

  //Displaying Name
 lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Aminul Islam ");
  lcd.setCursor(0,1);
  lcd.print("2017-1-60-111");
  delay(1500);
  lcd.clear();

}
void loop()
{

vout=analogRead(sensor);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius
tempf=(vout*1.8)+32; // Converting to Fahrenheit 
Serial.print("in DegreeC=");
Serial.print("\t");
Serial.print(tempc);
Serial.println();
Serial.print("in Fahrenheit=");
Serial.print("\t");
Serial.print(tempf);
Serial.println();


lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temperature in C");
lcd.setCursor(4,1);
lcd.print(tempc);
lcd.write(1);
lcd.print("C");
delay(1000);
 
  
}
