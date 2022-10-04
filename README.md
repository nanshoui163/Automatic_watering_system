# Automatic_watering_system
自动浇花系统


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

2022.6
所使用单片机的硬件资源:
	串口1：TX-->PA9,RX-->PA10
	串口2：波特率9600，蓝牙串口模块，RXD-->PA2(TX)  RXD-->PA3(RX) 通信协议：必须以回车换行结尾。
	OLED_IIC屏幕：电源3.3V，SDA PB15，SCL  PB13
	按键：WK_UP PA0
	蜂鸣器：PB8
	电机驱动板：一个接PA4，一个接GND。注意方向，方向错了可能抽不了水
	光敏电阻：PF8 ADC3_IN6，暂未用到。
	指示LED灯：PA8，PB14 可不使用
	
蓝牙APP：蓝牙调试器（注意在设置里替换换行符 \r\n 0D 0A；编码选GB2312）。
	     通信协议阅读usart2.c部分代码。

其他：keil的工程文件在USER目录下，额外资料见“其他资料”文件夹。
