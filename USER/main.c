/********************************************************************************************** 
* 本程序只供学习使用，未经作者许可，不得用于其它任何用途
* 介绍：懒人自动浇花器
* 开发者：楠痩
* 时间：2022.06
* 个人博客：CSDN的id 老子姓李！
* 博客链接：https://blog.csdn.net/qq_44078824?spm=1000.2115.3001.5343
* B站账号：楠痩
* B站演示视频：【六小时手搓自动浇花器】 https://www.bilibili.com/video/BV1BU4y1v76Z?share_source=copy_web&vd_source=0a9d69ff8d9feec15676635d762d2f76
* github仓库：nanshoui163/Automatic_watering_system (网址：https://github.com/nanshoui163/Automatic_watering_system)
* 其他事项：
*          1.外设连接见README.txt
*          2.程序比较简单，直接跑的裸机。六小时手搓，可能有些不足之处，欢迎指正交流
*          3.本人暂时不养花，没时间优化一下。这里给出优化建议，将dth11换成土壤湿度传感器；给不同植物的配置浇水参数；重新自定义APP，而不是用串口助手；增加光敏感功能等等。
*          4.有疑问欢迎b站或博客私信
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


// 显示时间
void MyShowTime(void);
// 展示设计log
void ShowLog(void);

// 显示及播报信息
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

// 显示及播报信息
void ShowVoiceMsg(void)
{
	char str[100] = {0};
	MyShowTime(); // 显示时间
    DTH11_display();// 显示温湿度
    
	sprintf(str,"现在时间%d点%d分，温度为%d摄氏度，湿度为百分之%d",calendar.hour,calendar.min,DHT11Data.temp_int,DHT11Data.humi_int);
	printf("%s",str);
	
}


// 显示时间
void MyShowTime(void)
{
	char water_str[100] = {0};
	int water_x = 0;
	int water_y = 4;

    if(sec_flag!=calendar.sec)
    {
        sec_flag = calendar.sec;
        // 年月日
        OLED_ShowNum(20,0,calendar.w_year,4,16);
        OLED_ShowString(90,0,"-",16);
        OLED_ShowNum(70,0,calendar.w_month,2,16);
        OLED_ShowString(55,0,"-",16);
        OLED_ShowNum(100,0,calendar.w_date,2,16);
        
        // 时:分:秒 8个字符 
        OLED_ShowNum(32,2,calendar.hour,2,16);
        OLED_ShowString(32+8*2,2,":",16);
        OLED_ShowNum(32+8*3,2,calendar.min,2,16);
        OLED_ShowString(32+8*5,2,":",16);
        OLED_ShowNum(32+8*6,2,calendar.sec,2,16);
		
		// 时:分 时:分 7个字符 
		
		sprintf(water_str,"W-%02d:%02d %02d:%02d",watre_time.hour1,watre_time.min1,watre_time.hour2,watre_time.min2);
		printf("%s\r\n",water_str);
		OLED_ShowString(water_x,water_y,(u8 *)water_str,16);
        // DTH11_display();		   // 显示温湿度
        //sprintf(str,"现在时间:%d:%d:%d,温度为%d，湿度为%d %%\r\n",calendar.hour,calendar.min,calendar.sec,DHT11Data.temp_int,DHT11Data.humi_int);
			printf("现在时间:%d:%d:%d\r\n",calendar.hour,calendar.min,calendar.sec);
			
			if(watre_flag == 1)
			{
				watre_flag = 0;
				set_motor_water_time(5);
			}
			
		motor_water_check();
    }
}

// 展示设计log
void ShowLog(void)
{
    OLED_Clear();         // OLED清屏
    OLED_ShowString(28,2,"Design by",16);
    OLED_ShowString(44,4,"nanshou",16);
	delay_ms(1000);       // 等待系统稳定
    OLED_Clear();         // OLED清屏
}

// 硬件设备初始化
void HARDWARE_Init()
{
    
    uart_init(115200);      // 串口1初始化
	usart2_init(9600);
    RTC_Init();	  		    // RTC初始化
    dht11_init();           // dht11初始化
    KEY_EXTIX_Init();
	MOTOR_Init();
	motor_off();
    LED_Init();             // LED初始化
    OLED_Init();            // OLED初始化
    OLED_Clear();           // OLED清屏
    // 展示设计log，等待系统稳定
    ShowLog();
	MOTOR_Init();
	motor_off();
	delay_ms(1000);
	
	BEEP_Init();




// 蜂鸣器提醒
	BEEP_Reminder(200);
	
}


int main(void)
{	
    u8 time_gap = 0;    // 时间间隔变量
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//1设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
  
	HARDWARE_Init();
	set_motor_water_time(3);
	while(1) 
	{	
		MyShowTime(); // 显示时间
		time_gap ++;
		if(time_gap == 100) time_gap = 0;
        delay_ms(5);
		
		if(time_gap == 50) 
		{
			LED0 = !LED0;
			// 显示温湿度
			DTH11_display();
			//
		}
				
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==0)	 	 //下降沿触发
		{
			delay_ms(10);//消抖
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==0)
				set_motor_water_time(3);

		}
	}
	  
}    



