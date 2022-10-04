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
#include "motor.h"
#include "sys.h" 
#include "delay.h"
#include "motor.h"

/* 模块控制说明 */
//IN1 IN2
// 0   0   待机
// 1   0   正转
// 0   1   反转

// 1   1   刹车


void MOTOR_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能ABCD时钟
	
		
	
	/*************MOTOR1，2->A4****************/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//MOTOR1_1 A4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO口速度为50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始GPIOA
	motor_off();
}


/* 一个接PA4，一个接GND */
/*
注意方向，方向错了可能抽不了水
*/
void motor_on(void)
{
	PAout(4)=1;
}

void motor_off(void)
{
	PAout(4)=0;
}
