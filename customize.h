// all customization takes place in this file thanks to Richard McCausland!!!

//Amend the wifiName and WifiPass with your own WiFi details.
const char* wifiName = "YOUR WIFI SSID";
const char* wifiPass = "YOUR SSID PASSWORD";

//Amend this token with your own brewspy token
String brewspytoken = "YOUR TOKEN";
String brewspyurl = "http://brew-spy.com/api/json/taplist/";
//Web Server address to read from 
const char* host = "http://brew-spy.com/api/json/taplist/SORRY YOUR TOKEN AGAIN";


//Aamend this figure with the weight of your keg empty in grams
float keg_tare_weight = 4107;
//dumpy corny keg 4470
//tall corny keg 4107
//2l coke bottle 44

// Defines calibration factors we'll use for calibrating.
int calibration_factor = -21120; //This comes from using a known weight and following the instructions on the serial monitor
int offset_factor = 196104;  //this comes from the serial monitor and is the reading with
                             //nothing on the scales once the calibration factor has been updated
                             // aka zero factor


//  ***  if you have followed the build documentation you should not need to amend anything below this line  ***
//Board Pins for the HX711 
const int LOADCELL_DOUT_PIN = 14;       //Remember these are ESP GPIO pins, these might not be the pins labeled on the board.
const int LOADCELL_SCK_PIN = 12;        //using 14 and 12 for a NodeMCU  
//Board Pins for the OLED display 
const int OLED_DOUT_PIN = D2;  //D2=SDK  As per labeling on NodeMCU
const int OLED_SCK_PIN = D1;   //D1=SCK  As per labeling on NodeMCU


                   
