#!/bin/bash

function xcu
{
	cd /home/zhang/XCU
	source build/envsetup.sh
	lunch 1
	make clean
	make -j8
	cd /home/zhang/XCU/hardware/bsp/jbn8/x86_64/images
	make usbimage
	{qemu-system-x86_64 -usb -usbdevice keyboard -hdb data.qcow2 -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::5559-:22 usb.img} &
	ssh qnxuser@localhost -p 5559
}
