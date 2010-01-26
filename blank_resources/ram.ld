// Nancy Minderman
// April 20, 2007
// Notes:

CONSTANTS
{
	vt_reserve = 8 * 4 + 5 * 4
	sup_stack_reserve = 2k
	stack_reserve = 30k
	heap_reserve = 30k
}

MEMORY {

// 256KB of sram starting at 0x02000000
// If the ANGEL monitor is in use,
// it will occupy the last half of RAM
//    ram_base    : ORIGIN = 0x02000000, LENGTH = 128K
//    ram_angel   : ORIGIN = 0x02020000, LENGTH = 256K-128K

// 256KB of sram starting at 0x02000000
// If you are using the Slingshot JTAG device to connect
// Angel is not running and all ram is available
 	ram_base	: ORIGIN = 0x02000000, LENGTH = 256K
 	ram_angel	: ORIGIN = ., LENGTH = 0

// Note that the following locations do reflect
// the flash map when code is running from RAM
// and the STD jumper is set
// DO NOT USE this map for code running from ROM
// romrun.ld and romcopy.ld are to be used in those cases
	flash_angel  : ORIGIN = 0x01000000, LENGTH = 1M
	flash_user   : ORIGIN = 0x01100000, LENGTH = 1M
}

SECTIONS
{

//
// The text segment
//

    .picbase                                            : > ram_base
    .text                                               : > .
    .syscall                                            : > .
    .intercall                                          : > .
    .interfunc                                          : > .
    .fixaddr                                            : > .
    .fixtype                                            : > .
    .rodata                                             : > .
    .secinfo                                            : > .

//
// The data segment
//

    .pidbase                                  ALIGN(16) : > .
    .sdabase                                            : > .
    .sbss                                               : > .
    .sdata                                              : > .
    .data                                               : > .
    .bss                                                : > .
    .heap                  ALIGN(16) PAD(heap_reserve)  : > .
    .stack                 ALIGN(16) PAD(stack_reserve) : > .
//
// These special symbols mark the bounds of RAM and ROM memory.
// They are used by the MULTI debugger.
//
    __ghs_romstart  = MEMADDR(flash_angel);
    __ghs_romend    = MEMENDADDR(flash_user);
    __ghs_ramstart  = MEMADDR(ram_base);
    __ghs_ramend    = MEMENDADDR(ram_angel);
        
}

