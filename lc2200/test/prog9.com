  1                       VAR X 100
  2 0x00000000 0x91000000 IN $at
  3 0x00000004 0xCC00005C LA $k0 X
  4 0x00000008 0x03C00000 ADD $a0 $k0 $zero
  5 0x0000000C 0x05000000 ADD $a2 $zero $zero
  6 0x00000010 0x51500014 back: BEQ $at $a2 next
  7 0x00000014 0x94000000 IN $a1
  8 0x00000018 0x44300000 SW $a1   0x0($a0)
  9 0x0000001C 0x23300004 ADDI $a0   $a0     4
 10 0x00000020 0x25500001 ADDI $a2   $a2     1
 11 0x00000024 0x500FFFE8 BEQ $zero $zero   back
 12 0x00000028 0x02100000 next: ADD   $v0   $at $zero
 13 0x0000002C 0x222FFFFF bac3: ADDI  $v0   $v0 -1
 14 0x00000030 0x05000000 ADD $a2 $zero $zero
 15 0x00000034 0x03C00000 ADD $a0 $k0 $zero
 16 0x00000038 0x36300000 back2: LW    $t0 0x0($a0)
 17 0x0000003C 0x37300004 LW    $t1   0x4($a0)
 18 0x00000040 0xD7600008 BGT   $t1   $t0 noth
 19 0x00000044 0x47300000 SW    $t1   0x0($a0)
 20 0x00000048 0x46300004 SW    $t0   0x4($a0)
 21 0x0000004C 0x25500001 noth: ADDI  $a2 $a2  1
 22 0x00000050 0x23300004 ADDI  $a0   $a0 4
 23 0x00000054 0xD25FFFE0 BGT   $v0   $a2 back2
 24 0x00000058 0x24000001 ADDI  $a1   $zero 1
 25 0x0000005C 0xD24FFFCC BGT   $v0   $a1 bac3
 26 0x00000060 0x70000000 HALT
