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

#include "stm32f10x.h"
#include "motor.h"
#include "sys.h" 
#include "delay.h"
#include "motor.h"

/* ģ�����˵�� */
//IN1 IN2
// 0   0   ����
// 1   0   ��ת
// 0   1   ��ת

// 1   1   ɲ��


void MOTOR_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��ABCDʱ��
	
		
	
	/*************MOTOR1��2->A4****************/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//MOTOR1_1 A4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO���ٶ�Ϊ50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼGPIOA
	motor_off();
}


/* һ����PA4��һ����GND */
/*
ע�ⷽ�򣬷�����˿��ܳ鲻��ˮ
*/
void motor_on(void)
{
	PAout(4)=1;
}

void motor_off(void)
{
	PAout(4)=0;
}
