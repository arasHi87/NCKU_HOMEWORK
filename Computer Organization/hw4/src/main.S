.section .text
.align 2
.globl main
/* Write your code here */
main:
  addi sp, sp, -4
  sw s0, 0(sp)
  la s0, _test_start
add:
  li t0, 0xffffffff # -1
  li t1, 0xffffffff # -1
  add t0, t0, t1    # t0 = -2
  add t0, t0, t1    # t0 = -3
  add t0, t0, t1    # t0 = -4
  add t0, t0, t1    # t0 = -5
  add t0, t0, t1    # t0 = -6
  li t1, 0xfffffffe # -2
  add t0, t1, t0    # t0 = -8
  add t0, t1, t0    # t0 = -10
  add t0, t1, t0    # t0 = -12
  add t0, t1, t0    # t0 = -14
  add t0, t1, t0    # t0 = -16
  sw t0, 0(s0)
  addi s0, s0, 4
sub:
  li t0, 0x00000000 # 0
  li t1, 0xffffffff # -1
  sub t0, t0, t1    # t0 = 1
  sub t0, t0, t1    # t0 = 2
  sub t0, t0, t1    # t0 = 3
  sub t0, t0, t1    # t0 = 4
  sub t0, t0, t1    # t0 = 5
  li t1, 0xfffffffd # -3
  sub t0, t1, t0    # t0 = -8
  sub t0, t1, t0    # t0 = 5
  sub t0, t1, t0    # t0 = -8
  sub t0, t1, t0    # t0 = 5
  sub t0, t1, t0    # t0 = -8
  sw t0, 0(s0)
  addi s0, s0, 4
xor:
  li t0, 0xffffffff # 
  li t1, 0xf0f0f0f0 # 
  xor t0, t0, t1    # t0 = 0x0f0f0f0f
  xor t0, t0, t1    # t0 = 0xffffffff
  xor t0, t0, t1    # t0 = 0x0f0f0f0f
  xor t0, t0, t1    # t0 = 0xffffffff
  xor t0, t0, t1    # t0 = 0x0f0f0f0f
  li t1, 0x77777777 # 
  xor t0, t1, t0    # t0 = 0x78787878
  xor t0, t1, t0    # t0 = 0x0f0f0f0f
  xor t0, t1, t0    # t0 = 0x78787878
  xor t0, t1, t0    # t0 = 0x0f0f0f0f
  xor t0, t1, t0    # t0 = 0x78787878
  sw t0, 0(s0)
  addi s0, s0, 4
or:
  li t0, 0x12345678 # 
  li t1, 0xfedcba98 # 
  or t0, t0, t1     # t0 = 0xfefcfef8
  or t0, t0, t1     # t0 = 0xfefcfef8
  or t0, t0, t1     # t0 = 0xfefcfef8
  or t0, t0, t1     # t0 = 0xfefcfef8
  or t0, t0, t1     # t0 = 0xfefcfef8
  li t1, 0x62400285 # 
  or t0, t1, t0     # t0 = 0xfefcfefd
  or t0, t1, t0     # t0 = 0xfefcfefd
  or t0, t1, t0     # t0 = 0xfefcfefd
  or t0, t1, t0     # t0 = 0xfefcfefd
  or t0, t1, t0     # t0 = 0xfefcfefd
  sw t0, 0(s0)
  addi s0, s0, 4
and:
  li t0, 0x12345678 # 
  li t1, 0xffffffff # 
  and t0, t0, t1    # t0 = 0x12345678
  and t0, t0, t1    # t0 = 0x12345678
  and t0, t0, t1    # t0 = 0x12345678
  and t0, t0, t1    # t0 = 0x12345678
  and t0, t0, t1    # t0 = 0x12345678
  li t1, 0xf0f0f0f0 # 
  and t0, t1, t0    # t0 = 0x10305070
  and t0, t1, t0    # t0 = 0x10305070
  and t0, t1, t0    # t0 = 0x10305070
  and t0, t1, t0    # t0 = 0x10305070
  and t0, t1, t0    # t0 = 0x10305070
  sw t0, 0(s0)
  addi s0, s0, 4
addi:
  li t0, 0xffffffff  # -1
  addi t0, t0, -1    # t0 = -2
  addi t0, t0, 1893  # t0 = 0x00000763
  addi t0, t0, -1912 # t0 = 0xffffffeb
  addi t0, t0, 1074  # t0 = 0x0000041d
  addi t0, t0, -1348 # t0 = 0xfffffed9
  li t1, 0x00000521  # t1 = 1313
  addi t2, t1, -798  # t2 = 515
  addi t3, t1, 315   # t3 = 1628
  addi t4, t1, 1177  # t4 = 2490
  addi t5, t1, -2047 # t5 = -734
  addi t6, t1, -1432 # t6 = -119
  add t2, t2, t3     # t2 = 2143
  add t4, t4, t5     # t4 = 1756
  add t0, t0, t6     # t0 = -414
  add t2, t2, t4     # t2 = 3899
  add t0, t0, t2     # t0 = 0x00000d9d
  sw t0, 0(s0)
  addi s0, s0, 4
xori:
  li t0, 0xffffffff  #
  xori t0, t0, 123   # t0 = 0xffffff84
  xori t0, t0, -1675 # t0 = 0x000006f1
  xori t0, t0, -831  # t0 = 0xfffffa30
  xori t0, t0, 2033  # t0 = 0xfffffdc1
  xori t0, t0, 1187  # t0 = 0xfffff962
  li t1, 0x00000387  # t1 = 903
  xori t2, t1, -285  # t2 = 0xfffffd64
  xori t3, t1, 164   # t3 = 0x00000323
  xori t4, t1, 1766  # t4 = 0x00000561
  xori t5, t1, -1895 # t5 = 0xfffffb1e
  xori t6, t1, 1209  # t6 = 0x0000073e
  add t2, t2, t3     # t2 = 0x00000087
  add t4, t4, t5     # t4 = 0x0000007f
  add t0, t0, t6     # t0 = 0x000000a0
  add t2, t2, t4     # t2 = 0x00000106
  add t0, t0, t2     # t0 = 0x000001a6
  sw t0, 0(s0)
  addi s0, s0, 4
ori:
  li t0, 0x00000001 #
  ori t0, t0, 444   # t0 = 0x000001bd
  ori t0, t0, 1765  # t0 = 0x000007fd
  ori t0, t0, -291  # t0 = 0xfffffffd
  ori t0, t0, 156   # t0 = 0xfffffffd
  ori t0, t0, 1282  # t0 = 0xffffffff
  li t1, 0x00000783 # t1 = 1923
  ori t2, t1, 285   # t2 = 0x0000079f
  ori t3, t1, -164  # t3 = 0xffffffdf
  ori t4, t1, -1766 # t4 = 0xffffff9b
  ori t5, t1, 1895  # t5 = 0x000007e7
  ori t6, t1, -1209 # t6 = 0xffffffc7
  add t2, t2, t3    # t2 = 0x0000077e
  add t4, t4, t5    # t4 = 0x00000782
  add t0, t0, t6    # t0 = 0xffffffc6
  add t2, t2, t4    # t2 = 0x00000f00
  add t0, t0, t2    # t0 = 0x00000ec6
  sw t0, 0(s0)
  addi s0, s0, 4
andi:
  li t0, 0xabcdef98  #
  andi t0, t0, -333  # t0 = 0xabcdef90
  andi t0, t0, -188  # t0 = 0xabcdee00
  andi t0, t0, 521   # t0 = 0x00000200
  andi t0, t0, -377  # t0 = 0x00000200
  andi t0, t0, 853   # t0 = 0x00000200
  li t1, 0x12345678  #
  andi t2, t1, 2033  # t2 = 0x00000670
  andi t3, t1, 218   # t3 = 0x00000058
  andi t4, t1, -316  # t4 = 0x12345640
  andi t5, t1, 1199  # t5 = 0x00000428
  andi t6, t1, -775  # t6 = 0x12345478
  add t2, t2, t3     # t2 = 0x000006c8
  add t4, t4, t5     # t4 = 0x12345a68
  add t0, t0, t6     # t0 = 0x12345678
  add t2, t2, t4     # t2 = 0x12346130
  add t0, t0, t2     # t0 = 0x2468b7a8
  sw t0, 0(s0)
  addi s0, s0, 4
main_exit:
  /* Simulation End */
  lw s0, 0(sp)
  addi sp, sp, 4
  ret

.section .rodata
lw_data:
  .word 0x66666666
