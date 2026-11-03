#ifndef __NRISTF4_CONFIG_H
#define __NRISTF4_CONFIG_H

#define ECU110WP_DC             1        //45WP 弹用 兵器导控所

#define DEBUG                  (1)      //1为调试打开

#define BaudRate        (19200)
#define ECUSoftVersion		(0x010001)		//V01.00.01 软件版本号 20200924升为该版本
#define BaudRate2       (115200)
#define ComHead0        (0xAA)
#define ComHead1        (0x55)
#define CfgHead0        (0xA5)
#define CfgHead1        (0x5A)


#define ComInstrLen     (14)
#define EngineGearNbr   (13)      //发动机齿数
#define StartMotorGearNbr   (3)      //起动电机齿数
#define CfgInfoLen      (16)          //配置信息长度
#define AckInfoLen      (12)          //应答帧信息长度
#define CfgBuf0         (0xA5)
#define CfgBuf1         (0x5A)


#endif
