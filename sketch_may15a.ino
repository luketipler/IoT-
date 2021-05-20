
#define BLYNK_PRINT Serial
  
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


char auth[] = "dSzIqIlLyhj842oiZejr9YKlrJVhsmhx";
char ssid[] = "VM2498811";
char pass[] = "y6fCkYpncdpy";

  
DHT dht(D2, DHT11);
BlynkTimer timer;


void sensor()
{
  // init for temp/humidity variables
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  

  // try except format, will return this value if DHT is not sending values
  if (isnan(humidity) || isnan(temp)) {Serial.println("No DHT values, try again!");
    return;
  }
  
  Blynk.virtualWrite(V5, temp); // temperature value
  Blynk.virtualWrite(V6, humidity); // humidity value
}


void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(D0,OUTPUT);
 
  Blynk.begin(auth, ssid, pass);
 
  dht.begin();
 
  timer.setInterval(1000L, sensor);
}

void led_pwm(int pwm_value);

// timer writer and override, eadch timer is assigned to V0
// these timers and manual switch allow for lighting schedules
BLYNK_WRITE(V0)
{
  led_pwm(param.asInt());
}


void loop()
{
  // run the system
  Blynk.run();
  timer.run();
}

// pwm value allows the Blynk sending to customise the amount 
// that the LED recieves.
void led_pwm(int pwm_value)
{
  analogWrite(D0, pwm_value);
}
