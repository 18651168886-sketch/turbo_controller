#ifndef _NRISTF4_SDIO_H
#define _NRISTF4_SDIO_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stdlib.h"
#include "NRISTF4_Define.h"
#include "ff.h"
//#include "nristf4_fram.h"
#include "fram.h"
#include "stdio.h"
#include "string.h"

#define SDFILEWRITEBUFSIZE 100
typedef struct{
    char FileName[30];
    FIL fnew;                      /* 文件对象 */
    FRESULT res_sd;                /* 文件操作结果 */
    UINT fnum;                     /* 文件成功读写数量 */
    u8 Flag_FatfsSuc;

}FATFS_STRUCT;
extern FATFS_STRUCT sFATFS;              //ADC 定义


void InitSDIO(void);
 void FileCreate(void);
void SD_WriteHead(void);
void SD_WriteData(void);
void SD_FileInit(void);
void SD_FileWrite(void);
void SD_FileWriteNew(void);
void u32tostr(unsigned long dat , unsigned char *str);
unsigned long strtou32( char *str);
u32 GetSDFileMAXIndex(char *path);

void PrintSDFileList(char *path);
u32 Myatoi(char * str);
extern u8 SDErrorFlag;
#endif


