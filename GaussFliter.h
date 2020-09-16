//高斯，中值，均值，双边

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

const float PI = 3.14159;

/*********************************************
 * 函数名GetGaussTmp（r,sigma）
 * 功能:生成一维高斯滤波模板
 * r:  ?应该是中间数的序号  r = 3,size = 5
 * y:  需要进行高斯滤波的序列
 * 
 **********************************************/
static vector<float> GetGaussTmp(const int r, const float sigma)
{   
    vector<float> GaussTmp(2*r - 1,0);
    for(int i = 0; i < 2*r - 1; i++)
    {
       GaussTmp[i] = exp(-(i-r+1)*(i-r+1)/(2*sigma*sigma))/(sigma*sqrt(2*PI));
    }
    return GaussTmp;
}

void GaussianFilter(const int r, const float sigma, vector<vector<float>>& signal)
{   
    vector<vector<float>> signal_copy = signal;
    vector<float>GaussTmp = GetGaussTmp(r, sigma);

    for(int i = r - 1; i < signal_copy[0].size()-r+1; i++)
    {
        float sum = 0;
        for(int j = 0; j < 2*r-1; j++)
        { 
            sum += signal_copy[1][i-r+j+1] * GaussTmp[j];  //这里坐标曾经有问题
        }
        signal[1][i] = sum;
    }
}

static bool compare(int a, int b)
{
    return a < b;
}

/********************************
* 函数名:MidvalFilter （）
* 作用：对输入信号进行中值滤波
* r: 窗口大小，应该为大于等于3的奇数
* signal 输入信号。signal[0]为x的集合，signal[1]为y的集合
* 无返回值，直接修改原信号
* 不补0，不改变边缘的数字
 ********************************/
void MidvalFilter(const int r, vector<vector<float>>& signal)
{
    if (r < 3 || !(r % 2))
    {
        printf("输入维度参数错误");
        return;
    }

    if (signal[1].size() == 1)
    {
        return;
    }

    vector<vector<float>>signal_copy = signal;
    for (int i = 0; i < signal_copy[1].size() - r + 1; i++)//窗口从i=0开始滑动
    {
        vector<float>buf(r,0);
        for (int j = 0; j < r; j++)
        {
            buf[j] = signal_copy[1][i+j];
        }
        sort(buf.begin(), buf.end(), compare);
        signal[1][i + (r - 1) / 2] = buf[(r - 1) / 2];
    }
}

/***********************************************************************
* 名字:均值滤波函数
* 作用:对输入信号进行均值滤波
* r: 窗口大小，应该为大于等于3的奇数
* signal 输入信号。signal[0]为x的集合，signal[1]为y的集合
* 无返回值，直接修改原信号
* 不补0，不改变边缘的数字
*************************************************************************/
void AverageFilter(const int r, vector<vector<float>>& signal)
{
    if (r < 3 || !(r % 2))
    {
        printf("输入维度参数错误");
        return;
    }

    if (signal[1].size() == 1)
    {
        return;
    }

    vector<vector<float>>signal_copy = signal;
    //int sum = 0;这里声明错了调试了半天
    for (int i = 0; i < signal_copy[1].size() - r + 1; i++)//i为窗口的起点
    {
        float sum = 0;
        for (int j = 0; j < r; j++)
        {
            sum += signal_copy[1][i + j];
        }
        signal[1][i + (r - 1) / 2] = sum / r;
    }
}