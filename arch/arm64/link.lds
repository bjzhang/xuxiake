/*
 * Copyright (c) 2022, Bamvor ZHANG
 */

OUTPUT_ARCH( "aarch64" )

MEMORY
{
   SRAM : ORIGIN = 0x40080000, LENGTH = 0x7FF000
}

ENTRY(_start)
SECTIONS
{
    . = 0x40000000 ;

    .start :
    {
        *(.start);
    } > SRAM
}
