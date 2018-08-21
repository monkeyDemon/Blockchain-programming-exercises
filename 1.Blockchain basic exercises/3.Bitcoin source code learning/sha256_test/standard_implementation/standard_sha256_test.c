/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "standard_sha256.h"

/*********************** FUNCTION DEFINITIONS ***********************/
void sha256_test()
{
	// test data
    printf("the string to test SHA-256: hello\n");
	BYTE text1[] = {"hello"};
	BYTE buf[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;
	int idx;
	int pass = 1;

	sha256_init(&ctx);
	sha256_update(&ctx, text1, strlen(text1));
	sha256_final(&ctx, buf);


    printf("\nresult of SHA-256\n");
    BYTE temp;
    for(int i=0; i<SHA256_BLOCK_SIZE; i++)
    {
        temp = buf[i];
        BYTE hex1 = temp >> 4;
        BYTE hex2 = temp & 0x0f;

        if(hex1<10)
            printf("%c",hex1+48);
        else
            printf("%c",hex1+87);

        if(hex2<10)
            printf("%c",hex2+48);
        else
            printf("%c",hex2+87);
    }
    printf("\n");

}

int main()
{
    sha256_test();

	return(0);
}
