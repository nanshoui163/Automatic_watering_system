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
#include "usart2.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
#include "led.h"
#include "rtc.h" 
#include "motor.h"
// ����2������
//���ڽ��ջ����� 	
u8 USART2_RX_BUF[USART2_MAX_RECV_LEN]; 				//���ջ���,���USART2_MAX_RECV_LEN���ֽ�.
u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 			  //���ͻ���,���USART2_MAX_SEND_LEN�ֽ�

//ͨ���жϽ�������2���ַ�֮���ʱ������10ms�������ǲ���һ������������.
//���2���ַ����ռ������10ms,����Ϊ����1����������.Ҳ���ǳ���10msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���
vu16 USART2_RX_STA=0;   	

extern u8 UserMode;
extern u8 RGB_LED_LEVEL;
 
// ������Ϣ
const u8 Help_Inf[] = "help:Please add help information\r\n"
                        "Remember to enter the command line and replace 0d 0A in the settings\r\n3. Code GB2312\r\n";

// ��סhelp����ȡ��ʾ��Ϣ

//�������͵�Ƭ��ʱ��
void BT_Send_Time(void)
{
	char time_chr[50];
	char cmd[5] = "t 1"; 
	RTC_Get();//�Ѽ���ֵ���ɽṹ��ֵ
	//���sprintf�����ɹ���
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
		
		//��������
		//seting_rtc(ENABLE);//����RTC,����ʱ��
		u2_printf("W 1\r\n");//����W 1

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
		
		//��������
		seting_rtc(ENABLE);//����RTC,����ʱ��
		u2_printf("T 1\r\n");//����T 1

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
		default: u2_printf("�����쳣"); 

                
    }

    
    // ��մ���2���ݻ���
    USART2_RX_STA = 0;
    USART2_RX_BUF[0] = '\0';
                      
}


void USART2_IRQHandler(void)
{
	u8 Res;	    
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//���յ�����
	{	 
	
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		//USART_SendData(USART1,Res);
		if((USART2_RX_STA&0x8000)==0)//����δ���
		{
			if(USART2_RX_STA&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)    
                {
                    
                    USART2_RX_STA=0;//���մ���,���¿�ʼ 
                    u2_printf("ָ���ʽ������ӻس�����\r\n");
                }
				else {
                        USART2_RX_STA|=0x8000;	//���������
                        // ��ӽ�����־
                        USART2_RX_BUF[USART2_RX_STA&0X3FFF]='\0' ;
                        printf("��������ָ�%s",USART2_RX_BUF);
                        User_Handler();// �û����ݴ���
                     }
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART2_MAX_RECV_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
       
	
    
    
    }  				 											 
}   



	

//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void usart2_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //����2ʱ��ʹ��

 	USART_DeInit(USART2);  //��λ����2
		 //USART2_TX   PA2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA2
   
    //USART2_RX	  PA3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PA3
	
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(USART2, &USART_InitStructure); //��ʼ������2
  

	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
	
	//ʹ�ܽ����ж�
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�   
	
	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	USART2_RX_STA=0;		//����

}

//����2,printf ����
//ȷ��һ�η������ݲ�����USART2_MAX_SEND_LEN�ֽ�
void u2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
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




















