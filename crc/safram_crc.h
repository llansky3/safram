/* Example of safety RAM protection & checking using checksum */
#ifndef SAFRAM_CRC_H
#define SAFRAM_CRC_H

/* Functions */
uint8_t safram_crc_protect(void);
uint8_t safram_crc_check(void);

void restart(char **argv, uint8_t count);

/*  Memory addresses for safety RAM 
    Note that these will be supplied during linking! */

extern uint32_t _DATA_SAFRAM_START;
extern uint32_t _DATA_SAFRAM_END;

#define PTR_UINT8_SAFRAM_START (uint8_t*)&_DATA_SAFRAM_START
#define PTR_UINT8_SAFRAM_END   (uint8_t*)&_DATA_SAFRAM_END  
    
#endif  /* SAFRAM_CRC_H */
