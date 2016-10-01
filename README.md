#Try Assembly on Linux

###Install nasm
We need **nasm** to create object file by assembly code. [Wikipedia](https://en.wikipedia.org/wiki/Netwide_Assembler "Click me!") says: **nasm** is an assembler and disassembler for the Intel x86 architecture. It can be used to write 16-bit, 32-bit (IA-32) and 64-bit (x86-64) programs. NASM is considered to be one of the most popular assemblers for Linux. <br/>

Run <br/>
```
sudo apt install nasm
```
###Create asm file
We want to see result so just copy the code below. Code is from ![logo](https://cloud.githubusercontent.com/assets/19840443/19013290/f3fcb338-87cc-11e6-96a5-eaa50f0c0aca.png)<br/>
``` asm
section	.text
    global _start   ;must be declared for linker (ld)
_start:	            ;tells linker entry point
    mov	edx,len     ;message length
    mov	ecx,msg     ;message to write
    mov	ebx,1       ;file descriptor (stdout)
    mov	eax,4       ;system call number (sys_write)
    int	0x80        ;call kernel
	
    mov	eax,1       ;system call number (sys_exit)
    int	0x80        ;call kernel

section	.data
msg db 'Hello, world!', 0xa  ;string to be printed
len equ $ - msg     ;length of the string
```
