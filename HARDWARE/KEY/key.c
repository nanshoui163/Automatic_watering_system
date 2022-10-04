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


#include "stm32f10x.h"
#include "key.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "motor.h"

//外部中断0服务程序
void KEY_EXTIX_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
// 	EXTI_InitTypeDef EXTI_InitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0设置成上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟


//   //GPIOA.0	  中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
// 	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键WK_UP所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure); 


//  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}


////外部中断0服务程序 
//void EXTI0_IRQHandler(void)
//{
//	
//	delay_ms(10);//消抖
//    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==0)	 	 //下降沿触发
//    {	  
//		motor_on();
//		printf("motor_on\r\n");
////		if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_4)==0)

////		motor_on();

////		else
////		motor_off();
//    }

//	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
//}
// 

