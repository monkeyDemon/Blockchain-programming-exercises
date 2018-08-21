// Copyright (c) 2014-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CRYPTO_SHA256_H
#define BITCOIN_CRYPTO_SHA256_H

#include <stdint.h>
#include <stdlib.h>
#include <string>

/** A hasher class for SHA-256. */
class CSHA256
{
private:
    uint32_t s[8];            // 8个哈希初值，Initialize中进行初始化

    // 缓冲区(SHA256以512bit为单位，一个block一个block的进行hash映射，因此缓冲区为64byte)
    // 将待哈希的序列添加进缓冲区，每当缓冲区填满，进行一次变换，将缓冲区清空
    unsigned char buf[64];

    // 记录曾经加入到缓冲区的总字节数
    // 因此当全部数据写入后，bytes代表了待Hash的数据的总字节数
    // 还可以通过对64取余可以判断当前缓冲区中存在的剩余数据的字节数
    uint64_t bytes;

    // 这两个私有成员的含义不太好理解，可以通过阅读我写的博客更好的理解源代码
    // https://blog.csdn.net/u011583927/article/details/80905740
public:
    static const size_t OUTPUT_SIZE = 32;

    CSHA256();
    CSHA256& Write(const unsigned char* data, size_t len);
    void Finalize(unsigned char hash[OUTPUT_SIZE]);
    CSHA256& Reset();
};

/** Autodetect the best available SHA256 implementation.
 *  Returns the name of the implementation.
 */
std::string SHA256AutoDetect();

/** Compute multiple double-SHA256's of 64-byte blobs.
 *  output:  pointer to a blocks*32 byte output buffer
 *  input:   pointer to a blocks*64 byte input buffer
 *  blocks:  the number of hashes to compute.
 */
void SHA256D64(unsigned char* output, const unsigned char* input, size_t blocks);

#endif // BITCOIN_CRYPTO_SHA256_H
