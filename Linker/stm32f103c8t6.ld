ENTRY(Reset_Handler)

MEMORY 
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text : 
    {
        *(.isr_vector)  /* Vector table */
        *(.text)        /* Code section */
        *(.rodata)      /* Read-only data */
        . = ALIGN(4); 
        _etext = .;
    } > FLASH

    _la_data = LOADADDR(.data); 

    .data : 
    {
        _sdata = .; 
        *(.data)        /* Initialized data */
        . = ALIGN(4); 
        _edata = .; 
    } > SRAM AT > FLASH

    .bss : 
    {
        _sbss = .;
        *(.bss)         /* Uninitialized data */
        *(.COMMON)      /* Common data (zero initialized) */
        . = ALIGN(4); 
        _ebss = .;
    } > SRAM 
}

