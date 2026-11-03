/*******************************(C) By CuiLei ************************************
 * 文件名称: NRIST_calculate.c
 * 适用模块: STM32F105VCT7
 * 描    述: 60所专用常用计算函数
 * 实验平台: 涡喷发动机ECU平台
 * 库版本  : ST3.5.0
 *
 * 文件版本: V1.0.0.0001
 * 作    者: 崔雷
 * 作者部门: 航空电气研究室
 * 完成日期: 2015年5月28日
 *
 * 取代版本: 无
 * 原作者  : 无
 * 完成日期: 无
**********************************************************************************/
#include "NRIST_calculate.h"
#include "stdlib.h"

float ADCregister[10][12]={0};                 //定义ADC寄存器数组为0
float ADCaverage[12] = {0};                    //ADC滤波后寄存器

/*********************************************************************************
** 函数名称: TwoDots_interpolation
** 编写者  : 崔雷
** 参考资料: 无
** 函数功能: 两点线性插值函数
   //-----------------
   //|   x0  |   x1  |
   //-----------------
   //|   y0  |   y1  |
   //-----------------
** 输入参数: 两点坐标（x0,y0）和（x1,y1）,要求点的横坐标xx
** 输出参数: 要求点的纵坐标yy
** 修改时间: 无
** 修改内容: 无
** 修改人  : 无
** 备    注: 无
*********************************************************************************/
float TwoDots_interpolation(float x0, float x1, float y0, float y1, float xx)
{
	float temp = (y1-y0) * (xx-x0) / (x1-x0) + y0;
	return temp;
}

/*********************************************************************************
** 函数名称: OneDimensional_interpolation
** 编写者  : 崔雷
** 参考资料: 无
** 函数功能: 一维线性插值函数
   //----------------------------------------
   //|  *   |   x1  |   x2  |   x3  |   x4  |
   //----------------------------------------
   //|  *   |   y1  |   y2  |   y3  |   y4  |
   //----------------------------------------
   //px:指向第一行的数组
   //py:指向第二行的数组
   //xx: 待插值的横坐标
   //xlength:横坐标的长度，从1开始
** 输入参数: px,py,xx,xlength
** 输出参数: 与xx对应的纵坐标
** 修改时间: 无
** 修改内容: 无
** 修改人  : 无
** 备    注: 无
*********************************************************************************/
float OneDimensional_interpolation(const float* px, const float* py, float xx, int xlength)
{
	int i=1;
	float Xmark;
	float temp;

	while( i <= xlength )
	{
		Xmark = *(px+i);
		if( Xmark == xx )
		{
			temp = *(py+i);
			break;
		}
		else if( Xmark > xx )
		{
			temp = TwoDots_interpolation( *(px+i-1), *(px+i), *(py+i-1), *(py+i), xx);
			break;
		}
		else
		{
			i++;
		}
	}

	return temp;
}

/*********************************************************************************
** 函数名称: TwoDimensional_interpolation
** 编写者  : 崔雷
** 参考资料: 无
** 函数功能: 二维线性插值函数
   //-------------------------------------------
   //|  *  |   x1   |   x2   |   x3   |   x4   |
   //-------------------------------------------
   //|  y1 |   z11  |   z12  |   z13  |   z14  |
   //-------------------------------------------
   //|  y2 |   z21  |   z22  |   z23  |   z24  |
   //-------------------------------------------
   //p:指向二维数组的第一个值
   //xx: 待插值的横坐标
   //yy: 待插值的纵坐标
   //xlength: 横坐标的长度，从1开始
   //ylength: 纵坐标的长度，从1开始
** 输入参数: p,xx,yy,xlength,ylength
** 输出参数: 与xx，yy对应的zz值
** 修改时间: 无
** 修改内容: 无
** 修改人  : 无
** 备    注: 无
*********************************************************************************/
float TwoDimensional_interpolation(const float *p, float xx, float yy, int xlength, int ylength)
{
	int j=1;
	float Ymark;
	float tempY1,tempY2;
	float tempZ;

	while( j <= ylength )
	{
		Ymark = *(p+(xlength+1)*j);
		if( Ymark == yy )
		{
			tempZ = OneDimensional_interpolation( p+1, p+1 + (xlength+1)*j, xx, xlength);
			break;
		}
		else if( Ymark > yy )
		{
			tempY1 = OneDimensional_interpolation( p+1, p+1 + (xlength+1)*(j-1), xx, xlength);
			tempY2 = OneDimensional_interpolation( p+1, p+1 + (xlength+1)*j, xx, xlength);
			tempZ = TwoDots_interpolation( *(p+(xlength+1)*(j-1)), *(p+(xlength+1)*j), tempY1, tempY2, yy);
			break;
		}
		else
		{
			j++;
		}
	}

	return tempZ;
}

/*********************************************************************************
** 函数名称: GetVolt
** 编写者  : 崔雷
** 参考资料: 无
** 函数功能: 获取ADC的值，将二进制换算为十进制
** 输入参数: advalue    ----    要转换的二进制值
** 输出参数: 转换后的十进制值
** 修改时间: 无
** 修改内容: 无
** 修改人  : 无
** 备    注: 无
*********************************************************************************/
float GetVolt(float advalue)
{
    return (float)(advalue/4096*3);               //读取转换的AD值     20150827黄若修改 将3.3改为3
}

/*********************************************************************************
** 函数名称: BufferTransfer
** 编写者  : 崔雷
** 参考资料: 无
** 函数功能: 获取ADC转换后DMA的Buffer中的值
** 输入参数: buffer    ----    要转移的Buffer地址
             lengthx   ----    转换的通道采集次数
			 lengthy   ----    采集的通道数
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修改人  : 无
** 备    注: 无
*********************************************************************************/
void BufferTransfer(__IO uint16_t buffer[], uint8_t lengthx, uint8_t lengthy)
{
    int i;
	int j;

	for(i=0; i<lengthx; i++)
    {
        for(j=0; j<lengthy; j++)
        {
            ADCregister[i][j] =  (float)buffer[lengthy * i + j];
        }
    }
}

/*********************************************************************************
** 函数名称: OneDimensional_filter
** 编写者  : 崔雷
** 参考资料: 无
** 函数功能: 一维数组滤波函数
** 输入参数: FilterRegister  ----    要滤波的数组register
             length          ----    数组长度
** 输出参数: 滤波后的值
** 修改时间: 无
** 修改内容: 无
** 修改人  : 无
** 备    注: 无
*********************************************************************************/
float OneDimensional_filter(float FilterRegister[], uint8_t length)
{
    float sum = 0;                                     //中间值的和
    int i_start;                                       //起始计数
    int i_end;                                         //终止计数
	int i;                                             //冒泡排序法用i
	int j;											   //冒泡排序法用j
    float temp;                                          //中间值
	int count;
	float average = 0;                                 //返回值
	u8 OneDimensional_i;
	float *Filter;
	Filter =(float *)malloc(length*sizeof(float));
	if(length < 3)
	{
		for(i=0;i<length;i++)
		{
			sum += FilterRegister[i];
		}
		if(length == 0)				   //如果length为0 则置为1 防止计算平均时出错
		{
			length = 1;
		}
		average = sum/length;
	}
	else
	{
		for(OneDimensional_i=0;OneDimensional_i<length;OneDimensional_i++)
		{
			Filter[OneDimensional_i]=FilterRegister[OneDimensional_i];
		}

	    if(length % 2)									   //如果数组长度为偶数，取中间4个
		{
		    i_start = length / 2 - 2;
			i_end = i_start + 4;
		}
		else											   //如果数组长度为奇数，取中间3个
		{
		    i_start = length / 2 - 1;
			i_end = i_start + 3;
		}

	    for(i=0;i<length;i++)							   //冒泡排序法,从小到大
	    {
	        for(j=0;j<length-i-1;j++)
	        {
	            if(Filter[j] > Filter[j+1])
	            {
	                temp = Filter[j];
	                Filter[j] = Filter[j+1];
	                Filter[j+1] = temp;
	            }
	        }
	    }

		for(count=i_start;count<=i_end;count++)
	    {
	        sum += Filter[count];
	    }
	    average = (float)sum / (i_end - i_start + 1);
		free(Filter);
	}
    return average;
}

/*********************************************************************************
** 函数名称: TwoDimensional_filter
** 编写者  : 崔雷
** 参考资料: 无
** 函数功能: 二维数组滤波函数
** 输入参数: FilterRegister  ----    要滤波的数组register
             lengthx         ----    转换的通道采集次数
			 lengthy         ----    采集的通道数
			 average         ----    滤波后的数组
** 输出参数: 无
** 修改时间: 无
** 修改内容: 无
** 修改人  : 无
** 备    注: 无
*********************************************************************************/
void TwoDimensional_filter(__IO uint16_t FilterRegister[120], uint8_t lengthx, uint8_t lengthy, float average[])
{
    int i;
	int j;
	int m;
	int n;
	int k;
	float register_original[16][16]={0};
	float register_trans[16][16]={0};

	for(i=0; i<lengthx; i++)
    {
        for(j=0; j<lengthy; j++)
        {
            register_original[i][j] =  FilterRegister[lengthy * i + j];
        }
    }

	for(m=0; m<lengthx; m++)												 //数组转置
    {
        for(n=0; n<lengthy; n++)
        {
            register_trans[n][m] =  register_original[m][n];
        }
    }

    for(k=0;k<lengthy;k++)
    {
        average[k] = OneDimensional_filter(register_trans[k], lengthx);
    }
}

/*********************************************************************************
** 函数名称: ADC_convert
** 编写者  : 崔雷
** 参考资料: 无
** 函数功能: ADC数值解算函数
** 输入参数: value        ----    要转换的测量值
             Sensor_min   ----    传感器输出的最小值
			 Sensor_max   ----    传感器输出的最大值
			 Real_min     ----    实际测量最小值
			 Real_max     ----    实际测量最大值
** 输出参数: 转换后的值
** 修改时间: 无
** 修改内容: 无
** 修改人  : 无
** 备    注: 无
*********************************************************************************/
float ADC_convert(float value, float Sensor_min, float Sensor_max, float Real_min, float Real_max)
{
    float ADC_ConvertedValue = 0;                            //转换后的十进制值
	float ADC_last = 0;                                      //解算后的值

	ADC_ConvertedValue = GetVolt(value);

	if(ADC_ConvertedValue >= Sensor_max)					 //上越界处理
    {
        ADC_ConvertedValue = Sensor_max;
    }

    if(ADC_ConvertedValue <= Sensor_min)					 //下越界处理
    {
        ADC_ConvertedValue = Sensor_min;
    }

	ADC_last = ((Real_max - Real_min) * (ADC_ConvertedValue - Sensor_min) / (Sensor_max - Sensor_min) + Real_min);    //模拟量解算

	return ADC_last;
}

/*********************************************************************************
** 函数名称: ADC_Sample2RealValue
** 编写者  : 张迎
** 参考资料: 无
** 函数功能: ADC数值解算函数
** 输入参数: sampledata        ----    要转换的采样值
             Real_min   ----    传感器输出的最小值
			 Real_max   ----    传感器输出的最大值
			 Sample_min     ----    采样最小值
			 Sample_max     ----    采样最大值
** 输出参数: 转换后的值
** 修改时间: 无
** 修改内容: 无
** 修改人  : 无
** 备    注: 无
*********************************************************************************/
float ADC_Sample2RealValue(float sampledata, float Real_min, float Real_max, float Sample_min, float Sample_max)
{
    float Real_t = 0.0f;
    float sample_t = sampledata > Sample_max ? Sample_max : sampledata;
    sample_t = sampledata < Sample_min ? Sample_min : sampledata;
    Real_t = (Real_max - Real_min) * (sample_t - Sample_min) / (Sample_max - Sample_min) + Real_min;
    return Real_t;
}

/*******************************************************************************
///////////////////////////////////////////////////////////////////////////////
// 函数名: 	 SumArray
// 编写者: 	 黄若
// 参考资料: 无
// 功  能: 	 和校验
// 输入参数: Array    ----     输入数组
			 Start    ----     偏移量（0表示从第一个数开始计算）
			 Size     ----     数组大小

// 输出参数: 无
// 修改时间:
// 修改内容:
// 修改人:
// 备  注:
///////////////////////////////////////////////////////////////////////////////
*******************************************************************************/
u8 SumArray(u8* Array ,u8 Start,u8 Size)
{
	u8 Sum=0;
	u8 SumCount;
	for (SumCount=Start;SumCount<Size;SumCount++)
	{
		Sum += Array[SumCount];
	}
	return Sum;
}

/*******************************************************************************
///////////////////////////////////////////////////////////////////////////////
// 函数名: 	 SumArray_float
// 编写者: 	 黄若
// 参考资料: 无
// 功  能: 	 和校验
// 输入参数: Array    ----     输入数组
			 Start    ----     偏移量（0表示从第一个数开始计算）
			 Size     ----     数组大小

// 输出参数: 无
// 修改时间:
// 修改内容:
// 修改人:
// 备  注:
///////////////////////////////////////////////////////////////////////////////
*******************************************************************************/
float SumArray_float(float* Array ,u16 Start,u16 Size)
{
	float Sum=0;
	u16 SumCount;
	for (SumCount=Start;SumCount<Size;SumCount++)
	{
		Sum += Array[SumCount];
	}
	return Sum;
}
// CRC16油泵校验
const unsigned short crc16_tab[] = { 0x0000, 0x1021, 0x2042, 0x3063, 0x4084,
		0x50a5, 0x60c6, 0x70e7, 0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad,
		0xe1ce, 0xf1ef, 0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7,
		0x62d6, 0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
		0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 0xa56a,
		0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 0x3653, 0x2672,
		0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 0xb75b, 0xa77a, 0x9719,
		0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 0x48c4, 0x58e5, 0x6886, 0x78a7,
		0x0840, 0x1861, 0x2802, 0x3823, 0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948,
		0x9969, 0xa90a, 0xb92b, 0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50,
		0x3a33, 0x2a12, 0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b,
		0xab1a, 0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
		0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 0x7e97,
		0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 0xff9f, 0xefbe,
		0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 0x9188, 0x81a9, 0xb1ca,
		0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 0x1080, 0x00a1, 0x30c2, 0x20e3,
		0x5004, 0x4025, 0x7046, 0x6067, 0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d,
		0xd31c, 0xe37f, 0xf35e, 0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214,
		0x6277, 0x7256, 0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c,
		0xc50d, 0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
		0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 0x26d3,
		0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 0xd94c, 0xc96d,
		0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 0x5844, 0x4865, 0x7806,
		0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e,
		0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1,
		0x1ad0, 0x2ab3, 0x3a92, 0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b,
		0x9de8, 0x8dc9, 0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0,
		0x0cc1, 0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
		0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 };

unsigned short crc16(unsigned char *buf, unsigned int len) 
{
	unsigned int i;
	unsigned short cksum = 0;
	for (i = 0; i < len; i++) 
	{
		cksum = crc16_tab[(((cksum >> 8) ^ *buf++) & 0xFF)] ^ (cksum << 8);
	}
	return cksum;
}

/*******************************************************************************
///////////////////////////////////////////////////////////////////////////////
// 函数名: 	 SumArray
// 编写者: 	 黄若
// 参考资料: 无
// 功  能: 	 异或校验
// 输入参数: Array    ----     输入数组
			 Start    ----     偏移量（0表示从第一个数开始计算）
			 Size     ----     数组大小

// 输出参数: 无
// 修改时间:
// 修改内容:
// 修改人:
// 备  注:
///////////////////////////////////////////////////////////////////////////////
*******************************************************************************/
u8 XORArray(u8* Array ,u8 Start,u8 Size)
{
	u8 XOR = 0;
	u8 XORCount;
	for (XORCount=Start;XORCount<Size;XORCount++)
	{
		XOR ^= Array[XORCount];
	}
	return XOR;
}

/*******************************************************************************
///////////////////////////////////////////////////////////////////////////////
// 函数名: 	 Sum_MaxAndMin
// 编写者: 	 黄若
// 参考资料: 无
// 功  能: 	 计算最大值和最小值之和
// 输入参数: Array    ----     输入数组
			 length   ----     数组大小

// 输出参数: 无
// 修改时间:
// 修改内容:
// 修改人:
// 备  注:
///////////////////////////////////////////////////////////////////////////////
*******************************************************************************/

u32 Sum_MaxAndMin(u32* Array , u8 length)
{
	u8 i;
	u32 max = Array[0];
	u32 min = Array[0];
	for(i=0;i<length;i++)
	{
		if(max < Array[i])
		{
			max = Array[i];
		}
		if(min >Array[i])
		{
			min = Array[i];
		}
	}
	return (max + min);
}
/*******************************************************************************
///////////////////////////////////////////////////////////////////////////////
// 函数名: 	 Diff_MaxAndMin
// 编写者: 	 黄若
// 参考资料: 无
// 功  能: 	 计算最大值和最小值之差
// 输入参数: Array    ----     输入数组
			 length   ----     数组大小

// 输出参数: 无
// 修改时间:
// 修改内容:
// 修改人:
// 备  注:
///////////////////////////////////////////////////////////////////////////////
*******************************************************************************/

u32 Diff_MaxAndMin(u32* Array , u8 length)
{
	u8 i;
	u32 max = Array[0];
	u32 min = Array[0];
	for(i=0;i<length;i++)
	{
		if(max < Array[i])
		{
			max = Array[i];
		}
		if(min >Array[i])
		{
			min = Array[i];
		}
	}
	return (max - min);
}

/*******************************************************************************
///////////////////////////////////////////////////////////////////////////////
// 函数名: 	 abswp
// 编写者: 	 黄若
// 参考资料: 无
// 功  能: 	 计算绝对值
// 输入参数:

// 输出参数: 无
// 修改时间:
// 修改内容:
// 修改人:
// 备  注:
///////////////////////////////////////////////////////////////////////////////
*******************************************************************************/
float abswp(float x)
{
	if(x<0)
	{
		x = x * (-1);
	}
	return x;
}
///*******************************************************************************
/////////////////////////////////////////////////////////////////////////////////
//// 函数名: 	 QuickSort
//// 编写者: 	 黄若
//// 参考资料: 无
//// 功  能: 	 计算绝对值
//// 输入参数:

//// 输出参数: 无
//// 修改时间:
//// 修改内容:
//// 修改人:
//// 备  注:
/////////////////////////////////////////////////////////////////////////////////
//*******************************************************************************/
//void QuickSort(float *arr,u8 left,u8 right)
//{

//	u8 i = left;
//	u8 j = right;
//	float key = arr[left];
//	if(left >= right)
//	{
//		return;
//	}
//	while(i<j)
//	{
//		while((i<j)&&(key<=arr[j]))
//		{
//			j--;
//		}
//		arr[i] = arr[j];
//		while((i<j)&&(key>=arr[i]))
//		{
//			i++;
//		}
//		arr[j]=arr[i];
//
//	}
//	arr[i] = key;
//	QuickSort(arr,left,i-1);
//	QuickSort(arr,i+1,right);
//
//
//}

