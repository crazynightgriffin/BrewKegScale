# BrewKegScale
Beer keg weighing system to calculate how much is left in it, displaying the reading on an OLED screen and sending the data to a 3rd party website (initially BrewSpy).

This is the code for the project there is also a website which has full build instructions and a great facebook group to ask for help.

https://www.facebook.com/groups/2166040850218376
https://brewkegscale.wordpress.com



# Lines which need updating with our details.
V0.1

line 73  WiFiMulti.addAP("YOUR SSID", "YOUR WiFi PASSWORD");

line 225 String jsondata = "{\"token\":\"YOUR API TOKEN\",\"unit\":\"pint\",\"kegVolume\":\"34\",\"beerLeft\":\"" + pints_left_string + "\"}";
