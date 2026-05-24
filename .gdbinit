set confirm off
set architecture riscv:rv32
target remote 127.0.0.1:26000
symbol-file kernel/kernel
set disassemble-next-line auto
set riscv use-compressed-breakpoints yes
define reset
  target remote :26000
  monitor reset
  b main
  continue
end