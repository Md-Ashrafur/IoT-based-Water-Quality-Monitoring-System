// Include Libraries
#include "Arduino.h"
#include "DS18B20.h"


// Pin Definitions
#define DS18B20WP_PIN_DQ  4
#define GPS_PIN_TX  11
#define GPS_PIN_RX  10
#define SIM800L_SOFTWARESERIAL_PIN_TX 2
#define SIM800L_SOFTWARESERIAL_PIN_RX 3



// Global variables and defines

// object initialization
DS18B20 ds18b20wp(DS18B20WP_PIN_DQ);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // DS18B20 1-Wire Temperature Sensor - Waterproof - Test Code
    // Read DS18B20 temp sensor value in degrees celsius. for degrees fahrenheit use ds18b20wp.ReadTempF()
    float ds18b20wpTempC = ds18b20wp.readTempC();
    Serial.print(F("Temp: ")); Serial.print(ds18b20wpTempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '2')
    {
    // Disclaimer: The Ublox NEO-6M GPS Module is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '3')
    {
    // Disclaimer: The QuadBand GPRS-GSM SIM800L is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DS18B20 1-Wire Temperature Sensor - Waterproof"));
    Serial.println(F("(2) Ublox NEO-6M GPS Module"));
    Serial.println(F("(3) QuadBand GPRS-GSM SIM800L"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing DS18B20 1-Wire Temperature Sensor - Waterproof"));
        else if(c == '2') 
          Serial.println(F("Now Testing Ublox NEO-6M GPS Module - note that this component doesn't have a test code"));
        else if(c == '3') 
          Serial.println(F("Now Testing QuadBand GPRS-GSM SIM800L - note that this component doesn't have a test code"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
