#include "stdafx.h"
#include "factor.h"

#pragma warning(disable:4018 4244 4267)

Factor* FactorReadFromFile(char *pszSamplePath, Factor *pFactor)
{
    // 先固定写成5个因子,以后改成从文件中读取
    pFactor->count = 5;
    pFactor->pElement = malloc(sizeof(char*)*pFactor->count);

    pFactor->pElement[0] = "xidian";
    pFactor->pElement[1] = "2016";
    pFactor->pElement[2] = "12";
    pFactor->pElement[3] = "hello";
    pFactor->pElement[4] = "github";

    return pFactor;
}

unsigned int FactorGetCount(Factor *pFactor)
{
    return pFactor->count;
}

unsigned int FactorPermuteCount(Factor *pFactor, int nCombine)
{
    // 从n个因子中,挑出t个进行排列,共有n^t种方案
    return pow(pFactor->count, nCombine);
}

int FactorPermute(Factor *pFactor, int nCombine, int sn, char *buf, int bufLen)
{
    // 清空缓冲区
    memset(buf, 0, bufLen);

    // 挑出nCombine个因子进行排列,输出第sn个的排列方案
    // 先随便返回点什么,以后补充
    sprintf(buf, "xidian");

    return strlen("xidian") + 1;
}

void FactorClear(Factor *pFactor)
{
    pFactor->count = 0;
    free(pFactor->pElement);
}