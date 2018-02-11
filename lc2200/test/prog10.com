  1                       VAR X 1
  2 0x00000000 0x23D00004 ADDI $a0 $sp 4
  3 0x00000004 0x44300004 SW $a1 0x4($a0)
  4 0x00000008 0x70000000 HALT
  5                       ;should be out of bounds
