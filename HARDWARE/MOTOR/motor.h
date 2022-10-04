#ifndef _MOTOR_H
#define _MOTOR_H


//IN1 IN2
// 0   0   ����
// 1   0   ��ת
// 0   1   ��ת

// 1   1   ɲ��

//MOTOR     1         2     3     4
//       A9 C10    C11,12  D67  B3,4  

//Forward    reverse stop
//  ��ת     ��ת   ֹͣ
#define MOTOR_STOP     0
#define MOTOR_FORWARD  1
#define MOTOR_REVERSE  2

#define MOTOR_1        1
#define MOTOR_2        2
#define MOTOR_3        3
#define MOTOR_4        4
void MOTOR_Init(void);//IO��ʼ��

/******************************************/
/*��������ܺ���
**num  --> ����ţ�1~4��
**mode --> ģʽ 
**              0 	   1      2        3 
** 			   ����   ��ת   ��ת     ɲ��
               stop  Forward reverse 
*/
/******************************************/
void MOTOR_Contrl(u8 num,u8 mode);

void motor_on(void);

void motor_off(void);

#endif


