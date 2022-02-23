// *  BREWKEGSCALE  V0.2  *

#include <HX711.h>  // needed to communicate with the HX711
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include <math.h>  // needed for the floor command
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "customize.h"

ESP8266WiFiMulti WiFiMulti;




HX711 scale;  // Initializes library functions.

float weight; // this is used to store the variable for the weight reading from the HX711
float pints_left; // this is used to store the variable for pints left

boolean hasRun = false;

 String Line_1 = "Line_1";
 String Line_2 = "Line_2";
 String Line_3 = "Line_3";
 String Line_3b = "Line_3b";
 String Line_4 = "Line_4";

 
 int old_something = 0;
 
// Initialize the OLED display using Wire library
SSD1306Wire  display(0x3c, OLED_DOUT_PIN, OLED_SCK_PIN);

void setup()
{
  Serial.begin(74880);   // Starts serial communication in 9600 baud rate.
   
  Serial.print(F("Sketch: ")); Serial.println(__FILE__);
Serial.print(F("Uploaded: ")); Serial.println(__DATE__);
  
  
  Serial.println("Initializing scale calibration.");  // Prints user commands.
  Serial.println("Please remove all weight from scale.");
  Serial.println("Place known weights on scale one by one.");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);   // Initializes the scaling process.
  
  scale.set_scale();
  //scale.tare();          // this line is removed as we will hard code the zero reading using the offset factor line below.
  scale.set_offset(offset_factor);  // set the zero

//setup screen
  Serial.println("Initializing OLED Display");
  display.init();
  //display.flipScreenVertically();  // use this to flip the display if needed.
  display.setFont(ArialMT_Plain_16);
  display.clear();
  display.drawString(10, 30, "Loading");  //displays Loading on the oled screen while it boots.
    delay(2000);
      display.display();

//join wifi
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(wifiName, wifiPass);


  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP

  display.init();
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
  display.drawString(64, 1, "BrewKegScale");
  display.drawString(64, 15, "Version 0.2");
  display.drawString(64, 32, WiFi.localIP().toString());
  display.display();
  delay(5000);
}
void loop()
{
  scale.set_scale(calibration_factor);  // Adjusts the calibration factor.
  scale.wait_ready();
  long zero_factor = scale.read_average(5); //Get a baseline reading
  
  Serial.print("Zero factor:        "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  
  Serial.print("Reading:            ");            // Prints weight readings in .3 decimal kg units.
  Serial.print(scale.get_units(5) * 1000, 0);
  Serial.println(" grams");
  
  Serial.print("Calibration factor: "); // Prints calibration factor.
  Serial.println(calibration_factor);
  
//This section calls updatebrewspy but only if its the first time through the void loop
 Serial.print("hasRun: "); // Prints calibration factor.
  Serial.println(hasRun);

   if (hasRun == false)
  {
    hasRun = true;
    updatebrewspy(); //UPDATES BrewSpy
    getbrewspyinfo();  //get info from BrewSpy
  }

//This section calls updatebrewspy but only if there is a change 
 int something = floor(pints_left);
   if (something != old_something)
   {
    updatebrewspy(); //UPDATES BREWSPY
    getbrewspyinfo();  //get info from BrewSpy
    old_something = something;
   }

  getweight();   //calls the getweight sub routine
  drawOnScreen(); //calls the drawOnScreen sub routine

 
  //scale.power_down();    //not needed?     // Puts the scale to sleep mode for 2 seconds.
  delay(2000);
  //scale.power_up();     //not needed?       // Wakes the scale up
 
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 100;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 100;  
  }
}

// end of VOID LOOP

void getweight() {  // read scale units covert to grams then calculate pints left
  weight = scale.get_units(5) * 1000, 0; //get weight in kg over 5 readings and convert to grams

//this prevents minus numbers for the weight 
//if (weight < 0)
//  {
//     weight = 0.00;
//   }
//convert weight to pints left
   pints_left = (weight - keg_tare_weight) / 568;  //takes the current weight minuses the keg tare weght and devides that by 568 which is the weight of a pint of pwater
Serial.print("Pints Left:          ");  //prints to serial monitor
Serial.println(pints_left);             //prints to serial monitor
   
   pints_left = floor(pints_left);      //rounds the pints left down to nearest whole number even 4.8 would round down to 4

Serial.print("Pints Left rounded: ");   //prints to serial monitor
Serial.println(pints_left);             //prints to serial monitor

//this section does not allow the pints left to be less than 0 just to keep the interface clean in the event of zeron drifting.
     if (pints_left < 0)
  {
     pints_left = 0.00;
   }
   
}
//end of GETWEIGHT

void drawOnScreen() {   //sets the OLED screen and writes data to it.
//clear screen
   display.clear();
// WRITE TEXT
//writes 1st row of text
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 1, String(Line_1));
//writes 2nd row of text
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 20, String(Line_2));
//writes 3rd row of text
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 32, String(Line_3));
// WRITE PINTS LEFT 4th row
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(20, 46, String(pints_left, 0));
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(110, 46, "Pints left"); 
// DRAWS BOXES
    display.drawRect(0, 0, 128, 64);
    display.drawRect(0, 46, 128, 64);
//draws screen    
    display.display();

if (Line_3b.length() > 0)
  {
      delay(2000);
   //clear screen to dra
   display.clear();
// WRITE TEXT
//writes 1st row of text
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 1, String(Line_1));
//writes 2nd row of text
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 20, String(Line_2));
//writes 3rd row of text
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 32, String(Line_3b));
// WRITE PINTS LEFT 4th row
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(20, 46, String(pints_left, 0));
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(110, 46, "Pints left"); 
// DRAWS BOXES
    display.drawRect(0, 0, 128, 64);
    display.drawRect(0, 46, 128, 64);
//draws screen    
    display.display();

   }
}

// end of DRAWONSCREEN

void updatebrewspy()
{
Serial.println("updating brewspy");

HTTPClient http;
String url="http://brew-spy.com/api/tap/keg/set";
String pints_left_string = "";     // empty string
pints_left_string.concat(pints_left); // joins pints left with the pints_left_string so that it is a string to send to brewspy
String jsondata = "{\"token\":\"" + brewspytoken + "\",\"unit\":\"pint\",\"kegVolume\":\"34\",\"beerLeft\":\"" + pints_left_string + "\"}";

http.begin(url);
http.addHeader("Content-Type", "Content-Type: application/json");
int httpResponseCode = http.POST(jsondata); //Send the actual POST request
if(httpResponseCode>0){

String response = http.getString(); //Get the response to the request
Serial.println(httpResponseCode); //Print return code
Serial.println(response); //Print request answer
} else {
Serial.print("Error on sending POST: ");
Serial.println(httpResponseCode);
http.end();
}
}

void getbrewspyinfo()   {
  
  HTTPClient http;    //Declare object of class HTTPClient
  Serial.println("Getting info from BrewSpy");
  Serial.print("Request Link:");

  http.begin(host);     //Specify request destination
  //http.begin(brewspyurl.c_str(), brewspytoken.c_str()); 

  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload from server

  Serial.print("Response Code:"); //200 is OK
  Serial.println(httpCode);   //Print HTTP return code

  Serial.print("Returned data from Server:");
  Serial.println(payload);    //Print request response payload
  
  if(httpCode == 200)
  {
    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    DynamicJsonBuffer jsonBuffer(capacity);
  
   // Parse JSON object
    JsonObject& root = jsonBuffer.parseObject(payload);
    if (!root.success()) {
      Serial.println(F("Parsing failed!"));
      return;
    }
     
  Line_2 = root["recipe"].as<char*>();
  Line_3 = root["abv"].as<char*>();
  Line_1 = "Tap ";
  Line_3 += "% ABV";
  Line_1 += root["tap"].as<char*>();
  Line_3b = root["style"].as<char*>();
  }
  else
  {
    Serial.println("Error in response");
  }
  http.end();  //Close connection
}  
