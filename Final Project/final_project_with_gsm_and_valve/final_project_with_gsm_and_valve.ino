
// include the library code:

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <GSM.h>


#define GSMrx "8"
#define GSMtx "9"
// APN data
#define GPRS_APN       "GPRS_APN" // replace your GPRS APN
#define GPRS_LOGIN     "login"    // replace with your GPRS login
#define GPRS_PASSWORD  "password" // replace with your GPRS password
// initialize the library instance
GSMClient client;
GPRS gprs;
GSM gsmAccess;

// URL, path & port (for example: arduino.cc)
char server[] = "weather.google.com";
char path[] = "/asciilogo.txt";
int port = 80; // port 80 is the default for HTTP


//GPS
float lat , lon ; // create variable for latitude and longitude object
SoftwareSerial gpsSerial(3, 4); //rx,tx
TinyGPS gps;
const int sensor = A0; // Assigning analog pin A1 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit
float vout;
float gpspin = 0;


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int sValve = 10;
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
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Starting Arduino web client.");
  // connection state
  boolean notConnected = true;


  while (notConnected) {
    if ((gsmAccess.begin(GSMrx) == GSM_READY) &
        (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY)) {
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, port)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.print("GET ");
    client.print(path);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }




  //pinMode(kPinTemp, INPUT);
  pinMode(sensor, INPUT); // Configuring pin A1 as input
  pinMode(gpspin, INPUT);
  pinMode(sValve, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(1, degree_symbol);
  lcd.setCursor(0, 0);
  lcd.print(" IoT Based Water ");
  lcd.setCursor(0, 1);
  lcd.print("Quality Monitoring System");
  delay(1000);
  lcd.clear();

  //Displaying Name
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Md. Ashrafur Rahman ");
  lcd.setCursor(0, 1);
  lcd.print("2017-1-60-125");
  delay(1500);
  lcd.clear();


  //Displaying Name
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Md. Sabbir Hossain ");
  lcd.setCursor(0, 1);
  lcd.print("2017-1-60-112");
  delay(1500);
  lcd.clear();

  //Displaying Name
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Aminul Islam ");
  lcd.setCursor(0, 1);
  lcd.print("2017-1-60-111");
  delay(1500);
  lcd.clear();

  Serial.println("The GPS Received Signal:");
  gpsSerial.begin(9600); // connect gps sensor
  lcd.begin(16, 2);

}
void loop()
{
  vout = analogRead(sensor);
  vout = (vout * 500) / 1023;
  tempc = vout; // Storing value in Degree Celsius

  if (tempc > 50 || tempc < 5 ) // Also TDSvalue > 40 || pHvalue > 9 || pHvalue <5
  {
    digitalWrite(sValve, HIGH);   // stop water flow  --
    display();
  }
  else
  {
    digitalWrite(sValve, LOW); // Continue water flow
    display();
  }
}

void display(void)
{
  vout = analogRead(sensor);
  vout = (vout * 500) / 1023;
  tempc = vout; // Storing value in Degree Celsius

  Serial.print("in DegreeC=");
  Serial.print("\t");
  Serial.print(tempc);
  Serial.println();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature in C");
  lcd.setCursor(4, 1);
  lcd.print(tempc);
  lcd.write(1);
  lcd.print("C");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TDS Count: ");
  lcd.setCursor(4, 1);
  lcd.print("Sensor error");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH value: ");
  lcd.setCursor(4, 1);
  lcd.print("Sensor error");
  delay(1000);

  // check for gps data
  lcd.clear();
  gps.encode(gpsSerial.read());// encode gps data

  gps.f_get_position(&lat, &lon); // get latitude and longitude
  // display position
  /* lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("GPS Signal");

    lcd.setCursor(1,0);
    lcd.print("LAT:");
    lcd.setCursor(5,0);
    lcd.print(lat);
    Serial.print(lat);
    Serial.print(" ");
    Serial.print(lon);
    Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print(",LON:");
    lcd.setCursor(5,1);
    lcd.print(lon);



    lat = analogRead(gpspin);
    String latitude = String(lat,6);
    String longitude = String(lon,6);
    Serial.println(latitude+";"+longitude);
    delay(1000);
  */



  // listen for incoming clients
  GSMClient client = server.available();



  if (client) {
    while (client.connected()) {
      if (client.available()) {
        Serial.println("Receiving request!");
        bool sendResponse = false;
        while (char c = client.read()) {
          if (c == '\n') {
            sendResponse = true;
          }
        }

        // if you've gotten to the end of the line (received a newline
        // character)
        if (sendResponse) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(analogRead(analogChannel));
            client.println("<br />");
          }
          client.println("</html>");
          //necessary delay
          delay(1000);
          client.stop();
        }
      }
    }
  }

}
