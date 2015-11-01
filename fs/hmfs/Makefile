ccflags-y += -DCONFIG_DEBUG
obj-m += hmfs.o
hmfs-objs := super.o debug.o node.o inode.o checkpoint.o file.o data.o namei.o segment.o hash.o dir.o symlink.o gc.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean


hmfs_300M_2G:
	sudo mount -t hmfs -o physaddr=0x80000000,init=140M none ~/hmfsMount/
ins_print:
	sudo insmod $(PRINTPATH)/printt.ko
rm_print:
	sudo rmmod printt
ins_hmfs:
	sudo insmod ./hmfs.ko 
rm_hmfs:
	sudo rmmod hmfs
mount_hmfs:
	sudo mount -t hmfs -o physaddr=0x70000000,init=40M none ~/hmfsMount/
hmfs:
	sudo insmod ./hmfs.ko && sudo mount -t hmfs -o physaddr=0x70000000,init=40M none ~/hmfsMount/
nohmfs:
	sudo umount ~/hmfsMount && sudo rmmod hmfs

reset_hmfs:
	make nohmfs
	make hmfs


wrong_hmfs:
#	sudo mount -t phmfs -o physaddr=0x80000000,init=298M none ~/hmfs/
	sudo insmod ./hmfs.ko && sudo mount -t hmfs -o physaddr=0x100000000,init=40M none ~/hmfs/

