#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define     LED0         PAout(8)   // PA8
#define     LED0_IN      PAin(8) // PA8����
#define     LED0_GPIOx   GPIOA
#define 	LED0_PIN     GPIO_Pin_8


void LED_Init(void);//��ʼ��
void LED_Flashing(u8 mode);
#define 	RGB_LED_GPIOx 	    GPIOB
#define 	RGB_LED_GPIO_PIN 	GPIO_Pin_9
#define		RGB_LED_HIGH	    (GPIO_SetBits(RGB_LED_GPIOx,RGB_LED_GPIO_PIN))
#define 	RGB_LED_LOW		    (GPIO_ResetBits(RGB_LED_GPIOx,RGB_LED_GPIO_PIN))


// ���ȵ�λ
extern u8 RGB_LED_LEVEL;
void RGB_LED_Init(void);
void RGB_LED_Write0(void);
void RGB_LED_Write1(void);
void RGB_LED_Reset(void);
void RGB_LED_Write_Byte(uint8_t byte);
void RGB_LED_Write_24Bits(uint8_t green,uint8_t red,uint8_t blue);
//������ɫ�趨��������ɫ�Դ�����
void RGB_LED_Red(void);
void RGB_LED_Green(void);
void RGB_LED_Blue(void);

void RGB_LED_WHITE(void);

void RGB_LED_BRIGHT(uint8_t brightness);

// �������ȵȼ� 0~5
void RGB_LED_SetLevel(uint8_t level);

// ��������
void RGB_LED_BrightnessIncrease(void);
// ���ȼ�С
void RGB_LED_BrightnessDecrease(void);
#endif
