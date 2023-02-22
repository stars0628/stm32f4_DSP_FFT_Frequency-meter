#include "fft_calculate.h"
#include "math.h"

uint32_t FFT_Mag[NPT/2]={0};//幅频特性
uint16_t magout[NPT];//模拟正弦波输出缓存区
uint16_t temp;//频率最大的成分
uint32_t fre = 0;//采样频率 kHz
uint64_t Freq;//波形频率

//修改定时器预分频系数和重装载值能影响检测波形频率的范围和精度，1 1680可测试200-20KHZ  1 65535可测试1-600HZ
uint8_t pre = 1;//定时器3预分频+1
uint16_t T = 1680;//定时器3重装载值+1

extern int long fftin [NPT];//FFT输入
extern int long fftout[NPT];//FFT输出

void GetPowerMag(void)//FFT变换，计算频率
{
    float X,Y,Mag,magmax;//实部，虚部，各频率幅值，最大幅值
    uint16_t i;
	
		//调用自cr4_fft_1024_stm32
		cr4_fft_1024_stm32(fftout, fftin, NPT);	//fft变换
	
    for(i=1; i<NPT/2; i++)
    {
			X = (fftout[i] << 16) >> 16;	//低16位存实部
			Y = (fftout[i] >> 16);			//高16位存虚部
		
			Mag = sqrt(X * X + Y * Y); 		//计算模值
			FFT_Mag[i]=Mag;					//存入缓存，用于输出查验
			//获取最大频率分量及其幅值
			if(Mag > magmax)
			{
				magmax = Mag;
				temp = i;
			}
		}
		fre=84000000/T/pre;//更新采样频率   时钟频率，重装载值，预分频  84000000为定时器3所在时钟线APB1频率
		Freq=(uint64_t)(temp*(fre*1.0/NPT));	//FFT所得实际频率f=点数i*(采样频率F/总采样点数N)	
}
