MAIN: mov #1,r1
cmp r1,r2
add #2,r3
sub DAT,r3
not r4
clr DAT
lea STR, r5
inc r4
dec DAT
jmp MAIN
bne MAIN(#1,r3)
red STR
prn STR
jsr MAIN
rts
stop

DAT: .data 1,2,3
STR: .string "abc"
