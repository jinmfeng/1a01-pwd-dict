#include "stdafx.h"
#include "factor.h"

#pragma warning(disable:4018)

int main(int argc, char* argv[])
{
    // 从sample.txt中读取因子
    Factor factor;
    memset(&factor, 0, sizeof(Factor));
    Factor *pFactor = FactorReadFromFile("sample.txt", &factor);
    if (pFactor == NULL) {
        printf("ERR: Read sample.txt failed!\n");
        return -1;
    }

    // 准备写入文件
    FILE *fout = fopen("pwd.txt", "wt");
    if (fout == NULL) {
        printf("ERR: Create pwd.txt failed!\n");
        FactorClear(pFactor);
        return -1;
    }

    // 最大因子组合数,默认为5;因为用户不太有可能使用组合了5个以上的因子构成密码,太难记了
    const unsigned int MAX_COMBO = 5;

    // 构造字典：从1个因子构成的密码开始,直到最多MAX_COMBO个因子构成的密码
    char buf[512]; // 分配一个足够大的缓冲区,不太会有人用超过500个字符的密码,这个差不多够用了
    unsigned int nFactorCount = FactorGetCount(pFactor);
    for (int i = 0; i < nFactorCount && i < MAX_COMBO; i++) {
        // 计算排列方案的总数
        unsigned int total = FactorPermuteCount(pFactor, i+1);
        for (int j = 0; j < total; j++) {
            // 每一种排列方式给一个编号j,把第j个方案的结果输出到buf中
            FactorPermute(pFactor, i + 1, j, buf, 512);
            // debug trace
            printf("(%d,%d)\t%s\n", i + 1, j, buf);
            // 写文件
            fwrite(buf, sizeof(char), strlen(buf), fout);
            fwrite("\r\n", sizeof(char), 2, fout);
        }
    }

    // 清理内存
    fclose(fout);
    FactorClear(pFactor);
    return 0;
}

