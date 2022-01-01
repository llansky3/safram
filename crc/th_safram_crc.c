/* Example of safety RAM protection & checking using checksum */
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "safram_crc.h"

void restart(char **argv, uint8_t count)
{
	char buffer[32] = {};
    char *nargv[] = {argv[0], buffer, 0};
	
    snprintf(buffer, sizeof(buffer), "%d",count + 1);
    execv("/proc/self/exe", nargv);
    printf("This should never be reached!");
}

__attribute__((section(".data_safram"))) uint8_t testarray[] = {0, 0, 0, 0};

int main(int argc, char **argv)
{
	uint8_t count = argc > 1 ? atoi(argv[1]) : 0; 
	uint8_t *safram_start = PTR_UINT8_SAFRAM_START;
	uint8_t *safram_end = PTR_UINT8_SAFRAM_END;
	uint8_t crc = safram_crc_protect();
	
	printf("This is an example of protecting RAM area with checksum! Run #%d!\n", count);
	printf("pid=%d, safram start_address=%lx, length=%lu, checksum=%lu\n", getpid(), safram_start, safram_end - safram_start - 1, crc);

	/* Waiting for external memory corruption */
	while(1) {
		if (safram_crc_check()) {
			restart(argv, count);
		}
		sleep(1);
	}
}