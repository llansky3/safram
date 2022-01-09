SECTIONS
{
    .data_safram : {
        _DATA_SAFRAM_START = .;
        *(.data_safram);
        _DATA_SAFRAM_END = .;
    }
    
    .data_safram_cplmnt : {
        _DATA_SAFRAM_CPLMNT_START = .;
        *(.data_safram_cplmnt);
        _DATA_SAFRAM_CPLMNT_END = .;
    }
}
INSERT AFTER .data