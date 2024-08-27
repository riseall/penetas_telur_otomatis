#define BLYNK_PRINT Serial    
#include <SPI.h>
#include <ESP8266WiFi.h>                                  //pustaka Esp wifi
#include <BlynkSimpleEsp8266.h>                           //Memasukan library Blynk Esp
#include <DHT.h>                                          //Memasukan library sensor DHT
#include <Servo.h>                                        //Memasukan library Servo

#define relayPin 5                                        //digital pin 1 (lampu)
#define relayPin1 4                                       //digital pin 2 (kipas)
#define DHTPIN 2                                          // Digital pin 4 (pembacaan sensor) 
#define DHTTYPE DHT11                                     // DHT 11 (sensor yang akan diakses)

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
Servo servo;

char auth[] = "dXCQRHGrTmsIFkkpgpb4u1EveeNsYzOC";         //Kunci autentikasi projek blink yang dikirim ke email
char ssid[] = "POCO X3 NFC";                              //Identitas Wifi
char pass[] = "dafaalenzaaa";                             //Sandi Wifi

void setup(){
  pinMode(relayPin, OUTPUT);
  pinMode(relayPin1, OUTPUT);
  Serial.begin(115200);                                   //Komunikasi Serial
  Blynk.begin(auth, ssid, pass);                          //Sambungkan Koneksi Wifi
  dht.begin();                                            //prosedur memulai pemanggilan library dht11
  servo.attach(15);                                       //NodeMCU d8 pin (Servo)
  
  // Setup a function to be called every second
  timer.setInterval(2000, sendSensor);
}

void sendSensor()
{
  float h1 = dht.readHumidity();                          //pembacaan kelembapan
  float t1 = dht.readTemperature();                       //pembacaan suhu

  Blynk.virtualWrite(V5, h1);                             //V5 is for Humidity
  Blynk.virtualWrite(V6, t1);                             //V6 is for Temperature
}

void loop(){
  float kelembapan = dht.readHumidity();                  //pembacaan kelembaban
  float suhu = dht.readTemperature();                     //pembacaan suhu
  
  if (kelembapan < 65){                                   //Jika kelembapan kurang dari 65      
    digitalWrite(relayPin1, LOW);                         //relay mati
    }
  else if (suhu > 37){                                    //Jika suhu lebih dari 37
    digitalWrite(relayPin, HIGH);                         //relay hidup
  }
  else 
  { 
    digitalWrite(relayPin, LOW);                          //relay hidup
    digitalWrite(relayPin1, HIGH);                        //relay mati
  }
    
  Blynk.run();
  timer.run();
}
  BLYNK_WRITE(V2)
{
  servo.write(90);
  delay(5000);
  servo.write(0);
  delay(5000);
}
