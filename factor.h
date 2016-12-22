#ifndef _FACTOR_H
#define _FACTOR_H

// 定义一个用于保存因子的数组结构
typedef struct tagFactor
{
    // 因子的数目
    unsigned int count;
    // 因子
    char **pElement;
} Factor;

// 从指定的文件中读取因子
Factor* FactorReadFromFile(char *pszSamplePath, Factor *pFactor);

// 获取因子的数目
unsigned int FactorGetCount(Factor *pFactor);

// 从因子中,挑出nCombine个进行组合,共有几种方案
unsigned int FactorPermuteCount(Factor *pFactor, int nCombine);

// 排列组合,挑出nCombine个因子进行排列,把第sn种排列方式的结果输出到buf,bufLen指标buf的大小,返回已经填充的buf大小
int FactorPermute(Factor *pFactor, int nCombine, int sn, char *buf, int bufLen);

// 释放内存
void FactorClear(Factor *pFactor);

#endif // _FACTOR_H