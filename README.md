# 口令字典
口令字典是一种暴力攻击手段,通常人们为了密码记忆方便,有相当高的概率
会采用一些单词或数字的组合形式.密码字典通过排列组合基本的构成单元
构成密码字典.

## 程序关键数学逻辑思想
+ 初始从一个配置文件中读取一系列的口令因子(factor),比如xidian 2016 12 hello github
+ 然后,按所有可能排列组合这些因子,得到口令字典,比如上面的5个因子,可以组成好多口令
    - 单因子口令共5个 xidian 2016 12 hello github
    - 双因子口令共5^2=25个 xidianxidian xidian2016 xidian12 ... github12 githubhello githubgithub
    - 3因子口令共5^3=125个
    - 4因子口令共5^4=625个
    - 5因子口令共5^5个
+ 用一个结构体Factor保存读取的因子
+ 每个因子都分配给一个编号,比如 1)xidian 2)2016 3)12 ...
+ 那么任意一种组合可以用一串数值来表示,比如 (1,1)->xidianxidian, (2,1,3)->2016xidian12, (2,2,3)->2016201612
+ 我们给每种组合定义固定的顺序,比如3因子口令按这个顺序 (1,1,1)-(1,1,2)-(1,1,3)-(1,1,4)-(1,1,5)-(1,2,1)-(1,2,2)-...-(5,5,4)-(5,5,5)
+ 我们可以写一个函数`f(因子总数,组合中因子数,组合序号)`产生对应的口令组合
```
f(5,3,1) -> xidianxidianxidian; // 3因子口令第1种组合
f(5,3,2) -> xidianxidian2016;   // 3因子口令第2种组合
```
+ 在一个循环中,逐个产生这些口令组合,逻辑大致如下
```
    for(int i=0;i<因子总数;i++){
        for(int j=0;j<排列总数;j++){
            口令 = f(因子总数, i+1, j);
            保存口令到文件中;
        }
    }
```

## 程序结构设计
+ 定义一个结构体Factor用来保存因子
+ 定义一系列函数FactorXXX来操作因子
+ 主程序中,只通过FactorXXX函数来使用因子,决不直接使用结构体Factor里的内容

这就是数据封装的思想:
+ 把数据封装在一个结构体内部,外部只调用该结构体对应的函数
+ 外部只在更高的抽象层次上工作,不考虑结构体操作函数的内部具体是怎么实现的
+ 结构体函数只负责实现自己要求的功能,不考虑外部会怎么调用它

## 结构体定义
```C
typedef struct tagFactor
{
    // 因子的数目
    unsigned int count;
    // 因子
    char **pElement;
} Factor;
```

## 结构体操作函数
```C
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
```

+ 在编写程序过程中,复杂的方法可以先用简化的实现,保证外部程序可以工作就行,以后再补充正确实现
+ 比如,`FactorReadFromFile`,我们开始只是随便写了点内容,根本没实现从文件中读数据的逻辑
+ 比如,`FactorPermute`,我们开始只返回固定的口令,以后才会再补充逻辑正确的实现