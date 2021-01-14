
CROSS_COMPILE=/home/bamvor/works/source2/software/riscv64-unknown-elf-gcc-8.3.0-2020.04.1-x86_64-linux-ubuntu14/bin//riscv64-unknown-elf-

all:
	${CROSS_COMPILE}gcc -c -mcmodel=medany -march=rv64imafdc -mabi=lp64d -x assembler-with-cpp -ggdb -c -o head.o head.S -D__ASSEMBLY__
	${CROSS_COMPILE}gcc -c -mcmodel=medany -march=rv64imafdc -mabi=lp64d -ggdb -c -o cpu_entry.o cpu_entry.c -nostdlib
	${CROSS_COMPILE}gcc -o xuxiake.elf -mcmodel=medany -march=rv64imafdc -mabi=lp64d -nostartfiles -Wl,--gc-sections,-Map=xuxiake.map,-cref,-u,_start -T link.lds head.o cpu_entry.o
	${CROSS_COMPILE}objcopy -O binary xuxiake.elf xuxiake.bin

qemu:
	qemu-system-riscv64 -M virt -m 512M -smp 1 -bios /home/bamvor/works/source/opensbi/build/platform/generic/firmware/fw_jump.bin -kernel xuxiake.bin -nographic -S -s
