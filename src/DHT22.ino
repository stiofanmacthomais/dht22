#include <PietteTech_DHT.h>
#include <time.h>

#define DHTTYPE  DHT22
#define DHTPIN   D4

PietteTech_DHT DHT(DHTPIN, DHTTYPE);

char *event = "HOME";
double temperature;
double humidity;
double dewpoint;

void setup()
{
  Particle.variable("temperature", &temperature, DOUBLE);
  Particle.variable("humidity", &humidity, DOUBLE);
  Particle.variable("dewpoint", &dewpoint, DOUBLE);
}

void loop()
{
  int result = DHT.acquireAndWait(2000);
  
  char message[100];
  time_t time = Time.now();
  Serial.println(Time.timeStr(time));
  
  temperature = DHT.getCelsius();
  humidity = DHT.getHumidity();
  dewpoint = DHT.getDewPoint();
 
  sprintf (message, "{\"temperature\": %.2f, \"humidity\": %.2f, \"dewpoint\": %.2f }", 
    temperature, 
    humidity, 
    dewpoint
  );
  
  Particle.publish (event, message);
  
  delay(60000);
}