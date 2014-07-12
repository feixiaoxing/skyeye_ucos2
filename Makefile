

CC=arm-linux-gcc
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy
OBJDUMP=arm-linux-objdump

CFLAGS= -O2 -g
ASFLAGS= -O2 -g
LDFLAGS=-Trtos.lds -Ttext 30000000 

OBJS=   init.o start.o boot.o abnormal.o cpu.o mmu.o print.o interrupt.o \
	ucos_ii.o test_task.o test_sem.o test_mutex.o test_mbox.o test_tmr.o test_queue.o test_mem.o\
	port.o 

.c.o:
	$(CC) $(CFLAGS) -c -I. $<
.s.o:
	$(CC) $(ASFLAGS) -c $<

rtos:$(OBJS)
	$(CC) -static -nostartfiles -nostdlib $(LDFLAGS) $? -o $@ -lgcc
	$(OBJCOPY) -O binary $@ rtos.bin
	$(OBJDUMP) -h -S -D rtos > rtos.txt

clean:
	rm *.o rtos rtos.bin -f
