#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3C

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

const int pinLM35 = A0;

void setup() {

  Serial.begin(9600);

 
  Wire.begin();

  delay(250);

 
  if (!display.begin(i2c_Address, true)) {
    Serial.println("ERROR: OLED no encontrada");

    while (1);
  }

  Serial.println("OLED funcionando correctamente");

 
  display.clearDisplay();

 
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(2);
  display.setCursor(15, 10);
  display.println("HOLA!");

 
  display.setTextSize(1);
  display.setCursor(20, 25);
  display.println("INICIANDO TERMOMETRO...");

 
  display.display();
  delay(1500);
}

void loop() {
  int lecturaADC = analogRead(pinLM35);
  float temperaturaC = (lecturaADC * (5.0 / 1023.0) * 100.0);

  Serial.print("Valor ADC: ");
  Serial.print(lecturaADC);
  Serial.print(" -> Temp: ");
  Serial.print(temperaturaC, 2);
  Serial.println(" *C");

  display.clearDisplay();

  display.setTextColor(SH110X_BLACK, SH110X_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("   SENSOR TEMPERATURA   ");

  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 18);
  display.println("Temp. Actual:");

  display.setTextSize(2);
  display.setCursor(25, 34);
  display.print(temperaturaC, 1);

  display.setTextSize(1);
  display.setCursor(85, 34);
  display.print((char)247);
  display.setTextSize(2);
  display.setCursor(95, 34);
  display.print("C");

  display.setTextSize(1);
  display.setCursor(15, 54);
  display.println("Status: OK");

  display.display();
  delay(1000);
}