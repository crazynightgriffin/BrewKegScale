# BrewKegScale
Beer keg weighing system to calculate how much is left in it, displaying the reading on an OLED screen and sending the data to a 3rd party website (initially BrewSpy).

This is the code for the project there is also a website which has full build instructions and a great facebook group to ask for help.

https://www.facebook.com/groups/2166040850218376

https://brewkegscale.wordpress.com



# Lines which need updating with your details.
V0.1
- line 16 float keg_tare_weight = 4107; //Aamend this figure with the weight of your keg empty in grams
- line 73 WiFiMulti.addAP("YOUR SSID", "YOUR WiFi PASSWORD");
- line 225 String jsondata = "{\"token\":\"YOUR API TOKEN\",\"unit\":\"pint\",\"kegVolume\":\"34\",\"beerLeft\":\"" + pints_left_string + "\"}";
   The token is the last part of the webhook eg the webhook is http://brew-spy.com/api/custom/123456789abcdefg you just need to copy in 123456789abcdefg
