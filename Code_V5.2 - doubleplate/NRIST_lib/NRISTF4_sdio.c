#include "NRISTF4_sdio.h"
#include "NRIST_Comm.h"
//#include "NRISTF4_Include.h"
//#include "sdio.h"
//#include "adc.h"

u8 SDErrorFlag = 0;

/******************************************************/
FATFS_STRUCT sFATFS;              //fatfs 定义



/*********************************************************************************
** 函数名称：InitSDIO
** 编写者  ：樊瑜
** 参考资料：无
** 函数功能：SD初始化
** 输入参数:
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void InitSDIO(void)
{
    FATFS fs;                      /* FatFs文件系统对象 */
	//在外部SPI Flash挂载文件系统，文件系统挂载时会对SPI设备初始化
	//增加一个逻辑驱动
	sFATFS.res_sd = f_mount(&fs,"0:",1);

	/*----------------------- 格式化测试 ---------------------------*/
	/* 如果没有文件系统就格式化创建创建文件系统 */
	if(sFATFS.res_sd == FR_NO_FILESYSTEM)
	{
    /* 格式化 */
		sFATFS.res_sd=f_mkfs("0:",0,0);

		if(sFATFS.res_sd == FR_OK)
		{
      /* 格式化后，先取消挂载 */
			sFATFS.res_sd = f_mount(NULL,"0:",1);
      /* 重新挂载	*/
			sFATFS.res_sd = f_mount(&fs,"0:",1);

			sFATFS.Flag_FatfsSuc = 0; // 文件系统挂载成功
		}
		else
		{
             sFATFS.Flag_FatfsSuc = 1; //格式化失败
		}
	}
	else if(sFATFS.res_sd != FR_OK)
	{
		sFATFS.Flag_FatfsSuc = 2; //挂载文件系统失败
	}
	else
	{
		sFATFS.Flag_FatfsSuc = 0; // 文件系统挂载成功
	}
}



/*********************************************************************************
** 函数名称：SDFileInit
** 编写者  ：张迎
** 参考资料：无
** 函数功能：新建sd卡文件并写入表头
** 输入参数：
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：文件名序号保存在Flash中，应注意是片内还是片外Flash，存取方式不同
*********************************************************************************/

void SD_FileInit(void)
{
	u32 FileIndex_u32;
    BYTE FileHead[] =              /* 写缓冲区*/
        "指令回传\t总温\t电源电压\t排气温度\t油压\t副油开度\t主油开度\t换算转速\t开关量输出\t物理转速\t油泵目标转速\t电机开度\t引擎状态\t报警标识\t帧计数\tECU温度\t装订转速\t高度\t空速\t油泵反馈转速\n";
//    BYTE ReadBuffer[1024]={0};        /* 读缓冲区 */

	FileIndex_u32 = GetSDFileMAXIndex("0:") + 1;		//读取flash
    sprintf(sFATFS.FileName , "0:ECU_110WP_%08d.txt" , FileIndex_u32);

	sFATFS.res_sd = f_open(&sFATFS.fnew, sFATFS.FileName , FA_CREATE_ALWAYS | FA_WRITE | FA_OPEN_ALWAYS | FA_READ);
	if ( sFATFS.res_sd == FR_OK )
	{
		/* 将指定存储区内容写入到文件内L*/
		sFATFS.res_sd = f_write(&sFATFS.fnew , FileHead , sizeof(FileHead) , &sFATFS.fnum);
//		f_lseek(&sFATFS.fnew , 0);
//		sFATFS.res_sd = f_read(&sFATFS.fnew , (char *)ReadBuffer , sizeof(ReadBuffer) , &sFATFS.fnum);
//		f_close(&sFATFS.fnew);
	}
    if(sFATFS.res_sd != FR_OK)
    {
        SDErrorFlag = 1;
    }

}
/*********************************************************************************
** 函数名称：SD_FileWrite
** 编写者  ：张迎
** 参考资料：无
** 函数功能：向新建的文件中写入数据
** 输入参数：
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
void SD_FileWriteNew(void)
{
    BYTE WriteBuffer[SDFILEWRITEBUFSIZE] = {0};

//    BYTE ReadBuffer[1024]={0};        /* 读缓冲区 */
	memset(WriteBuffer , 0 , sizeof(WriteBuffer));
 	sFATFS.res_sd = f_open(&sFATFS.fnew, sFATFS.FileName , FA_WRITE | FA_OPEN_ALWAYS | FA_READ);
	f_lseek(&sFATFS.fnew , ((FIL*)&sFATFS.fnew)->fptr );
	sFATFS.res_sd = f_write(&sFATFS.fnew , WriteBuffer , sizeof(WriteBuffer) , &sFATFS.fnum);

	f_lseek(&sFATFS.fnew , 0);
	//s_sd = f_read(&sFATFS.fnew , (char *)ReadBuffer , sizeof(ReadBuffer) , &sFATFS.fnum);
	f_close(&sFATFS.fnew);
}
/*********************************************************************************
** 函数名称：SD_FileWrite
** 编写者  ：张迎
** 参考资料：无
** 函数功能：向新建的文件中写入数据
** 输入参数：
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/
u16 sdSaveMaxTime = 0;
u8 cnt = 0;
void SD_FileWrite(void)
{
	static u16 sdSaveCnt = 0;
	char WriteBuf[100] = {0};
	if(0 == sSDIO.FlagSaveAlarm)
	{
			cnt++;
			Timer.SDCard.Enble = 1;
			Timer.SDCard.Value = 0;
			memset(WriteBuf , 0 , sizeof(WriteBuf));
			sprintf(WriteBuf , "%d\t%f\t%f\t%f\t%f\t%d\t%d\t%f\t%d\t%f\t%f\t%d\t%d\t%d\t%d\t%f\t%f\t%f\t%f\t%f\r\n" ,
			(uint8_t)pSaveData_Out.savedata1 , //指令回传                
			pSaveData_Out.savedata2 , //总温
			pSaveData_Out.savedata3 ,//电源电压
			pSaveData_Out.savedata4 ,//排气温度
			pSaveData_Out.savedata5 ,//燃油压力
			(uint8_t)pSaveData_Out.savedata6 ,//副油开度
			(uint8_t)pSaveData_Out.savedata7 ,//主油开度
			pSaveData_Out.savedata8 ,//换算转速
			(uint8_t)pSaveData_Out.savedata9 ,//开关量输出
			pSaveData_Out.savedata10 ,//物理转速
			pSaveData_Out.savedata11 ,//油泵目标转速
			(uint8_t)pSaveData_Out.savedata12 ,//电机开度
			(uint8_t)pSaveData_Out.savedata13 ,//引擎状态
			(uint8_t)pSaveData_Out.savedata14 ,//报警标识
			(uint8_t)cnt ,//帧计数
			pSaveData_Out.savedata16 ,//ECU温度
			pSaveData_Out.savedata17 ,//装订转速
			pSaveData_Out.savedata18 ,//高度
			pSaveData_Out.savedata19 ,//速度
			(real32_T)B_Speed         //油泵反馈转速
			);

//		sFATFS.res_sd = f_open(&sFATFS.fnew, sFATFS.FileName , FA_WRITE | FA_OPEN_ALWAYS | FA_READ);
//		f_lseek(&sFATFS.fnew , ((FIL*)&sFATFS.fnew)->fsize);
			sFATFS.res_sd = f_write(&sFATFS.fnew , WriteBuf , strlen(WriteBuf) , &sFATFS.fnum);
			sdSaveCnt++;
//        if(sdSaveCnt * strlen(WriteBuf) >= 2048 )//&& DMA_GetITStatus(DMA2_Stream7 , DMA_FLAG_TCIF7) == SET)
			{
					f_sync(&sFATFS.fnew);
					sdSaveCnt = 0;
			}

//		f_close(&sFATFS.fnew);
			sdSaveMaxTime = sdSaveMaxTime < Timer.SDCard.Value ? Timer.SDCard.Value : sdSaveMaxTime;
			if(Timer.SDCard.Value > 250)	//changed by zy 20181210
			{
				sSDIO.FlagSaveAlarm = 1;
			}
			else
			{
				Timer.SDCard.Value = 0;
			}
			Timer.SDCard.Enble = 0;
	}

}

/*********************************************************************************
** 函数名称：u32tostr
** 编写者  ：张迎
** 参考资料：无
** 函数功能：u32转char*
** 输入参数：
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/

void u32tostr(unsigned long dat , unsigned char *str)
{
	char temp[20];
	unsigned char i = 0 , j = 0;
	while(dat)
	{
		temp[i++] = dat % 10 + 0x30;
		dat /= 10;
	}
	for(j = 0 ; j < i ; j++)
	{
		str[j] = temp[i - j - 1];
	}
	if(!i)
	{
		str[i++] = '0';
	}
	str[i] = 0;
}

/*********************************************************************************
** 函数名称：strtou32
** 编写者  ：张迎
** 参考资料：无
** 函数功能：char*转u32
** 输入参数：
** 输出参数：无
** 修改时间: 无
** 修改内容：无
** 修改人  ：无
** 备    注：无
*********************************************************************************/

unsigned long strtou32( char *str)
{
	unsigned long temp = 0;
	unsigned long fact = 1;
	unsigned char len = strlen(str);
	unsigned char i;
	for(i = len ; i > 0 ; i --)
	{
		temp += ((str[i - 1] - 0x30) * fact);
		fact *= 10;
	}
	return temp;
}

/*********************************************************************************
** 函数名称:GetSDFileList
** 编 写 者:zy
** 参考资料:无
** 函数功能:获取SD卡中文件最大序号
** 输入参数:文件路径 一般为："0:"
** 输出参数:SD卡中文件最大序号
** 修改时间:无
** 修改内容:无
** 修 改 人:无
** 备     注:无
*********************************************************************************/
u32 GetSDFileMAXIndex(char *path)
{
    FRESULT res;
    FILINFO fno;
    DIR dir;
    char *fn;
    char file_num[20] = {0};
    u32 FileMAXIndex = 0;
    u32 FileIndex = 0;

#if _USE_LFN
    static char lfn[_MAX_LFN * 2 + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif

    res = f_opendir(&dir , path);
    if(FR_OK == res)
    {
        for(;;)
        {
            res = f_readdir(&dir , &fno);
            if(FR_OK != res || fno.fname[0] == 0)
            {
 //               printf("FileMAXIndex : %d\r\n" , FileMAXIndex);
                break;
            }
#if _USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            if('.' == *fn)
            {
                continue;
            }
            if(6 < strlen(fn))
            {
                memset(file_num , 0 ,sizeof(file_num));
                strncpy(file_num , fn + 11 , 8);
                FileIndex = atoi(file_num);
                FileMAXIndex = FileMAXIndex > FileIndex ? FileMAXIndex : FileIndex;
//                printf("%s/%s  namelen : %d  nameindex : %d  file_size: %d\r\n" , path , fn , strlen(fn) , FileIndex , fno.fsize);
            }

        }
    }
return FileMAXIndex;

}

void PrintSDFileList(char *path)
{
        FRESULT res;
        FILINFO fno;
        DIR dir;
        char *fn;

#if _USE_LFN
        static char lfn[_MAX_LFN * 2 + 1];
        fno.lfname = lfn;
        fno.lfsize = sizeof(lfn);
#endif

        res = f_opendir(&dir , path);
        if(FR_OK == res)
        {
            for(;;)
            {
                res = f_readdir(&dir , &fno);
                if(FR_OK != res || fno.fname[0] == 0)
                {
                    break;
                }
#if _USE_LFN
                fn = *fno.lfname ? fno.lfname : fno.fname;
#else
                fn = fno.fname;
#endif
                if('.' == *fn)
                {
                    continue;
                }
                if(4 < strlen(fn))
                {
                    printf("%s/%s  namelen : %d   file_size: %d\r\n" , path , fn , strlen(fn)  , fno.fsize);
                }

            }
        }

}


