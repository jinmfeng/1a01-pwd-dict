#include "stdafx.h"
#include "factor.h"

#pragma warning(disable:4018 4244 4267)

Factor* FactorReadFromFile(char *pszSamplePath, Factor *pFactor)
{
    FILE *pSample = fopen(pszSamplePath, "rt");
    if (pSample == NULL) {
        printf("ERR: Cannot open file %s\n", pszSamplePath);
        return NULL;
    }

    // 获取文件尺寸
    fseek(pSample, 0, SEEK_END);
    int size = ftell(pSample) + 1;

    // 读取内容
    char *buf = malloc(size);
    memset(buf, 0, size);

    fseek(pSample, 0, SEEK_SET);
    int read = fread(buf, sizeof(char), size, pSample);

    // 计数换行符的个数
    int count = 0;
    char *pNext = strchr(buf, '\n');
    while (pNext) {
        count++;
        pNext = strchr(pNext+1, '\n');
    }

    // 为因子分配空间. 如果有n个换行符,那么至多可能有n+1个因子,因为末尾可能有也可能没有换行符
    pFactor->pElement = malloc(sizeof(char*)*(count+1));
    memset(pFactor->pElement, 0, sizeof(char*)*(count + 1)); // 为分配的空间初始化为全0是一个好习惯
    pFactor->count = 0;

    char *pElement = strtok(buf, "\n");
    while (pElement) {
        pFactor->pElement[pFactor->count] = pElement;
        pFactor->count++;
        pElement = strtok(NULL, "\n");
    }

    // debug trace
    printf("INFO: read %d factors:\n", pFactor->count);
    for (int i = 0; i < pFactor->count; i++) {
        printf("%s", pFactor->pElement[i]);
        if (i % 8 == 7) printf("\n");
        else printf("\t");
    }
    printf("\n");

    fclose(pSample);

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
    int *permute = malloc(sizeof(int)*nCombine);
    memset(permute, 0, sizeof(int)*nCombine);

    // 第n个组合方案的计算公式
    for (int i = 0; i < nCombine; i++) {
        permute[i] = (sn / (unsigned int)pow(pFactor->count, nCombine-i-1)) % (pFactor->count);
    }

    // 计算缓冲区是否足够
    int totalLen = 0;
    for (int i = 0; i < nCombine; i++) {
        totalLen += strlen(pFactor->pElement[permute[i]]);
    }
    if (totalLen + 1 > bufLen) {
        printf("ERR: buffer is too small, need %d bytes", totalLen + 1);
        return 0;
    }

    // 写缓冲区
    for (int i = 0; i < nCombine; i++) {
        strcat(buf, pFactor->pElement[permute[i]]);
    }

    return strlen(buf) + 1;
}

void FactorClear(Factor *pFactor)
{
    pFactor->count = 0;
    free(pFactor->pElement);
}