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

#include "beep.h"
#include "delay.h"

//��ʼ��PB8Ϊ�����.��ʹ������ڵ�ʱ��		    
//��������ʼ��
void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��GPIOB�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB.8
 
 GPIO_ResetBits(GPIOB,GPIO_Pin_8);//���0���رշ��������

}



// ����������
void BEEP_Reminder(u8 ms)
{
   
    BEEP=1;		  
	delay_ms(ms);//��ʱ
    BEEP=0;
    delay_ms(ms);//��ʱ

}
