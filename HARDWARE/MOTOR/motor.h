#ifndef _MOTOR_H
#define _MOTOR_H


//IN1 IN2
// 0   0   待机
// 1   0   正转
// 0   1   反转

// 1   1   刹车

//MOTOR     1         2     3     4
//       A9 C10    C11,12  D67  B3,4  

//Forward    reverse stop
//  正转     反转   停止
#define MOTOR_STOP     0
#define MOTOR_FORWARD  1
#define MOTOR_REVERSE  2

#define MOTOR_1        1
#define MOTOR_2        2
#define MOTOR_3        3
#define MOTOR_4        4
void MOTOR_Init(void);//IO初始化

/******************************************/
/*电机控制总函数
**num  --> 马达编号（1~4）
**mode --> 模式 
**              0 	   1      2        3 
** 			   待机   正转   反转     刹车
               stop  Forward reverse 
*/
/******************************************/
void MOTOR_Contrl(u8 num,u8 mode);

void motor_on(void);

void motor_off(void);

#endif


