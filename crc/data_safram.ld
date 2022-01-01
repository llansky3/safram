SECTIONS
{
    .data_safram : {
        _DATA_SAFRAM_START = .;
        *(.data_safram);
        . = . + 1;
        _DATA_SAFRAM_END = .;
        _DATA_SAFRAM_CHECKSUM = .;
    }
}
INSERT AFTER .data