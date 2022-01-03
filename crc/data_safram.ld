SECTIONS
{
    .data_safram : {
        _DATA_SAFRAM_START = .;
        *(.data_safram);
        . = . + 1;
        _DATA_SAFRAM_END = .;
    }
}
INSERT AFTER .data