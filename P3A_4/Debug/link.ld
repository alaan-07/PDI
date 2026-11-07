/*
 * The stack starts at the top of memory, defined by __sp, and grows down.
 * Unfortunately this means we must hardcode the size of memory.
 * Here we choose 64K. Change this value to change the working memory size.
 */
__mem   = 0x40000000; /*This should be set to the beginning of the memory as specified by the device tree, for spike run: "spike --dump-dts a.out"*/

__stack = 0x00100000; /*This is the offset that the stack is from the start of memory.*/

SECTIONS
{
    . = __mem;
    .text : ALIGN(4) {
    __text_init = .;
        *(.text.init) /* add the instruction from init.s*/
        *(.text)      /* add the instructions compiled */
        *(.rodata)
    __text_end = .;
    }

    .data : ALIGN(4) {
    __data_init = .;
        *(COMMON)
        *(.sdata)
        *(.data*)
        *(.got*)
    __data_end = .;
    }

    .bss : ALIGN(4) {
    __bss_init = .;
        *(.sbss)
        *(.bss)
    __bss_end = .;
    }

    .commnent : { *(.comment) }
    .riscv.attributes : { *(.riscv.attributes) }
}
