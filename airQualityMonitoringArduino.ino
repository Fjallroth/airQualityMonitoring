#include <MICS-VZ-89TE.h>
#include <DHT.h>
#include <Wire.h>

// DHT Setup
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float humidity;
float temperature;

int period = 797;
unsigned long time_now = 0;

int MICS_voc;
int MICS_eqco2;

#include <SoftwareSerial.h>
SoftwareSerial pmsSerial(2, 3);

void setup() {
  Serial.begin(9600);
  pmsSerial.begin(9600);
  dht.begin();
}

struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};

pms5003data data;

void loop() {
  if (millis() - time_now > period) {
    time_now = millis();

    // DHT loop
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    Serial.print("Humidity:, ");
    Serial.print(humidity);
    Serial.print(", %, Temp:, ");
    Serial.print(temperature);
    Serial.print(", Celsius,");

    // VOC sensor loop
    MICS_VZ_89TE myMICS;
    myMICS.begin();
    myMICS.readSensor();
    MICS_eqco2 = myMICS.getCO2();
    MICS_voc = myMICS.getVOC();
    Serial.print("MICS VOC PPB:, ");
    Serial.print(MICS_voc);
    Serial.print(" ,MICS CO2 PPM:, ");
    Serial.print(MICS_eqco2);
    Serial.println(",");
  }

  if (readPMSdata(&pmsSerial)) {
    Serial.print(",PM 1.0:, ");
    Serial.print(data.pm10_standard);
    Serial.print("\t\t,PM 2.5:, ");
    Serial.print(data.pm25_standard);
    Serial.print("\t\t,PM 10:, ");
    Serial.print(data.pm100_standard);
    Serial.print(",");
  }
}

boolean readPMSdata(Stream *s) {
  if (!s->available()) {
    return false;
  }

  if (s->peek() != 0x42) {
    s->read();
    return false;
  }

  if (s->available() < 32) {
    return false;
  }

  uint8_t buffer[32];
  uint16_t sum = 0;
  s->readBytes(buffer, 32);

  for (uint8_t i = 0; i < 30; i++) {
    sum += buffer[i];
  }

  uint16_t buffer_u16[15];
  for (uint8_t i = 0; i < 15; i++) {
    buffer_u16[i] = buffer[2 + i * 2 + 1];
    buffer_u16[i] += (buffer[2 + i * 2] << 8);
  }

  memcpy((void *)&data, (void *)buffer_u16, 30);

  if (sum != data.checksum) {
        Serial.println("Checksum failure");
        return false;
      }
      // success!
      return true;
    
    }