
ARCH ?= arm64
#/home/bamvor/works/source/buildroot/output/host/bin/
CROSS_COMPILE ?= aarch64-linux-
#ARCH ?= riscv
#CROSS_COMPILE ?= riscv64-unknown-elf-

#CFLAGS=-Wall -c -mcmodel=medany -march=rv64imafdc -mabi=lp64d
#CFLAGS=-Wall -c -mcmodel=medany -march=rv64imafdc -mabi=lp64d
CFLAGS=-Wall -I. -Iarch/${ARCH}/include -DDEBUG
all:
	${CROSS_COMPILE}gcc  -x assembler-with-cpp -ggdb -c -o arch/${ARCH}/head.o arch/${ARCH}/head.S -D__ASSEMBLY__ ${CFLAGS}
	${CROSS_COMPILE}gcc -ggdb -c -o cpu_entry.o cpu_entry.c -ffreestanding ${CFLAGS}
	${CROSS_COMPILE}gcc -ggdb -c -o lib.o lib.c -ffreestanding ${CFLAGS}
	${CROSS_COMPILE}gcc -ggdb -c -o arch/${ARCH}/lib.o arch/${ARCH}/lib.c -ffreestanding ${CFLAGS}
	${CROSS_COMPILE}gcc -ggdb -c -o arch/${ARCH}/cpu_entry.o arch/${ARCH}/cpu_entry.c -ffreestanding ${CFLAGS}
	${CROSS_COMPILE}gcc -ggdb -c -o arch/${ARCH}/print.o arch/${ARCH}/print.c -ffreestanding ${CFLAGS}
#	${CROSS_COMPILE}gcc -ggdb -c -o gpio.o gpio.c -ffreestanding ${CFLAGS}
#	${CROSS_COMPILE}gcc -o xuxiake.elf -nostartfiles -Wl,--gc-sections,-Map=xuxiake.map,-cref,-u,_start -T arch/${ARCH}/link.lds head.o cpu_entry.o gpio.o lib.o ${CFLAGS}
	${CROSS_COMPILE}gcc -o xuxiake.elf -nostartfiles -Wl,--gc-sections,-Map=xuxiake.map,-cref,-u,_start -T arch/${ARCH}/link.lds arch/${ARCH}/head.o arch/${ARCH}/lib.o arch/${ARCH}/cpu_entry.o arch/${ARCH}/print.o lib.o cpu_entry.o ${CFLAGS}
	${CROSS_COMPILE}objcopy -O binary xuxiake.elf xuxiake.bin
	${CROSS_COMPILE}objdump -Sx xuxiake.elf > xuxiake.S

qemu:
	#qemu-system-riscv64 -M virt -m 512M -smp 1 -bios ${BUILDROOT_OUTPUT}/images/fw_jump.bin -kernel xuxiake.bin -nographic
	qemu-system-aarch64 -M virt -cpu cortex-a72 -m 512M -smp 1 -kernel xuxiake.bin -nographic ${DEBUG}
