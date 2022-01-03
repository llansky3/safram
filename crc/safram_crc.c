
#include <stdint.h>

#include "safram_crc.h"
#include "crc8.h"

uint8_t safram_crc_protect(void)
{
	uint8_t *safram_start = PTR_UINT8_SAFRAM_START;
	uint8_t *safram_end = PTR_UINT8_SAFRAM_END;
	uint8_t crc;
	
    /* calculate CRC - excluding checksum itself */
	crc = crc8(safram_start,(uint32_t) (safram_end - safram_start - 1) , 0xFF);
	crc = crc ^ 0xFF;
	
	/* last byte in .data_safram memory section is the checksum */
	*safram_end = crc;
	return crc;
	
}
 
uint8_t safram_crc_check(void)
{
    uint8_t *safram_start = PTR_UINT8_SAFRAM_START;
	uint8_t *safram_end = PTR_UINT8_SAFRAM_END;
	uint8_t crc;
	
	crc = crc8(safram_start,(uint32_t) (safram_end - safram_start - 1) , 0xFF);
	crc = crc ^ 0xFF;
	
	if (*safram_end != crc)
	{
		/* Memory is corrupted */
		return 1;
	}
	else
	{
		/* All good, checksum matches */
		return 0;
	}
}

