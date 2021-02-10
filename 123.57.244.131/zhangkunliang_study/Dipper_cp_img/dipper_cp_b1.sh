#!/bin/bash


basepath=$(pwd)
targetdir="/home/zhang/Dipper_Burning_Tool/uuu_dipper8/file/imx8x-fota"
sourcedir="/home/zhang/ithing-dipper8/out/target/product/dipper8b1"


function cleanfile
{
	echo "clear file is start dipper8b1"

	rm -rf ${targetdir}/bspdata

	rm -rf ${targetdir}/flash.bin

	rm -rf ${targetdir}/system.img

	rm -rf ${targetdir}/uImage+uDTB

	rm -rf ${targetdir}/uImage+uDTB-recovery

	rm -rf ${targetdir}/uramdisk.img

	rm -rf ${targetdir}/uramdisk-recovery.img

	echo "clear file is end dipper8b1"
}

function cpfile
{
	cleanfile
	
	echo "copy file is start dipper8b1"

	cp ${sourcedir}/bspdata   					 ${targetdir}

	cp ${sourcedir}/flash.bin  					 ${targetdir}

	cp ${sourcedir}/system.img       			 ${targetdir}

	cp ${sourcedir}/uImage+uDTB  				 ${targetdir}

	cp ${sourcedir}/uImage+uDTB-recovery         ${targetdir}

	cp ${sourcedir}/uramdisk.img   				 ${targetdir}

	cp ${sourcedir}/uramdisk-recovery.img     	 ${targetdir}

	echo "copy file is end dipper8b1"

	echo "start sync"
	
	sync
}