MEMORY
{
    FLASH (rwx) : ORIGIN = 0x0000, LENGTH = 0x2000
    RAM   (rwx): ORIGIN = 0x3000, LENGTH = 0x2000
}

SECTIONS
{
    .text : {
        *(.vectors*)
        *(.text*)
    } > FLASH
    .stack :{
	*(.stack*)
    }>RAM
}

