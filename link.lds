/*
 * Copyright (c) 2020, Bamvor ZHANG
 */

OUTPUT_ARCH( "riscv" )

MEMORY
{
   SRAM : ORIGIN = 0x45200000, LENGTH = 0x7FF000
}

ENTRY(_start)
SECTIONS
{
    . = 0x45000000 ;

    .start :
    {
        *(.start);
    } > SRAM
}
