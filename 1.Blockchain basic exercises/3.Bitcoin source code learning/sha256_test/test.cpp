#include<iostream>

#include "sha256.h"
#include "uint256.h"

//using namespace std;
int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        std::cout<<"please type a string to test sha-256"<<std::endl;
        return 1;
    }

    char* str = argv[1];

    std::cout << "The string to test SHA-256:" << std::endl;
    int strLen = strlen(str);
    for(char* p = str; p<str+strLen; p++)
    {
        std::cout<<*p;
    }
    std::cout<<std::endl;

    uint256 sha256_result;

    // use code in Bitcoin Core to solve SHA-256
    CSHA256 sha;
    sha.Write((unsigned char*)str, strLen);
    sha.Finalize((unsigned char*)&sha256_result);

    // show hash result by GetHex()
    std::cout << std::endl << "Bitcoin SHA-256 result by GetHex():" << std::endl;
    std::cout << sha256_result.GetHex() << std::endl;

    // show hash result by parsing member variable data[Width]
    std::cout << std::endl << "Bitcoin SHA-256 result by parse data[Width]:" << std::endl;
    unsigned int size = sha256_result.size();
    unsigned char* pointer = sha256_result.begin();
    unsigned char temp;
    for(unsigned char* pdata = pointer; pdata < pointer + size; pdata++)
    {
        temp = *pdata;
        unsigned char hex1 = temp >> 4;
        unsigned char hex2 = temp & 0x0f;

        if(hex1<10)
            std::printf("%c",hex1+48);
        else
            std::printf("%c",hex1+87);

        if(hex2<10)
            std::printf("%c",hex2+48);
        else
            std::printf("%c",hex2+87);
    }
    std::cout << std::endl;
}
