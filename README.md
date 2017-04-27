#Try Assembly on Linux

##Install nasm
We need **nasm** to create object file by assembly code. [Wikipedia](https://en.wikipedia.org/wiki/Netwide_Assembler "Click me!") says: **nasm** is an assembler and disassembler for the Intel x86 architecture. It can be used to write 16-bit, 32-bit (IA-32) and 64-bit (x86-64) programs. NASM is considered to be one of the most popular assemblers for Linux. Try <br/>
```
sudo apt install nasm
```
<br/>
##Create asm file
We want to see results so just copy the code below and save as "main.asm". Code is from ![logo](https://cloud.githubusercontent.com/assets/19840443/19013290/f3fcb338-87cc-11e6-96a5-eaa50f0c0aca.png)<br/>
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
<br/>
##Create object file
The ```nasm -hf``` gives available output formats. Check [stackoverflow]( "http://stackoverflow.com/questions/4252227/error-when-trying-to-run-asm-file-on-nasm-on-ubuntu" "stackoverflow site" ).
```
valid output formats for -f are (`*' denotes default):
  * bin       flat-form binary files (e.g. DOS .COM, .SYS)
    ith       Intel hex
    srec      Motorola S-records
    aout      Linux a.out object files
    aoutb     NetBSD/FreeBSD a.out object files
    coff      COFF (i386) object files (e.g. DJGPP for DOS)
    elf32     ELF32 (i386) object files (e.g. Linux)
    elf       ELF (short name for ELF32) 
    elf64     ELF64 (x86_64) object files (e.g. Linux)
    as86      Linux as86 (bin86 version 0.3) object files
    obj       MS-DOS 16-bit/32-bit OMF object files
    win32     Microsoft Win32 (i386) object files
    win64     Microsoft Win64 (x86-64) object files
    rdf       Relocatable Dynamic Object File Format v2.0
    ieee      IEEE-695 (LADsoft variant) object file format
    macho32   NeXTstep/OpenStep/Rhapsody/Darwin/MacOS X (i386) object files
    macho     MACHO (short name for MACHO32)
    macho64   NeXTstep/OpenStep/Rhapsody/Darwin/MacOS X (x86_64) object files
    dbg       Trace of all info passed to output stage
```
We have linux, so try it
```
nasm -f elf64 -o main.o main.asm
```
<br/>
##Create executable file
```
ld main.o -o main
```
<br/>
##Open
```
chmod +x main
./main
```
