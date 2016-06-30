BITS 16
[global _start]
[extern main]

push 0
call main

jmp $
