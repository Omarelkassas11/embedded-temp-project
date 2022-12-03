#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <dht11.h>
#include "DIO_int.h"
#include "LCD.h"
#include "ADC.h"
dht11 DHT;
#define tempSensor A0

const int ok = A3;
const int UP = A1;
const int DOWN = A2;

const int LeD = 8;             



int ack = 0;
int pos = 0;
int sec = 0;
int Min = 0;
int hrs = 0;
int T_threshold = 30;
int H_threshold = 60;

int SET = 0;
boolean T_condition = true;
boolean H_condition = true;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int main(void) {

  // Buttons
  DIO_SetPinDirection(DDRB,ok, INPUT);
  DIO_SetPinDirection(DDRB,UP, INPUT);
  DIO_SetPinDirection(DDRB,DOWN, INPUT);

  // Relay
  DIO_SetPinDirection(DDRB,LeD, OUTPUT);
  

 DIO_SetPinValue(PORTB,LeD, LOW);
  
 DIO_SetPinValue(PORTB,ok, HIGH);
 DIO_SetPinValue(PORTB,UP, HIGH);
 DIO_SetPinValue(PORTB,DOWN, HIGH);

  LCD_init();
  lcd.backlight();

  Serial.begin(9600);

  LCD_Clear();
  lcd.setCursor(0, 0);
  LCD_String ("Temperature &");
  lcd.setCursor(0, 1);
  LCD_String ("Humidity ");

  delay (3000);

  LCD_Clear();
  lcd.setCursor(0, 0);
  LCD_String ("Controller For");
  lcd.setCursor(0, 1);
  LCD_String ("Incubator");

  delay (3000);

  LCD_Clear();
  Serial.println("Temperature and Humidity Controller");


while(1) {
  // Get the voltage reading from the LM35
  int reading = ADC_Read(tempSensor);
  // Convert that reading into voltage
  float voltage = reading * (5.0 / 1024.0);
  // Convert the voltage into the temperature in Celsius
  int temperature= voltage * 100;
  
  if (SET == 0) {

    LCD_Clear();
    lcd.setCursor(0, 0);
    LCD_String ("Set Temperature:");
    lcd.setCursor(0, 1);
    LCD_String (T_threshold);
    LCD_String (" *C");

    while (T_condition) {

      if (DIO_GetPinValue(PINB,UP) == LOW) {
        T_threshold = T_threshold + 1;
        lcd.setCursor(0, 1);
        LCD_String (T_threshold);
        LCD_String (" *C");
        delay(200);

      }
      if (DIO_GetPinValue(PINB,DOWN) == LOW) {
        T_threshold = T_threshold - 1;

        lcd.setCursor(0, 1);
        LCD_String (T_threshold);
        LCD_String (" *C");

        delay(200);

      }

      if (DIO_GetPinValue(PINB,ok) == LOW) {
        delay(200);
        T_condition = false;
      }
    }

    lcd.backlight();
    LCD_Clear();
    lcd.setCursor(0, 0);
    LCD_String ("Set Humidity:");
    lcd.setCursor(0, 1);
    LCD_String (H_threshold);
    LCD_String ("%");

    delay(100);

    while (H_condition) {
      if (DIO_GetPinValue(PINB,UP) == LOW) {
        H_threshold = H_threshold + 1;

        lcd.setCursor(0, 1);
        LCD_String (H_threshold);
        LCD_String ("%");

        delay(100);

      }

      if (DIO_GetPinValue(PINB,DOWN) == LOW) {

        H_threshold = H_threshold - 1;

        lcd.setCursor(0, 1);
        LCD_String (H_threshold);
        LCD_String ("%");

        delay(200);
      }

      if (DIO_GetPinValue(PINB,ok) == LOW) {
        delay(100);
        H_condition = false;
      }
    }

    SET = 1;
  }
  ack = 0;
  int chk;
  chk = ADC_Read(tempSensor);    // READ DATA
  switch (chk)
  {

    case DHTLIB_OK:

      //Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:

      //Serial.print("Checksum error,\t");
      ack = 0;
      break;
    case DHTLIB_ERROR_TIMEOUT:

      //Serial.print("Time out error,\t");
      ack = 0;
      break;
    default:
      //Serial.print("Unknown error,\t");
      break;
  }

  // DISPLAT DATA

  Serial.print("Tempreature, \t");
  Serial.print(temperature, 1);
  

  delay(100);

  if (ack == 0)
  {

    LCD_Clear();
    lcd.setCursor(0, 0);
    LCD_String ("    Temp:");
    LCD_String (temperature);
    lcd.setCursor(0, 1);
   
    delay(500);
    if (temperature > T_threshold) {
      if (temperature > T_threshold) {
      
      }
    }

    delay(500);
    if (temperature < T_threshold) {
      if (temperature < T_threshold) {
       
      }
    }

   
    

      if (temperature < T_threshold) {
        delay(500);
        if (temperature < T_threshold) {
         DIO_SetPinValue(PORTB,LeD
                       , LOW);
        }
      }

      if (temperature > T_threshold) {
        delay(500);
        if (temperature > T_threshold) {
         DIO_SetPinValue(PORTB,LeD, HIGH);
        }
      }

      

        delay(25);

        LCD_Clear();
        lcd.setCursor(0, 0);
        LCD_String ("No Sensor data.");
        lcd.setCursor(0, 1);
        LCD_String ("System Halted.");
       DIO_SetPinValue(PORTB,LeD, LOW);
       
       
      }
      delay(500);
    }
  }
