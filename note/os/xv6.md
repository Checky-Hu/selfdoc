xv6 note
======

## chapter0
- `sh.c` implements shell;
- `stat.h` defines file struct;
- plan 9 implements "everything is file";

## chapter1


## appendix-a

### hardware of personal computer
- personal computer contains: CPU, Memory, I/O devices;
- cpu bus contains: Address Bus, Data Bus, Control Bus;

### cpu and memory

#### common registers
- x86 instruction set contains 8 32-bits common registers: %eax, %ebx, %ecx, %edx, %edi, %esi, %ebp, %esp; and 1 instruction pointer register: %eip;
- `e` means `extended`. So there is 8 16-bits common registers too: %ax, %bx, %cx, %dx, %di, %si, %bp, %sp;
- for `%|a-d|x`, there are 2 8-bits common registers for each, such as: %al(low bits) and %ah(high bits) for %ax;

#### float registers
- x86 instruction set contains 8 80-bits float registers;

#### control registers
- x86 instruction set contains 4 control registers: %cr0, %cr2, %cr3, %cr4;(%cr1 is reserved)

#### debug registers
- x86 instruction set contains 4 debug registers: %dr0, %dr1, %dr2, %dr3;

#### segment registers
- x86 instruction set contains 6 segment registers: %cs, %ds, %es, %fs, %gs, %ss;

#### global/local descriptor table registers
- x86 instruction set contains: %gdtr, %ldtr;

### I/O
- x86 instruction set contains `in, out` for I/O devices' read and write;
- modern x86 use `memory mapped I/O` for interacting with I/O devices just like memory;

