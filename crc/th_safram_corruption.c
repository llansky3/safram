/* Inspired by: https://renenyffenegger.ch/notes/Linux/memory/read-write-another-processes-memory */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char* argv[]) 
{
    if (argc != 4) {
        printf("Usage:\n");
        printf("  th_safram_corruption pid start_address length\n");
        exit(1);
    }

    uint16_t pid = strtol(argv[1], NULL, 10);
    uint32_t start_address = strtoul(argv[2], NULL, 16);
    uint16_t length = strtol(argv[3], NULL, 10);

    char proc_mem[32];
    sprintf(proc_mem, "/proc/%d/mem", pid);

    printf("Opening %s, address is %ld\n", proc_mem, start_address);
    int fd_proc_mem = open(proc_mem, O_RDWR);
    if (fd_proc_mem == -1) {
        printf("Could not open %s\n", proc_mem);
        exit(1);
    }

    uint8_t *data = malloc(length);

    lseek(fd_proc_mem, start_address, SEEK_SET);
    read(fd_proc_mem, data, length);

    printf("Data at %ld in process %d is:", start_address, pid);
    for (uint16_t i = 0; i < length; i++ ) {
        if (!(i % 10)) {
            printf("\n");
        }
        printf("  %X\n", data[i]);
    }

    printf("Adding one to the first byte!\n");
    data[0]++;

    lseek(fd_proc_mem, start_address, SEEK_SET);
    if (write (fd_proc_mem, data, length) == -1) {
        printf("Error while writing\n");
        exit(1);
    }

    free(data);
}