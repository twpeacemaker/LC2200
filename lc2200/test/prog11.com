  1 0x00000000 0x95000000 IN $a2
  2 0x00000004 0x03000005 ADD $a0 $zero $a2
  3 0x00000008 0x44300000 SW $a1 0x0($a0)
  4                       ;test out of bounds of prog mem
  5 0x0000000C 0x95000000 IN $a2
  6 0x00000010 0x0D000005 ADD $sp $zero $a2
  7 0x00000014 0x44D00000 SW $a1 0x0($sp)
  8                       ;test out of bounds of stack mem
  9 0x00000018 0x70000000 HALT
