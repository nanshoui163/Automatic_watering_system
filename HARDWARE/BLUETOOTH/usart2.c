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
#include "usart2.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
#include "led.h"
#include "rtc.h" 
#include "motor.h"
// 串口2接蓝牙
//串口接收缓存区 	
u8 USART2_RX_BUF[USART2_MAX_RECV_LEN]; 				//接收缓冲,最大USART2_MAX_RECV_LEN个字节.
u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 			  //发送缓冲,最大USART2_MAX_SEND_LEN字节

//通过判断接收连续2个字符之间的时间差不大于10ms来决定是不是一次连续的数据.
//如果2个字符接收间隔超过10ms,则认为不是1次连续数据.也就是超过10ms没有接收到
//任何数据,则表示此次接收完毕.
//接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
vu16 USART2_RX_STA=0;   	

extern u8 UserMode;
extern u8 RGB_LED_LEVEL;
 
// 帮助信息
const u8 Help_Inf[] = "help:Please add help information\r\n"
                        "Remember to enter the command line and replace 0d 0A in the settings\r\n3. Code GB2312\r\n";

// 按住help，获取提示信息

//蓝牙发送单片机时间
void BT_Send_Time(void)
{
	char time_chr[50];
	char cmd[5] = "t 1"; 
	RTC_Get();//把计数值换成结构体值
	//如果sprintf解析成功，
	if (sprintf(time_chr, "%s %04u-%02u-%02u %02u:%02u:%02u\r\n", cmd, calendar.w_year, calendar.w_month, calendar.w_date, calendar.hour, calendar.min, calendar.sec))
	{
		
		u2_printf("%s", time_chr);
	}
	else
	{
		u2_printf("t 0\r\n");
	}

}

void BT_Set_Water_Time(void)
{
	char T;
	//char time[] = "W 10:30 14:20\r\n";
	
	//char buf[3];
	if(sscanf((u8 *)USART2_RX_BUF,"%c %u:%u %u:%u\r\n",&T,&(watre_time.hour1),&( watre_time.min1) ,&(watre_time.hour2),&( watre_time.min2)))
	{
		//printf("T %04u-%02u-%02u %02u:%02u:%02u", calendar.w_year, calendar.w_month, calendar.w_date, calendar.hour, calendar.min, calendar.sec);
		
		//保存数据
		//seting_rtc(ENABLE);//开启RTC,设置时间
		u2_printf("W 1\r\n");//返回W 1

	}
	else
	{
		u2_printf("W 0\r\n");
	}
}

void BT_Set_Time()
{
		char T;
	 u32 year;
	//char time[] = "T 2022-9-20 13:9:0\r\n";
	
	//char buf[3];
	if(sscanf((char *)USART2_RX_BUF,"%c %lu-%u-%u %u:%u:%u\r\n",&T,&year, &(calendar.w_month), &(calendar.w_date), &(calendar.hour),&( calendar.min), &(calendar.sec)))
	{
		calendar.w_year = year;
		printf("T %04u-%02u-%02u %02u:%02u:%02u", calendar.w_year, calendar.w_month, calendar.w_date, calendar.hour, calendar.min, calendar.sec);
		
		//保存数据
		seting_rtc(ENABLE);//开启RTC,设置时间
		u2_printf("T 1\r\n");//返回T 1

	}
	else
	{
		u2_printf("T 0\r\n");
	}
	
}
extern void set_motor_water_time(u8 sec);
void User_Handler(void)
{
    u8 len = USART2_RX_STA&0X3FFF;
    
//    if(USART2_RX_BUF[0] == 'h'&&USART2_RX_BUF[1]== 'e'&&USART2_RX_BUF[2]== 'l'&&USART2_RX_BUF[3]== 'p')
//    {
//        u2_printf("%s",Help_Inf);
//    }
    
    if(strstr((const char *)USART2_RX_BUF,"CONNECTING")){
        u2_printf("CONNECTING\r\n");
    }
    //else if(len>=5&&USART2_RX_BUF[0] == 'c'&&USART2_RX_BUF[1]== 'm'&&USART2_RX_BUF[2]== 'd'&&USART2_RX_BUF[3]== ' ')
    else switch(USART2_RX_BUF[0])
    {
		
		case 't':BT_Send_Time();break;
		case 'T':BT_Set_Time(); break;
		case 'W':BT_Set_Water_Time(); break;
		case 'w':set_motor_water_time(5); break;
		default: u2_printf("蓝牙异常"); 

                
    }

    
    // 清空串口2数据缓存
    USART2_RX_STA = 0;
    USART2_RX_BUF[0] = '\0';
                      
}


void USART2_IRQHandler(void)
{
	u8 Res;	    
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收到数据
	{	 
	
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		//USART_SendData(USART1,Res);
		if((USART2_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART2_RX_STA&0x4000)//接收到了0x0d
			{
				if(Res!=0x0a)    
                {
                    
                    USART2_RX_STA=0;//接收错误,重新开始 
                    u2_printf("指令格式错误，请加回车换行\r\n");
                }
				else {
                        USART2_RX_STA|=0x8000;	//接收完成了
                        // 添加结束标志
                        USART2_RX_BUF[USART2_RX_STA&0X3FFF]='\0' ;
                        printf("蓝牙发送指令：%s",USART2_RX_BUF);
                        User_Handler();// 用户数据处理
                     }
			}
			else //还没收到0X0D
			{	
				if(Res==0x0d)USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART2_MAX_RECV_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
       
	
    
    
    }  				 											 
}   



	

//初始化IO 串口2
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率	  
void usart2_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //串口2时钟使能

 	USART_DeInit(USART2);  //复位串口2
		 //USART2_TX   PA2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA2
   
    //USART2_RX	  PA3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PA3
	
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
	USART_Init(USART2, &USART_InitStructure); //初始化串口2
  

	USART_Cmd(USART2, ENABLE);                    //使能串口 
	
	//使能接收中断
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断   
	
	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	USART2_RX_STA=0;		//清零

}

//串口2,printf 函数
//确保一次发送数据不超过USART2_MAX_SEND_LEN字节
void u2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
}
void PrintCom(uint8_t *DAT,uint8_t len)
{
	uint8_t i;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2,*DAT);
		DAT++;
	}	
}




















