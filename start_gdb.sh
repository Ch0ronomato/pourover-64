gdb -ex 'set arch mips:4000' -ex 'gef-remote --qemu-user --qemu-binary build/hello.elf 127.0.0.1 5064' build/hello.elf
