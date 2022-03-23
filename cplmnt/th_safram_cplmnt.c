#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "safram_cplmnt.h"

void restart(char **argv, uint8_t count)
{
	char buffer[32] = {};
    char *nargv[] = {argv[0], buffer, 0};
	
    snprintf(buffer, sizeof(buffer), "%u",count + 1);
    execv("/proc/self/exe", nargv);
    printf("This should never be reached!");
}

SAFRAM_DEF_UINT8_ARRAY(testarray) = {255, 254, 253, 252, 251, 250, 249, 248};
SAFRAM_DEF_UINT8_ARRAY_CPLMNT(testarray) = {0, 1, 2, 3, 4, 5, 6, 7};

void periodic_task(char **argv, uint8_t count)
{
	/* No specific safety critical section */
    uint8_t value;
    for(uint8_t i = 0; i < 8; i++) {
        value = SAFRAM_GET_UINT8_ARRAY(testarray, i, restart(argv, count));
        if (i == 1) {
            printf("testarray[%u]=0x%02X, one's complement=0x%02X\n", i, value, FCN_UINT8_CPLMNT(value));
            value += i;
            SAFRAM_SET_UINT8_ARRAY(testarray, i, value);
        }
    }
	sleep(1);
}

int main(int argc, char* argv[]) 
{
    uint8_t count = argc > 1 ? atoi(argv[1]) : 0;
    uint8_t *safram_start = PTR_UINT8_SAFRAM_START;
    uint8_t *safram_cplmnt_start = PTR_UINT8_SAFRAM_CPLMNT_START;
	uint8_t *safram_end = PTR_UINT8_SAFRAM_END;
	uint8_t *safram_cplmnt_end = PTR_UINT8_SAFRAM_CPLMNT_END; 
    
    if (argc > 2) {
        printf("Usage:\n");
        printf("  th_safram_cplmnt count\n");
        exit(1);
    }

    printf("This is an example of protecting RAM variable with one's complement! Run #%d!\n", count);
	printf("pid=%d\n", getpid());
    printf(".data_safram       , start_address=%p, length=%lu\n", safram_start, safram_end - safram_start);
    printf(".data_safram_cplmnt, start_address=%p, length=%lu\n", safram_cplmnt_start, safram_cplmnt_end - safram_cplmnt_start);
	
    /* Executing periodic task and waiting for external memory corruption */
	while(1) {
		periodic_task(argv, count);
	}
}