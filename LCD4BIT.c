#include "LCD4BIT.h"

void Delay(unsigned long b)
{
  while (--b!=0); 
}

void write_command(int cmd)
 {
  GPIOB_PCOR  |= 0x00000F00;                    // Clear Data pins , PTA0- PTA3
  GPIOB_PCOR  |= 0x00002000;                            // RW = 0 ,  PTA7        
  GPIOB_PCOR  |= 0X00001000;                            // RS= 0,  PTA6
  GPIOB_PSOR  |= 0x00000F00 & cmd;           //Set Data pins
  GPIOB_PSOR  |= 0x00004000;                            // Enable = 1                                
  Delay(30000);                                   // Provide Delay
  GPIOB_PCOR  |= 0x00004000;                    // Set Enable=0
  }
 
void write_data(int dat)
{
  GPIOB_PCOR  |= 0x00000F00;                    // Clear Data PTA0- PTA3
  GPIOB_PCOR  |= 0x00002000;                   // RW= 0                  
  GPIOB_PSOR  |= 0x00001000;                    //RS= 1
  GPIOB_PSOR |= 0x00000F00 & dat;            // Set Data pins
  GPIOB_PSOR  |= 0x00004000;                     // Enable = 1
  Delay(30000);                                   //Provide Delay
  GPIOB_PCOR  |= 0x00004000;                    //Set Enable=0
  }

void lcd_data(char dat)
{
  write_data(dat << 4);               //msb
  write_data(dat << 8);                    //lsb
}

void lcd_command(char cmd)
{
  write_command(cmd << 4 );           // msb
  write_command(cmd << 8);                 //lsb
}

void printlcd(char *CPtr)
{
  while(*CPtr != '\0')
 {
  lcd_data(*CPtr);
  CPtr++;
  Delay(20000);
 }
}

void init_lcd(void)
 {                                                                              
  GPIOB_PDDR |= 0x00007F00;                 // set GPIOA port PTA0-PTA3 as a output
	GPIOB_PIDR = 0x00007F00; 
  Delay(20000);
  write_command(0x30 << 4);              // msb - 3
  Delay(10000);
  write_command(0x20 << 4);               // msb - 2
	
  lcd_command(0x28);                          /* 5x7 two line in 4 bit mode */
	lcd_command(0x01);                          /* clear display */
  lcd_command(0x06);                          /* auto address inc */
  lcd_command(0x0C);                          /* cursor off */
  lcd_command(0x80);                          /* first location */
  }