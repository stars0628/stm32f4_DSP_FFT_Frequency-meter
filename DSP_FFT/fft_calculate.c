#include "fft_calculate.h"
#include "math.h"

uint32_t FFT_Mag[NPT/2]={0};//��Ƶ����
uint16_t magout[NPT];//ģ�����Ҳ����������
uint16_t temp;//Ƶ�����ĳɷ�
uint32_t fre = 0;//����Ƶ�� kHz
uint64_t Freq;//����Ƶ��

//�޸Ķ�ʱ��Ԥ��Ƶϵ������װ��ֵ��Ӱ���Ⲩ��Ƶ�ʵķ�Χ�;��ȣ�1 1680�ɲ���200-20KHZ  1 65535�ɲ���1-600HZ
uint8_t pre = 1;//��ʱ��3Ԥ��Ƶ+1
uint16_t T = 1680;//��ʱ��3��װ��ֵ+1

extern int long fftin [NPT];//FFT����
extern int long fftout[NPT];//FFT���

void GetPowerMag(void)//FFT�任������Ƶ��
{
    float X,Y,Mag,magmax;//ʵ�����鲿����Ƶ�ʷ�ֵ������ֵ
    uint16_t i;
	
		//������cr4_fft_1024_stm32
		cr4_fft_1024_stm32(fftout, fftin, NPT);	//fft�任
	
    for(i=1; i<NPT/2; i++)
    {
			X = (fftout[i] << 16) >> 16;	//��16λ��ʵ��
			Y = (fftout[i] >> 16);			//��16λ���鲿
		
			Mag = sqrt(X * X + Y * Y); 		//����ģֵ
			FFT_Mag[i]=Mag;					//���뻺�棬�����������
			//��ȡ���Ƶ�ʷ��������ֵ
			if(Mag > magmax)
			{
				magmax = Mag;
				temp = i;
			}
		}
		fre=84000000/T/pre;//���²���Ƶ��   ʱ��Ƶ�ʣ���װ��ֵ��Ԥ��Ƶ  84000000Ϊ��ʱ��3����ʱ����APB1Ƶ��
		Freq=(uint64_t)(temp*(fre*1.0/NPT));	//FFT����ʵ��Ƶ��f=����i*(����Ƶ��F/�ܲ�������N)	
}
