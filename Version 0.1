#include <HX711.h>  // needed to communicate with the HX711
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include <math.h>  // needed for the floor command
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

HX711 scale;  // Initializes library functions.

float weight; // this is used to store the variable for the weight reading from the HX711
float pints_left; // this is used to store the variable for pints left
float keg_tare_weight = 4107; //Aamend this figure with the weight of your keg empty in grams
//dumpy corny keg 4470
//tall corny keg 4107
//2l coke bottle 44

boolean hasRun = false;

 const int LOADCELL_DOUT_PIN = 14;       //Remember these are ESP GPIO pins, these might not be the pins labeled on the board.
 const int LOADCELL_SCK_PIN = 12;        //using 14 and 12 for a NodeMCU  

 const int OLED_DOUT_PIN = D2;  //D2=SDK  As per labeling on NodeMCU
 const int OLED_SCK_PIN = D1;   //D1=SCK  As per labeling on NodeMCU

 String Line_1 = " ";
 String Line_2 = "TAP 1";
 String Line_3 = " ";

 int old_something = 0;

// Defines calibration factors we'll use for calibrating.
int calibration_factor = -21120; //This comes from using a known weight and following the instructions on the serial monitor
int offset_factor = 196104;  //this comes from the serial monitor and is the reading with
                             //nothing on the scales once the calibration factor has been updated
                             // aka zero factor

// Initialize the OLED display using Wire library
SSD1306Wire  display(0x3c, OLED_DOUT_PIN, OLED_SCK_PIN);

void setup()
{
  Serial.begin(74880);   // Starts serial communication in 9600 baud rate.
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
  WiFiMulti.addAP("YOUR SSID", "YOUR WiFi PASSWORD");


  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  
for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
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


  getweight();   //calls the getweight sub routine
  drawOnScreen(); //calls the drawOnScreen sub routine

//This section calls updatebrewspy but only if its the first time through the void loop
 Serial.print("hasRun: "); // Prints calibration factor.
  Serial.println(hasRun);

   if (hasRun == false)
  {
    hasRun = true;
    updatebrewspy(); //UPDATES BREWSPY
  }




//This section calls updatebrewspy but only if there is a change 
 int something = floor(pints_left);
 if (something != old_something)
   updatebrewspy(); //UPDATES BREWSPY
 old_something = something;

 
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
// clear the display
    display.clear();

// WRITE TEXT
//writes 1st row of text
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 1, String(Line_1));
    
//writes 2nd row of text
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 15, String(Line_2));

//writes 3rd row of text
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 32, String(Line_3));

// DRAW BOXES
    display.drawRect(0, 0, 128, 64);
    display.drawRect(0, 46, 128, 64);

// WRITE PINTS LEFT 4th row
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(20, 46, String(pints_left, 0));
    
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(110, 46, "Pints left"); 

// write the buffer to the display
    display.display();
}
// end of DRAWONSCREEN

void updatebrewspy()
{
Serial.print("updating brewspy");

HTTPClient http;
String url="http://brew-spy.com/api/tap/keg/set";
String pints_left_string = "";     // empty string
pints_left_string.concat(pints_left); // joins pints left with the pints_left_string so that it is a string to send to brewspy
String jsondata = "{\"token\":\"YOUR API TOKEN\",\"unit\":\"pint\",\"kegVolume\":\"34\",\"beerLeft\":\"" + pints_left_string + "\"}";

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
