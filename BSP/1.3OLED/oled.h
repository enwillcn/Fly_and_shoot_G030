#ifndef __OLED_H
#define __OLED_H 

//#include "sys.h"
#include "stdlib.h"	
#include "main.h"

//-----------------OLED端口定义---------------- 

//#define OLED_SCL_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET)//SCL
//#define OLED_SCL_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET)

//#define OLED_SDA_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET)//SDA
//#define OLED_SDA_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET)

//#define OLED_RES_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET)//RES
//#define OLED_RES_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET)

//#define OLED_DC_Clr()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET)//DC
//#define OLED_DC_Set()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET)
// 		     
//#define OLED_CS_Clr()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)//CS
//#define OLED_CS_Set()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)


// #define OLED_SCL_Clr() GPIOA->BSRR = (uint32_t)(GPIO_PIN_11 << 16)
// #define OLED_SCL_Set() GPIOA->BSRR = (uint32_t)GPIO_PIN_11

#define OLED_SCL_Clr() GPIOA->BSRR = (uint32_t)(GPIO_PIN_0 << 16)               //SPI1
#define OLED_SCL_Set() GPIOA->BSRR = (uint32_t)GPIO_PIN_0


// #define OLED_SDA_Clr() GPIOA->BSRR = (uint32_t)(GPIO_PIN_10 << 16)
// #define OLED_SDA_Set() GPIOA->BSRR = (uint32_t)GPIO_PIN_10

#define OLED_SDA_Clr() GPIOA->BSRR = (uint32_t)(GPIO_PIN_10 << 16)             //SPI1    
#define OLED_SDA_Set() GPIOA->BSRR = (uint32_t)GPIO_PIN_10

#define OLED_RES_Clr() GPIOA->BSRR = (uint32_t)(GPIO_PIN_9 << 16)
#define OLED_RES_Set() GPIOA->BSRR = (uint32_t)GPIO_PIN_9

#define OLED_DC_Clr()  GPIOC->BSRR = (uint32_t)(GPIO_PIN_6 << 16)
#define OLED_DC_Set()  GPIOC->BSRR = (uint32_t)GPIO_PIN_6
 		     
#define OLED_CS_Clr()  GPIOA->BSRR = (uint32_t)(GPIO_PIN_11 << 16)
#define OLED_CS_Set()  GPIOA->BSRR = (uint32_t)GPIO_PIN_11


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_ClearPoint(uint8_t x,uint8_t y);
void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_WR_Byte(uint8_t dat,uint8_t mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t mode);
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode);
void OLED_ShowChar6x8(uint8_t x,uint8_t y,uint8_t chr,uint8_t mode);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1,uint8_t mode);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1,uint8_t mode);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1,uint8_t mode);
void OLED_ScrollDisplay(uint8_t num,uint8_t space,uint8_t mode);
void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t sizex,uint8_t sizey,uint8_t BMP[],uint8_t mode);
void OLED_Init(void);

void OLED_Refresh_SPI(void);
void OLED_Init_SPI(void);

#endif

