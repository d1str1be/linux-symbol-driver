obj-m += scdrv.o
scdrv-y += main.c driver.c buffer.c
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
