#include <avr/io.h>
#include <util/delay.h>

// Function Prototypes
void LCD_init();
void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
void LCD_String (char *str);   /* Send string to LCD function */
void LCD_String_xy (char row, char pos, char *str);  /* Send string to LCD with xy position */
void LCD_Clear();