  1 0x00000000 0x230FFFFC ADDI $a0 $zero -4
  2 0x00000004 0x44300000 SW $a1 0x0($a0)
  3 0x00000008 0x70000000 HALT
  4                       ;should be out of bounds
