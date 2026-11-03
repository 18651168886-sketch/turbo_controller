/*********************************************************************************
 * 文件名称: fram.c
 * 适用模块: STM32F407VGT7
 * 描    述: 模拟量采集集成库函数
 * 实验平台: 发烟机ECU平台
 * 库版本  : V1.4.0
 *
 * 文件版本: V1.0.0.0001
 * 作    者: 甘辉
 * 作者部门: 发动机研发三部
 * 完成日期: 2019年6月11日
 *
 * 取代版本: 无
 * 原作者  : 无
 * 完成日期: 无
**********************************************************************************/
#include"fram.h"

static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;

static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);
/*********************************************************************************
** 函数名称: FRAM_Config
** 编 写 者: 甘辉
** 参考资料: 无
** 函数功能: SPI及端口配置
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
void FRAM_Config(void)
{
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 使能 FLASH_SPI 及GPIO 时钟 */
    RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    // 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

    //设置引脚复用
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);

    /*!< 配置 SPI_FLASH_SPI 引脚: SCK */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*!< 配置 SPI_FLASH_SPI 引脚: MISO */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*!< 配置 SPI_FLASH_SPI 引脚: MOSI */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*!< 配置 SPI_FLASH_SPI 引脚: CS */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* 停止信号 FLASH: CS引脚高电平*/
    SPI_FRAM_CS_HIGH();

    /* FLASH_SPI 模式配置 */
    // FLASH芯片 支持SPI模式0及模式3，据此设置CPOL CPHA
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);

    /* 使能 FLASH_SPI  */
    SPI_Cmd(SPI2, ENABLE);
}
/*********************************************************************************
** 函数名称: SPI_FRAM_SendByte
** 编 写 者: 樊瑜
** 参考资料: 无
** 函数功能: SPI数据发送
** 输入参数: byte
** 输出参数: 寄存器中缓存数据
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
u8 SPI_FRAM_SendByte(u8 byte)
{
    SPITimeout = SPIT_FLAG_TIMEOUT;

    /* 等待发送缓冲区为空，TXE事件 */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
    {
        if((SPITimeout--) == 0)
            return SPI_TIMEOUT_UserCallback(0);
    }

    /* 写入数据寄存器，把要写入的数据写入发送缓冲区 */
    SPI_I2S_SendData(SPI2, byte);

    SPITimeout = SPIT_FLAG_TIMEOUT;

    /* 等待接收缓冲区非空，RXNE事件 */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if((SPITimeout--) == 0)
            return SPI_TIMEOUT_UserCallback(1);
    }

    /* 读取数据寄存器，获取接收缓冲区数据 */
    return SPI_I2S_ReceiveData(SPI2);
}
/*********************************************************************************
** 函数名称: SPI_FRAM_ReadByte
** 编 写 者: 樊瑜
** 参考资料: 无
** 函数功能: SPI数据读取
** 输入参数: 无
** 输出参数: 寄存器中缓存数据
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
u8 SPI_FRAM_ReadByte(void)
{
    return (SPI_FRAM_SendByte(Dummy_Byte));
}
/*********************************************************************************
** 函数名称: FRAM_WREN
** 编 写 者:樊瑜
** 参考资料: 无
** 函数功能: 写使能
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
void FRAM_WREN(void)
{
    SPI_FRAM_CS_HIGH();
    SPI_FRAM_CS_LOW();
    SPI_FRAM_SendByte(0x06);
    SPI_FRAM_CS_HIGH();
}
/*********************************************************************************
** 函数名称: FRAM_WRDI
** 编 写 者: 樊瑜
** 参考资料: 无
** 函数功能: 写失能
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
void FRAM_WRDI(void)
{
    SPI_FRAM_CS_HIGH();
    SPI_FRAM_CS_LOW();
    SPI_FRAM_SendByte(0x04);
    SPI_FRAM_CS_HIGH();
}
/*********************************************************************************
** 函数名称: FRAM_Write
** 编 写 者: 樊瑜
** 参考资料: 无
** 函数功能: 写数据
** 输入参数: Addr  :    0~0x01FF
             Data  :    待写数据
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
void FRAM_Write(u16 Addr,u8 Data)
{
    SPI_FRAM_CS_LOW();
    SPI_FRAM_SendByte(0x02);
    SPI_FRAM_SendByte((Addr&0xFF00)>>8);
    SPI_FRAM_SendByte(Addr&0xFF);
    SPI_FRAM_SendByte(Data);
    SPI_FRAM_CS_HIGH();
}
/*********************************************************************************
** 函数名称: FRAM_Write
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 写数据
** 输入参数: Addr  :    0~0x01FF
             Data  :    待写数据
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
void FM25_Write(u16 Addr,u8* Data , u16 nbr2Write)
{
    SPI_FRAM_CS_LOW();
    SPI_FRAM_SendByte(0x02);
    SPI_FRAM_SendByte((Addr&0xFF00)>>8);
    SPI_FRAM_SendByte(Addr&0xFF);
    for(u16 i = 0; i < nbr2Write ; i++)
    {
        SPI_FRAM_SendByte(Data[i]);
    }
    SPI_FRAM_CS_HIGH();
}

/*********************************************************************************
** 函数名称: FRAM_Read
** 编 写 者: 樊瑜
** 参考资料: 无
** 函数功能: 读取数据
** 输入参数: Addr  :    0~0x01FF
** 输出参数: Data  :    数据
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
u8 FRAM_Read(u16 Addr)
{
    u8 Data;
    SPI_FRAM_CS_LOW();
    SPI_FRAM_SendByte(0x03);
    SPI_FRAM_SendByte((Addr&0xFF00)>>8);
    SPI_FRAM_SendByte(Addr&0xFF);
    Data = SPI_FRAM_SendByte(Dummy_Byte);
    SPI_FRAM_CS_HIGH();
    return Data;
}
/*********************************************************************************
** 函数名称: FM25_Read
** 编 写 者: 张迎
** 参考资料: 无
** 函数功能: 读取数据
** 输入参数: Addr  :    0~0x01FF
** 输出参数: Data  :    数据
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
void FM25_Read(u8* Data , u16 Addr , u16 nbr2Read)
{
    SPI_FRAM_CS_LOW();
    SPI_FRAM_SendByte(0x03);
    SPI_FRAM_SendByte((Addr&0xFF00)>>8);
    SPI_FRAM_SendByte(Addr&0xFF);
    for(u16 i = 0; i < nbr2Read ; i++)
    {
        Data[i] = SPI_FRAM_SendByte(Dummy_Byte);
    }
    SPI_FRAM_CS_HIGH();
    return;
}

/*********************************************************************************
** 函数名称: SPI_TIMEOUT_UserCallback
** 编 写 者:樊瑜
** 参考资料: 无
** 函数功能: 等待超时回调函数
** 输入参数: 无
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修 改 人: 无
** 备    注: 无
*********************************************************************************/
static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
    /* 等待超时后的处理,输出错误信息 */
    printf("SPI 等待超时!errorCode = %d",errorCode);
    return 0;
}

