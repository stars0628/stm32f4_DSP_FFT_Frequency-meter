# STM32 DSP FFT频率计(1024次采样)

## 界面预览

## 本仓库包含以下内容：

1. HAL工程
2. Keil工程


## 实现的功能
A0脚可以采集频率，在fft_calculate.c中修改定时器预分频系数和重装载值能影响检测波形频率的范围和精度，1 1680可测试200-20KHZ  1 65535可测试1-600HZ

## 移植须知
1. 使用了ADC1，使用了定时器3，使用了DMA采集ADC数据
2. 在Options for Target的C++的Define栏添加括号中内容（__FPU_PRESENT=1,__TARGET_FPU_VFP,ARM_MATH_CM4,__CC_ARM）
3. ARM_MATH_CM4应根据芯片内核进行修改，如f1系列芯片应改为ARM_MATH_CM3
4. 要根据错误注释掉stm32f405xx.h中#define __FPU_PRESENT的定义，因为其在Options for Target中定义了使用硬件FPU，其它芯片要看有没有FPU，无则删除
5. 要在Options for Target的Target的Code Generation中勾选Use MicroLIB，并在Float Point Hardware中选择Single Precision
6. 注意修改tim.c 定时器的预分频系数和重装载值
7. 在fft_calculate.h文件中修改所用的芯片

## 其它事项
1. 代码中有详细备注
2. HAL配置以HAL工程为准
3. 该样例采样次数为1024次，因为使用的官网下载的DSP库只支持256和1024FFT
