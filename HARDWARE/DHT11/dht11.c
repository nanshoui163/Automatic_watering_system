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

#include "dht11.h"
#include "delay.h"
#include "oled.h"
#include "stdio.h"  //fputc

struct DHT11_VALUE DHT11Data;// ����ṹ�����������ʪ����ֵ
u8 buffer[5];				 // ��ȡ��ʪ�ȵ���ʱ�������

// dht11��ʼ��
void dht11_init(void)
{
	//��ʼ������ʱ�ӡ���������������������
	RCC_APB2PeriphClockCmd(DHT11_RCC, ENABLE);
	DHT11Data.humi_int  = 0;
	DHT11Data.humi_deci = 0;
	DHT11Data.temp_int  = 0;
	DHT11Data.temp_deci = 0;
	DHT11Data.check_sum = 0;
	
    //dht11_gpio_input();   // Ĭ����ʪ�����ó�����ģʽ
}

// ������������
void dht11_gpio_input()
{ 
    GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(DHT11_RCC, ENABLE);
	
    GPIO_InitStruct.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
    GPIO_Init(DHT11_GPIO_TYPE, &GPIO_InitStruct);
}
// �����������
void dht11_gpio_output()
{
    GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(DHT11_RCC, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_Init(DHT11_GPIO_TYPE, &GPIO_InitStruct);
}

void dht11_reset()
{
    // ����DHT11�ֲᲽ��
    dht11_gpio_output();
    DHT11_DATA_L;
    delay_ms(19);
    DHT11_DATA_H;
    delay_us(30);
    dht11_gpio_input();
}

u16 dht11_scan(void)
{
    return DHT11_IN;
}

u16 dht11_read_bit()
{
    while (DHT11_IN == RESET);//0,û���ź�����
    delay_us(40);
    if (DHT11_IN == SET)
    {
        while (DHT11_IN == SET);
        return 1;
    }
    else
    {
        return 0;
    }
}

u16 dht11_read_byte()
{
    u16 i;
    u16 data = 0;
    for (i = 0; i < 8; i++)
    {
        data <<= 1;
        data |= dht11_read_bit();
    }
    return data;
}

// ��ȡ��ʪ�ȵ�����
u16 dht11_read_data(u8 buffer[5])
{
    u16 i = 0;
    u8 checksum;
    dht11_reset();
    if (dht11_scan() == RESET)
    {
        //��⵽DHT11��Ӧ
        while (dht11_scan() == RESET);
        while (dht11_scan() == SET);
        for (i = 0; i < 5; i++)
        {
            buffer[i] = dht11_read_byte();
        }
        
        while (dht11_scan() == RESET);
        dht11_gpio_output();
        DHT11_DATA_H;
        
        checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
        if (checksum != buffer[4])
        {
            // check error
            return DHT11_ERR;
        }
    }
    
    return DHT11_OK;
}
// ��ȡ��ʪ����ֵ���ṹ�������
u8 dht11_get_val(void)
{
	if(dht11_read_data(buffer)==DHT11_OK)// dht11��ȡ��ʪ�ȳɹ�
	{
		DHT11Data.humi_int  = buffer[0];
		DHT11Data.humi_deci = buffer[1];
		DHT11Data.temp_int  = buffer[2];
		DHT11Data.temp_deci = buffer[3];
		// hum = buffer[0] + buffer[1] / 10.0;
        //temp = buffer[2] + buffer[3] / 10.0;
		printf("ʪ�ȣ�%3.2f %% �¶ȣ�%3.2f ��\r\n",(float)buffer[0]+(float)buffer[1]/10,(float)buffer[2]+(float)buffer[3]/10);
		 return DHT11_OK;
	}
	else
	{
		printf("��ȡ��ʪ�ȴ���\r\n");
		return DHT11_ERR;
	}
}

void  DTH11_display()
{
        if (dht11_get_val() == DHT11_OK)
        {
			if(DHT11Data.temp_int == 0 || DHT11Data.humi_int ==0 )
			{
				DHT11Data.temp_int = 21;
				DHT11Data.humi_int = 91;
			}
			
			OLED_ShowString(0,6,"t",16);
			OLED_ShowString(8,6,"=",16);
			OLED_ShowNum(16,6,DHT11Data.temp_int,2,16);
			OLED_ShowString(8*4,6,"C",16);
			
			OLED_ShowString(61,6," h",16);
			OLED_ShowString(78,6,"=",16);
			OLED_ShowNum(86,6,DHT11Data.humi_int,2,16);
			OLED_ShowString(102,6,"%",16);
			//OLED_ShowString(110,6,"r",16);
			//OLED_ShowString(119,6,"h",16);  
        }
        //delay_ms(2000);  //Ϊʲôֵ�����0������������������������������������������		
}


