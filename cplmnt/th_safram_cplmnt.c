#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "safram_cplmnt.h"

void restart()
{
	printf("This is restart!\n");
}

int main(int argc, char* argv[]) 
{
    if (argc != 1) {
        printf("Usage:\n");
        printf("  th_safram_cplmnt\n");
        exit(1);
    }
    uint8_t testarray[] = {0,0,0,0};
    uint8_t testarray_cplmnt[] = {0,0,0,0};
    
    SAFRAM_SET_UINT8_ARRAY(testarray, 0, 0x55);

    printf("testarray[0]=0x%X, testarray_cpl[0]=0x%X\n", testarray[0],testarray_cplmnt[0]);
    
    printf("SAFRAM_GET_UINT8_ARRAY(testarray, 0)=0x%X\n", SAFRAM_GET_UINT8_ARRAY(testarray, 0, restart));
    testarray_cplmnt[0] = 0;
    printf("SAFRAM_GET_UINT8_ARRAY(testarray, 0)=0x%X\n", SAFRAM_GET_UINT8_ARRAY(testarray, 0, restart));
}