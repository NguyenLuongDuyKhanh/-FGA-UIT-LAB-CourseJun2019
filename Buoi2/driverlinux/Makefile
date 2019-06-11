obj-m += src/hello-1.o
testing = /home/khanh/Desktop/Workingzone/driverlinux/src/hello-c.c

all1:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	mv ./src/*.ko ./bin


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
