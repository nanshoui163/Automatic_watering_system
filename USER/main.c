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

#include "delay.h"
#include "sys.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "usart2.h"
#include "oled.h"
#include "dht11.h"
#include "rtc.h"
#include "beep.h"
#include "motor.h"


// ��ʾʱ��
void MyShowTime(void);
// չʾ���log
void ShowLog(void);

// ��ʾ��������Ϣ
void ShowVoiceMsg(void);

u8 UserMode;
static vu8 sec_flag = 0;

static char sec_water = 0;


void set_motor_water_time(u8 sec)
{
	sec_water =  sec ;
	BEEP_Reminder(20);
}


void motor_water_check()
{
	 if(sec_water > 0)
	 {
		 motor_on();
		 sec_water--;
	 }
	 else
	 {
		 motor_off();
		 sec_water = 0;
	 }
}

// ��ʾ��������Ϣ
void ShowVoiceMsg(void)
{
	char str[100] = {0};
	MyShowTime(); // ��ʾʱ��
    DTH11_display();// ��ʾ��ʪ��
    
	sprintf(str,"����ʱ��%d��%d�֣��¶�Ϊ%d���϶ȣ�ʪ��Ϊ�ٷ�֮%d",calendar.hour,calendar.min,DHT11Data.temp_int,DHT11Data.humi_int);
	printf("%s",str);
	
}


// ��ʾʱ��
void MyShowTime(void)
{
	char water_str[100] = {0};
	int water_x = 0;
	int water_y = 4;

    if(sec_flag!=calendar.sec)
    {
        sec_flag = calendar.sec;
        // ������
        OLED_ShowNum(20,0,calendar.w_year,4,16);
        OLED_ShowString(90,0,"-",16);
        OLED_ShowNum(70,0,calendar.w_month,2,16);
        OLED_ShowString(55,0,"-",16);
        OLED_ShowNum(100,0,calendar.w_date,2,16);
        
        // ʱ:��:�� 8���ַ� 
        OLED_ShowNum(32,2,calendar.hour,2,16);
        OLED_ShowString(32+8*2,2,":",16);
        OLED_ShowNum(32+8*3,2,calendar.min,2,16);
        OLED_ShowString(32+8*5,2,":",16);
        OLED_ShowNum(32+8*6,2,calendar.sec,2,16);
		
		// ʱ:�� ʱ:�� 7���ַ� 
		
		sprintf(water_str,"W-%02d:%02d %02d:%02d",watre_time.hour1,watre_time.min1,watre_time.hour2,watre_time.min2);
		printf("%s\r\n",water_str);
		OLED_ShowString(water_x,water_y,(u8 *)water_str,16);
        // DTH11_display();		   // ��ʾ��ʪ��
        //sprintf(str,"����ʱ��:%d:%d:%d,�¶�Ϊ%d��ʪ��Ϊ%d %%\r\n",calendar.hour,calendar.min,calendar.sec,DHT11Data.temp_int,DHT11Data.humi_int);
			printf("����ʱ��:%d:%d:%d\r\n",calendar.hour,calendar.min,calendar.sec);
			
			if(watre_flag == 1)
			{
				watre_flag = 0;
				set_motor_water_time(5);
			}
			
		motor_water_check();
    }
}

// չʾ���log
void ShowLog(void)
{
    OLED_Clear();         // OLED����
    OLED_ShowString(28,2,"Design by",16);
    OLED_ShowString(44,4,"nanshou",16);
	delay_ms(1000);       // �ȴ�ϵͳ�ȶ�
    OLED_Clear();         // OLED����
}

// Ӳ���豸��ʼ��
void HARDWARE_Init()
{
    
    uart_init(115200);      // ����1��ʼ��
	usart2_init(9600);
    RTC_Init();	  		    // RTC��ʼ��
    dht11_init();           // dht11��ʼ��
    KEY_EXTIX_Init();
	MOTOR_Init();
	motor_off();
    LED_Init();             // LED��ʼ��
    OLED_Init();            // OLED��ʼ��
    OLED_Clear();           // OLED����
    // չʾ���log���ȴ�ϵͳ�ȶ�
    ShowLog();
	MOTOR_Init();
	motor_off();
	delay_ms(1000);
	
	BEEP_Init();




// ����������
	BEEP_Reminder(200);
	
}


int main(void)
{	
    u8 time_gap = 0;    // ʱ��������
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//1�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
  
	HARDWARE_Init();
	set_motor_water_time(3);
	while(1) 
	{	
		MyShowTime(); // ��ʾʱ��
		time_gap ++;
		if(time_gap == 100) time_gap = 0;
        delay_ms(5);
		
		if(time_gap == 50) 
		{
			LED0 = !LED0;
			// ��ʾ��ʪ��
			DTH11_display();
			//
		}
				
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==0)	 	 //�½��ش���
		{
			delay_ms(10);//����
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==0)
				set_motor_water_time(3);

		}
	}
	  
}    



