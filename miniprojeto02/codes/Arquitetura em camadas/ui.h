#ifndef UI_H
#define UI_H

//#include "lcd.h"

#define MENU1 1
#define MENU2 12
#define MENU3 13
/*
//Define portas do display LCD
Lcd_PortType ports[] = {
        D4_GPIO_Port, D5_GPIO_Port, D6_GPIO_Port, D7_GPIO_Port
        
};

//Define os pinos do display
Lcd_PinType pins[] = {D4_Pin, D5_Pin, D6_Pin, D7_Pin};

//Create Lcd_HandleTypeDef and initialize
Lcd_HandleTypeDef lcd = Lcd_create(ports, pins, RS_GPIO_Port, RS_Pin, EN_GPIO_Port, EN_Pin, LCD_4_BIT_MODE);
*/
int updateMenu(int menu);

#endif