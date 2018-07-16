.section .rodata

msg:
    .ascii "Hello, world!\n"

.section .text

.global _start

_start:
    # call SYS_WRITE
    movl $4, %eax
    # push arguments
    movl $1, %ebx
    movl $msg, %ecx
    movl $14, %edx
    int $0x80

    # Call SYS_EXIT
    movl $1, %eax
    # push arguments
    movl $0, %ebx
    # initiate
    int $0x80
