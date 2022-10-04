/********************************************************************************************** 
* ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
* ���ܣ������Զ�������
* �����ߣ�骯l
* ʱ�䣺2022.06
* ���˲��ͣ�CSDN��id �������
* �������ӣ�https://blog.csdn.net/qq_44078824?spm=1000.2115.3001.5343
* Bվ�˺ţ�骯l
* Bվ��ʾ��Ƶ������Сʱ�ִ��Զ��������� https://www.bilibili.com/video/BV1BU4y1v76Z?share_source=copy_web&vd_source=0a9d69ff8d9feec15676635d762d2f76
* github�ֿ⣺nanshoui163/Automatic_watering_system (��ַ��https://github.com/nanshoui163/Automatic_watering_system)
* �������
*          1.�������Ӽ�README.txt
*          2.����Ƚϼ򵥣�ֱ���ܵ��������Сʱ�ִ꣬������Щ����֮������ӭָ������
*          3.������ʱ��������ûʱ���Ż�һ�¡���������Ż����飬��dth11��������ʪ�ȴ�����������ֲͬ������ý�ˮ�����������Զ���APP���������ô������֣����ӹ����й��ܵȵȡ�
*          4.�����ʻ�ӭbվ�򲩿�˽��
**********************************************************************************************/


#include "led.h"
#include "delay.h"
#include "core_cm3.h"

//////////////////////////////////////////////////////////////////////////////////	 
//LED PA8
////////////////////////////////////////////////////////////////////////////////// 	   

// ���ȵ�λ
u8 RGB_LED_LEVEL = 0;
//��ʼ��PA8Ϊ�����.��ʹ��ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
 GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 �����

}

void LED_Flashing(u8 mode)
{
    static u16 cnt = 0;
    u16 max = 0;
    u8 state = LED0_IN;
    if(mode >= 3) mode = 0;
    
    delay_ms(1);
    cnt++;
    switch(mode)
    {
        case 0:max = 200;if(cnt>=max) cnt =0;else LED0 = state?0:1;break;
        case 1:max = 150;if(cnt>=max) cnt =0; else LED0 = state?0:1;;break;
        case 2:max = 100;if(cnt>=max) cnt =0; else LED0 = state?0:1;;break;
    }
}


void RGB_LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
	GPIO_InitStructure.GPIO_Pin = RGB_LED_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(RGB_LED_GPIOx, &GPIO_InitStructure);					
	GPIO_SetBits(RGB_LED_GPIOx,RGB_LED_GPIO_PIN);						 
}

/********************************************************/
//
/********************************************************/
void RGB_LED_Write0(void)
{
	RGB_LED_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();
	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}

/********************************************************/
//
/********************************************************/

void RGB_LED_Write1(void)
{
	RGB_LED_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}

void RGB_LED_Reset(void)
{
	RGB_LED_LOW;
	delay_us(80);
}

void RGB_LED_Write_Byte(uint8_t byte)
{
	uint8_t i;

	for(i=0;i<8;i++)
		{
			if(byte&0x80)
				{
					RGB_LED_Write1();
			}
			else
				{
					RGB_LED_Write0();
			}
		byte <<= 1;
	}
}

void RGB_LED_Write_24Bits(uint8_t green,uint8_t red,uint8_t blue)
{
	RGB_LED_Write_Byte(green);
	RGB_LED_Write_Byte(red);
	RGB_LED_Write_Byte(blue);
}


//������ɫ�趨��������ɫ�Դ�����
void RGB_LED_Red(void)
{
	 uint8_t i;
	//4��LEDȫ�ʵ�
	for(i=0;i<8;i++)
		{
			RGB_LED_Write_24Bits(0, 0xff, 0);
	}
}

void RGB_LED_Green(void)
{
	uint8_t i;

	for(i=0;i<4;i++)
		{
			RGB_LED_Write_24Bits(0xff, 0, 0);
	}
}

void RGB_LED_Blue(void)
{
	uint8_t i;

	for(i=0;i<4;i++)
		{
			RGB_LED_Write_24Bits(0, 0, 0xff);
	}
}


void RGB_LED_WHITE(void)
{
    uint8_t i;
	//4��LEDȫ�ʵ�
	for(i=0;i<8;i++)
		{
			RGB_LED_Write_24Bits(0xff, 0xff, 0xff);
	}
        
}

void RGB_LED_BRIGHT(uint8_t brightness)
{
   // __disable_irq();   // �ر����ж�

    uint8_t i;
	for(i=0;i<8;i++)
		{
			RGB_LED_Write_24Bits(brightness, brightness, brightness);
	}
    // __enable_irq();    // �������ж�
}

// �������ȵȼ�
void RGB_LED_SetLevel(uint8_t level)
{
    if(level > 5) level = 5;
    RGB_LED_BRIGHT(level*50);
    RGB_LED_LEVEL = level;

}


// ��������
void RGB_LED_BrightnessIncrease(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_8);
    RGB_LED_LEVEL++;
    RGB_LED_SetLevel(RGB_LED_LEVEL);
    GPIO_SetBits(GPIOA,GPIO_Pin_8);
}

// ���ȼ�С
void RGB_LED_BrightnessDecrease(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_8);
    if(RGB_LED_LEVEL>0)RGB_LED_LEVEL--;
    RGB_LED_SetLevel(RGB_LED_LEVEL);
    GPIO_SetBits(GPIOA,GPIO_Pin_8);
}
