# SHA256 的C语言实现

前几天总结了[SHA256的算法原理](https://blog.csdn.net/u011583927/article/details/80905740)一文

SHA2系列的原理并不复杂，但是需要注意细节还是挺多的。不少中文博客贴出的代码都有错，这两天也踩了几个坑。

代码在这里！！！[SHA256的C Code](https://github.com/monkeyDemon/Blockchain-programming-exercises/tree/master/1.Blockchain%20basic%20exercises/2.Cryptography%20and%20security%20technology/SHA256/C%20Code)

代码实现主要依照的这个git仓库[crypto-algorithms](https://github.com/B-Con/crypto-algorithms)，向大家推荐，里面实现了各种加密算法。

## 代码正确性的测试

如何测试加密算法是否正确，上一文也提到过

我使用的是一个[在线SHA256加密验证工具](https://hash.online-convert.com/sha256-generator)

测试了三种不同类型的数据的Hash结果
- 纯英文
- 中英文夹杂
- 长消息

## 逻辑运算

SHA256中使用的所有逻辑运算，使用宏定义的方式实现如下：
``` C
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
```

## 算法回顾
这里对SHA256原理进行简单回顾，方便大家对照源代码

首先需要将原始消息拆解成512-bit大小的块
![插图1](./markdown_image/SHA256_1.png)

最后单独甩出的不完整的块需要被补全,对应代码中的`sha256_final`函数

整体的操作是依次对块进行Hash映射，第i块映射的结果是第i+1块的输入。这个过程在函数`sha256_update`中完成

第一个块的输入是预设好的hash初值，初始化过程对应代码中的`sha256_init`函数

最后一个块的输出便是最终的数字摘要
![插图2](./markdown_image/SHA256_2.png)

而其中最关键的操作是这个映射函数Map

其内部也相当于是一个循环加密的过错，不断将原始信息进行打乱：

![插图4](./markdown_image/SHA256_4.png)

代码中函数`sha256_transform`实现了该过程
