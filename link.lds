/*
 * Copyright (c) 2020, Bamvor ZHANG
 */

OUTPUT_ARCH( "riscv" )

MEMORY
{
   SRAM : ORIGIN = 0x80000000, LENGTH = 0x00500000
}

ENTRY(_start)
SECTIONS
{
    . = 0x80200000 ;

    .start :
    {
        *(.start);
    }
}
