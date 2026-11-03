#include "NRISTF4_flash.h"

/*******************************************************************************
///////////////////////////////////////////////////////////////////////////////
// 函数名：	 STMFLASH_ReadWord
// 编写者：	 樊瑜
// 参考资料：无
// 功  能：	 读取指定地址半字
// 输入参数： 指定地址										  
// 输出参数： 对应数据 
// 修改时间：
// 修改内容：
// 修改人：
// 备  注：
///////////////////////////////////////////////////////////////////////////////
*******************************************************************************/
u32 STMFLASH_ReadWord(u32 faddr)
{
	return *(vu32*)faddr; 
}  

/*******************************************************************************
///////////////////////////////////////////////////////////////////////////////
// 函数名：	 STMFLASH_GetFlashSector
// 编写者：	 樊瑜
// 参考资料：无
// 功  能：	获取某个地址所在Flash对应的扇区
// 输入参数： 指定地址										  
// 输出参数： 对应数据 
// 修改时间：
// 修改内容：
// 修改人：
// 备  注：
///////////////////////////////////////////////////////////////////////////////
*******************************************************************************/
uint16_t STMFLASH_GetFlashSector(u32 addr)
{
	if(addr<ADDR_FLASH_SECTOR_1)
	{
		return FLASH_Sector_0;
	}
	else if(addr<ADDR_FLASH_SECTOR_2)
	{
		return FLASH_Sector_1;
	}
	else if(addr<ADDR_FLASH_SECTOR_3)
	{
		return FLASH_Sector_2;
	}
	else if(addr<ADDR_FLASH_SECTOR_4)
	{
		return FLASH_Sector_3;
	}
	else if(addr<ADDR_FLASH_SECTOR_5)
	{
		return FLASH_Sector_4;
	}
	else if(addr<ADDR_FLASH_SECTOR_6)
	{
		return FLASH_Sector_5;
	}
	else if(addr<ADDR_FLASH_SECTOR_7)
	{
		return FLASH_Sector_6;
	}
	else if(addr<ADDR_FLASH_SECTOR_8)
	{
		return FLASH_Sector_7;
	}
	else if(addr<ADDR_FLASH_SECTOR_9)
	{
		return FLASH_Sector_8;
	}
	else if(addr<ADDR_FLASH_SECTOR_10)
	{
		return FLASH_Sector_9;
	}
	else if(addr<ADDR_FLASH_SECTOR_11)
	{
		return FLASH_Sector_10; 
	}
	else
	{
		return FLASH_Sector_11;	
	}
}

/*******************************************************************************
///////////////////////////////////////////////////////////////////////////////
// 函数名：	 STMFLASH_Write
// 编写者：	 樊瑜
// 参考资料：无
// 功  能：	从指定地址写入指定长度
// 输入参数： WriteAddr          起始地址(地址必须是4的倍数)	
              pBuffer            数据指针
              NumToWrite         写入长度
// 输出参数： 无 
// 修改时间：
// 修改内容：
// 修改人：
// 备  注：
///////////////////////////////////////////////////////////////////////////////
*******************************************************************************/
void STMFLASH_Write(u32 WriteAddr,u8 *pBuffer,u16 NumToWrite)	
{ 
  FLASH_Status status = FLASH_COMPLETE;
  u32 addrx=0;
  u32 endaddr=0;	
  if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)
  {
	  return;
  }
  FLASH_Unlock();									//解锁
  FLASH_DataCacheCmd(DISABLE);//FLASH擦除期间，必须禁止数据缓存
 		
	addrx=WriteAddr;				//写入的起始地址
	endaddr=WriteAddr+NumToWrite*4;	//写入的结束地址
	if(addrx<0X1FFF0000)			//只有主存储区才需要执行擦除操作
	{
		while(addrx<endaddr)		
		{
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//
			{   
				status=FLASH_EraseSector(STMFLASH_GetFlashSector(addrx),VoltageRange_3);
				if(status!=FLASH_COMPLETE)
				{
					break;
				}					
			}
			else 
			{
				addrx+=4;
			}
		} 
	}
	if(status==FLASH_COMPLETE)
	{
		while(WriteAddr<endaddr)//写数据
		{
			if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE)//D′è?êy?Y
			{ 
				break;	//写入异常
			}
			WriteAddr+=4;
			pBuffer++;
		} 
	}
  FLASH_DataCacheCmd(ENABLE);	//FLASH擦除结束，开启数据缓存
  FLASH_Lock();
} 

/*******************************************************************************
///////////////////////////////////////////////////////////////////////////////
// 函数名：	 STMFLASH_Read
// 编写者：	 樊瑜
// 参考资料：无
// 功  能：	从指定地址写入指定长度
// 输入参数： ReadAddr          起始地址(地址必须是4的倍数)	
              pBuffer            数据指针
              NumToWrite         写入长度
// 输出参数： 无 
// 修改时间：
// 修改内容：
// 修改人：
// 备  注：
///////////////////////////////////////////////////////////////////////////////
*******************************************************************************/
void STMFLASH_Read(u32 ReadAddr,u8 *pBuffer,u16 NumToRead)   	
{
	u32 i;
	for(i=0;i<NumToRead;i++)
	{
//		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);
		pBuffer[i] = *(vu32*)ReadAddr;

		ReadAddr+=4;
	}
}
