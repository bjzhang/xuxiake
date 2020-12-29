/*
 * Copyright (c) 2020, Bamvor ZHANG
 */

OUTPUT_ARCH( "riscv" )

MEMORY
{
   SRAM : ORIGIN = 0x80200000, LENGTH = 0x7FF000
}

ENTRY(_start)
SECTIONS
{
    . = 0x80200000 ;

    .start :
    {
        *(.start);
    } > SRAM
}
