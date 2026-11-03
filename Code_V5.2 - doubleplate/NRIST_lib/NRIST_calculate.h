#ifndef __NRIST_CALCULATE_H
#define	__NRIST_CALCULATE_H

#include "stm32f4xx.h"

//extern float ADCregister[10][12];
//extern float ADCaverage[12];

float TwoDots_interpolation(float x0, float x1, float y0, float y1, float xx);
float OneDimensional_interpolation(const float* px, const float* py, float xx, int xlength);
float TwoDimensional_interpolation(const float *p, float xx, float yy, int xlength, int ylength);
float GetVolt(float advalue);
void BufferTransfer(__IO uint16_t buffer[], uint8_t lengthx, uint8_t lengthy);
float OneDimensional_filter(float FilterRegister[], uint8_t length);
void TwoDimensional_filter(__IO uint16_t FilterRegister[120], uint8_t lengthx, uint8_t lengthy, float average[]);
float ADC_convert(float value, float Sensor_min, float Sensor_max, float Real_min, float Real_max);
float ADC_Sample2RealValue(float sampledata, float Real_min, float Real_max, float Sample_min, float Sample_max);
u8 SumArray(u8* Array ,u8 Start,u8 Size);
float SumArray_float(float* Array ,u16 Start,u16 Size);
float abswp(float x);
u8 XORArray(u8* Array ,u8 Start,u8 Size);
unsigned short crc16(unsigned char *buf, unsigned int len);
u32 Sum_MaxAndMin(u32* Array , u8 length);
void QuickSort(float *arr,u8 left,u8 right);
u32 Diff_MaxAndMin(u32* Array , u8 length);




#endif /* __NRIST_CALCULATE_H */
