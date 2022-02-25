
CROSS_COMPILE ?= riscv64-unknown-elf-

CFLAGS=-Wall
all:
	${CROSS_COMPILE}gcc -c -mcmodel=medany -march=rv64imafdc -mabi=lp64d -x assembler-with-cpp -ggdb -c -o head.o head.S -D__ASSEMBLY__ ${CFLAGS}
	${CROSS_COMPILE}gcc -c -mcmodel=medany -march=rv64imafdc -mabi=lp64d -ggdb -c -o cpu_entry.o cpu_entry.c -nostdlib ${CFLAGS}
	${CROSS_COMPILE}gcc -c -mcmodel=medany -march=rv64imafdc -mabi=lp64d -ggdb -c -o lib.o lib.c -nostdlib ${CFLAGS}
	${CROSS_COMPILE}gcc -c -mcmodel=medany -march=rv64imafdc -mabi=lp64d -ggdb -c -o gpio.o gpio.c -nostdlib ${CFLAGS}
	${CROSS_COMPILE}gcc -o xuxiake.elf -mcmodel=medany -march=rv64imafdc -mabi=lp64d -nostartfiles -Wl,--gc-sections,-Map=xuxiake.map,-cref,-u,_start -T link.lds head.o cpu_entry.o gpio.o lib.o ${CFLAGS}
	${CROSS_COMPILE}objcopy -O binary xuxiake.elf xuxiake.bin ${CFLAGS}

qemu:
	qemu-system-riscv64 -M virt -m 512M -smp 1 -bios ${BUILDROOT_OUTPUT}/images/fw_jump.bin -kernel xuxiake.bin -nographic
