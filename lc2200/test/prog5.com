  1 0x00000000 0x91000000 IN  $at
  2                       ;n
  3 0x00000004 0x05000000 ADD $a2 $zero $zero
  4                       ;= counter
  5 0x00000008 0x51500014 back: BEQ $at $a2 next
  6                       ;while(len > counter) {
  7 0x0000000C 0x94000000 IN $a1
  8 0x00000010 0x44D00000 SW $a1 0x0($sp)
  9 0x00000014 0x2DDFFFFC ADDI $sp $sps -4
 10 0x00000018 0x25500001 ADDI $a2 $a2 1scs
 11 0x0000001C 0x500FFFE8 BEQ $zero $zero back
 12                       ;unconditional back
 13 0x00000020 0x70000000 next: HALT
