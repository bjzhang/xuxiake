

all:
	riscv64-unknown-elf-gcc -c -mcmodel=medany -march=rv64imafdc -mabi=lp64d -x assembler-with-cpp -ggdb -c -o head.o head.S
	riscv64-unknown-elf-gcc -c -mcmodel=medany -march=rv64imafdc -mabi=lp64d -ggdb -c -o cpu_entry.o cpu_entry.c -nostdlib
	riscv64-unknown-elf-gcc -o xuxiake.elf -mcmodel=medany -march=rv64imafdc -mabi=lp64d -nostartfiles -Wl,--gc-sections,-Map=xuxiake.map,-cref,-u,_start -T link.lds head.o cpu_entry.o
	riscv64-unknown-elf-objcopy -O binary xuxiake.elf xuxiake.bin

qemu:
	qemu-system-riscv64 -M virt -m 512M -smp 1 -bios /home/bamvor/works/source/opensbi/build/platform/generic/firmware/fw_jump.bin -kernel xuxiake.bin -nographic
