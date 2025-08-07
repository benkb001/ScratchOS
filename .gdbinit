# .gdbinit
target remote localhost:1234
file kernel/kernel.elf
symbol-file kernel/kernel.elf
layout asm
break *0x1155
continue