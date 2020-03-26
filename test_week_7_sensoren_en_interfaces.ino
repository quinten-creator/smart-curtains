// oled scherm

#include <Wire.h>
#include <Adafruit_SSD1306.h> 
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Blynk server

#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

char auth[] = "DCsDZhcKEmqpL-VFZe-CHjf2crsvhZ1T";
char ssid[] = "qh";
char pass[] = "12345678";

//BLYNK_WRITE(V3)
#define lichtsensor A0

int gordijnopen = 2;
int gordijndicht = 3;

int lichtwaarde = 0;
void setup() {

  Serial.begin(9600);
  
  pinMode(gordijnopen, OUTPUT);
  pinMode(gordijndicht, OUTPUT);
  
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  

  Blynk.begin(auth, ssid, pass,"server.wyns.it",8081);

  IPAddress(192,168,1,100), (8080);
    
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x60)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
    }
  Serial.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:
      Blynk.run();
  
  lichtwaarde = analogRead(lichtsensor);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(lichtwaarde);
  Blynk.virtualWrite(V1, lichtwaarde);

  delay(1000);
  if(lichtwaarde <= 1000)
  {
    digitalWrite(gordijndicht,HIGH);
    digitalWrite(gordijnopen,LOW);
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("gordijn dicht");
    delay(7000);
    while(lichtwaarde <= 1000)
    {
      lichtwaarde = analogRead(lichtsensor);
      digitalWrite(gordijndicht,LOW);
      digitalWrite(gordijnopen,LOW);
    }
  
  }
  else
  {
    if(lichtwaarde >= 1005)
    {
      digitalWrite(gordijndicht,LOW);
      digitalWrite(gordijnopen,HIGH);
      
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.print("gordijn open");
      delay(7000);
      while(lichtwaarde >= 1005)
      {
        lichtwaarde = analogRead(lichtsensor);
        digitalWrite(gordijndicht,LOW);
        digitalWrite(gordijnopen,LOW);
        }
      }
    }
    display.display();
  }
