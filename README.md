# BrewKegScale
Beer keg weighing system to calculate how much is left in it, displaying the reading on an OLED screen and sending the data to a 3rd party website (initially BrewSpy).

# Lines which need updating with our details.
# V0.1
line 73  WiFiMulti.addAP("YOUR SSID", "YOUR WiFi PASSWORD");
line 225 String jsondata = "{\"token\":\"YOUR API TOKEN\",\"unit\":\"pint\",\"kegVolume\":\"34\",\"beerLeft\":\"" + pints_left_string + "\"}";
