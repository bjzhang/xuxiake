# XU xiake

XU xiake is a "travel writer and geographer in of the Ming dynasty. He traveled throughout China for more than 30 years, documenting his travels extensively." (from wiki: https://en.wikipedia.org/wiki/Xu_Xiake). His long time travel and notes are quite important work.

When I started to learn the ARM architecture 15 years ago. There is no well-organized material at all. Things be better in recent years. While it is still a gap between read the documents of ARM and do the real pratice in the proper but not complex environment. This is why I create XU xiake project. I hope XU xuxiake could help from beginner to intermediate level by travelling ON the difference hardware features through software.

It is not the goal that writing an operation system. Instead, this project focus on how to understand the hardware by writing code. Currently, it act as an simple operation system. While it could be a bootloader, hypervisor or library. And I will provide the exercises with XU xiake later.

Right now, XU xiake only support ARM64 in qemu(qemu-system-aarch64). I plan to support ARM64 and RISC-V in both emulator and hardware.


## Build
Execute the following command to build MMU or userspace support respectively.
`make CFLAGS="-DCONFIG_MMU"``
`make CFLAGS="-DCONFIG_USERSPACE -DCONFIG_SYSCALL"`

### Expected output
```
$ make CFLAGS="-DCONFIG_MMU"
aarch64-linux-gcc  -x assembler-with-cpp -ggdb -c -o arch/arm64/head.o arch/arm64/head.S -D__ASSEMBLY__ -DCONFIG_MMU -Wall -I. -Iarch/arm64/include -DDEBUG
aarch64-linux-gcc -ggdb -c -o cpu_entry.o cpu_entry.c -ffreestanding -DCONFIG_MMU -Wall -I. -Iarch/arm64/include -DDEBUG
aarch64-linux-gcc -ggdb -c -o lib.o lib.c -ffreestanding -DCONFIG_MMU -Wall -I. -Iarch/arm64/include -DDEBUG
aarch64-linux-gcc -ggdb -c -o arch/arm64/lib.o arch/arm64/lib.c -ffreestanding -DCONFIG_MMU -Wall -I. -Iarch/arm64/include -DDEBUG
aarch64-linux-gcc -ggdb -c -o arch/arm64/cpu_entry.o arch/arm64/cpu_entry.c -ffreestanding -DCONFIG_MMU -Wall -I. -Iarch/arm64/include -DDEBUG
aarch64-linux-gcc -ggdb -c -o arch/arm64/mmu.o arch/arm64/mmu.c -ffreestanding -DCONFIG_MMU -Wall -I. -Iarch/arm64/include -DDEBUG
aarch64-linux-gcc -ggdb -c -o arch/arm64/print.o arch/arm64/print.c -ffreestanding -DCONFIG_MMU -Wall -I. -Iarch/arm64/include -DDEBUG
aarch64-linux-gcc -o xuxiake.elf -nostartfiles -Wl,--gc-sections,-Map=xuxiake.map,-cref,-u,_start -T arch/arm64/link.lds arch/arm64/head.o arch/arm64/lib.o arch/arm64/cpu_entry.o arch/arm64/print.o arch/arm64/mmu.o lib.o cpu_entry.o -DCONFIG_MMU -Wall -I. -Iarch/arm64/include -DDEBUG
aarch64-linux-objcopy -O binary xuxiake.elf xuxiake.bin
aarch64-linux-objdump -Sx xuxiake.elf > xuxiake.S
```

## Run
`make qemu`

### Expected output
#### MMU
```
bamvor@VM-24-2-ubuntu:~/works/source/xuxiake$ make qemu
qemu-system-aarch64 -M virt -cpu cortex-a72 -m 3072M -smp 1 -kernel xuxiake.bin -nographic
XXK: Hello XU Xiake
Current exception level: 0x00000001
XXK: After set vector
XXK: MMU initing
XXK: MMU init done
XXK: Test write addres not mappped by kernel:enter svc esr: 0x96000049, ec: 0x00000025, iss: 0x00000049
Data abort from lower exception
fault address is valid 0x80000000
fault by writing
CAUTION: may some level is not actually exist
dfsc: 0x0x00000009, type: access flag fault, enable it by setting af=1, level: 0x00000001
Exception return
...DONE
XXK: Exit!(Please poweroff or kill the qemu process)
```

#### USERSPACE
Note that because MMU is off, userspace could access the hardware register. And it will be trapped by svc instruction when XU xiake is compiled with CONFIG_SYSCALL.
```
bamvor@VM-24-2-ubuntu:~/works/source/xuxiake$ make qemu
qemu-system-aarch64 -M virt -cpu cortex-a72 -m 3072M -smp 1 -kernel xuxiake.bin -nographic
XXK: Hello XU Xiake
Current exception level: 0x00000001
XXK: After set vector
XXK: Jump to userspace
try to output from userspace by accessing uart register directly
enter svc esr: 0x56000000, ec: 0x00000015, iss: 0x00000000
SVC from aarch64 EE
write syscall
try to output from userspace by write syscall
Exception return
XXK: Exit!(Please poweroff or kill the qemu process)
```

## How to debug
In the first terminal, run with "-s -S", e.g.  `make qemu DEBUG="-s -S"`
In the second terminal, run the gdb/gdb-multiarch depends on if your gdb support multiarch or not. e.g. `gdb-multiarch xuxiake.elf`

In the second terminal, If "auto loading" warning is encountered, add `.gdbinit` to `~/.gdbinit`, e.g. `add-auto-load-safe-path /home/bamvor/works/source/xuxiake/.gdbinit`
```
In the second terminal, connect to qemu by `target remote :1234`
```
(gdb) target remote :1234
```
Then your could debug it as usually.

