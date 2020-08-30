ifneq ($(KERNELRELEASE),)
# For older Kbuild which does not look for Kbuild file first
include Kbuild

else 
# When invoked normally
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD

modules_install: default
	$(MAKE) -C $(KDIR) M=$$PWD modules_install

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
