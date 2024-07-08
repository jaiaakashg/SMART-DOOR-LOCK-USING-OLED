#include <Wire.h>             
#include <Adafruit_GFX.h>     
#include <Adafruit_SSD1306.h>  
#include <NewPing.h>           
#include <WiFi.h>             
#define OLED_RESET    -1        
#define SCREEN_WIDTH  128       
#define SCREEN_HEIGHT 64        
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIGGER_PIN   17        
#define ECHO_PIN      16        
#define MAX_DISTANCE  200       
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#define RELAY_PIN     23       
#define DOOR_LOCK_TIME 2000     

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Smart Door Lock");
  display.display();
  delay(2000);  
  display.clearDisplay();
}

void loop() {
  unsigned int distance = sonar.ping_cm();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Distance: ");
  display.print(distance);
  display.println(" cm");
  display.display();

  
  if (distance < 50) {
    unlockDoor();  
  }

  delay(500);  
}

void unlockDoor() {
  digitalWrite(RELAY_PIN, HIGH);   
  delay(DOOR_LOCK_TIME);           
  digitalWrite(RELAY_PIN, LOW);    
}

