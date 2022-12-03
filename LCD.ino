#include <avr/io.h>        /* Include AVR std. library file */
#include <util/delay.h>   /* Include Delay header file */
#include "LCD.h"

#define lcd_Clear           0x01          /* replace all characters with ASCII 'space'                       */
#define lcd_Home            0x02          /* return cursor to first position on first line                   */
#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0x80          // set cursor position
void LCD_Command( unsigned char cmnd )
{
 /* Set RS to LOW */
 DIO_SetPinValue(PORTA, 0, LOW);

  /* Set R/W to LOW */
  DIO_SetPinValue(PORTA, 1, LOW);

  /* Set E to HIGH  */
  DIO_SetPinValue(PORTA, 2, HIGH);

  /* Load Command on Data bus */
  DIO_SetPortValue(PORTD, cmnd);

  /* Set E to LOW */
  DIO_SetPinValue(PORTA, 2, LOW);

  /* Wait for E to settle */
  _delay_ms(5);

  /* Set E to HIGH */
  DIO_SetPinValue(PORTA, 2, HIGH);

  /* Delay for 10ms to let the LCD execute command */
  _delay_ms(10);
}


void LCD_Char( unsigned char data )
{
  /* Set RS to HIG */
  DIO_SetPinValue(PORTA, 0, HIGH);

  /* Set R/W to LOW */
  DIO_SetPinValue(PORTA, 1, LOW);

  /* Set E to HIGH */
  DIO_SetPinValue(PORTA, 2, HIGH);

  /* Load Command on Data bus */
  DIO_SetPortValue(PORTD, data);

  /* Set E to LOW */
  DIO_SetPinValue(PORTA, 2, LOW);

  /* Wait for E to settle */
  _delay_ms(5);

  /* Set E to HIGH */
  DIO_SetPinValue(PORTA, 2, HIGH);

  /* Delay to let the LCD Display the character */
  _delay_ms(10);
}

void LCD_Init (void)      /* LCD Initialize function */
{
  /* Delay 30ms to ensure the initialization of the LCD driver */
  _delay_ms(30);

  /* Return Home  */
  LCD_Command(lcd_Home);
  _delay_ms(15);

  /* Function Set  */
  LCD_Command(lcd_FunctionSet8bit);
  _delay_ms(1);

  /* Display ON OFF Control */
  LCD_Command(lcd_DisplayOn);
  _delay_ms(1);

  /* Clear Display */
  LCD_Command(lcd_Clear);
  _delay_ms(15);

  /* Entry Mode Set  */
  LCD_Command(lcd_EntryMode);
  _delay_ms(2);
}

void LCD_String (char *str)   /* SEnd string to LCD function */
{
    /* Local loop index */
  u8 u8Index = 0;
  u8 iteration=0;
//  while (pu8StringCpy[u8Index] != '\0')
  for (iteration=0; iteration<u8Index ; iteration++)
  {

    /* Write Character on LCD */
    LCD_Char(str[iteration]);

//    /* Increment local loop index */
    u8Index++;

    /* Delay to let the LCD show the character */
    _delay_ms(2);
  }
}

void LCD_String_xy (char row, char pos, char *str)  /* SEnd string to LCD with xy position */
{
  if (row == 0 && pos<16)
    LCD_Command((pos & 0x0F)|0x80);                   /* Command of fiSSt row and required position<16 */
  else if (row == 1 && pos<16)
    LCD_Command((pos & 0x0F)|0xC0);                   /* Command of fiSSt row and required position<16 */
    
  LCD_String(str);                                  /* Call LCD string function */
}

void LCD_Clear()
{
  LCD_Command (0x01);   /* Clear display */
  _delay_ms(2);
  LCD_Command (0x80);   /* CuSSor at home position */
}
