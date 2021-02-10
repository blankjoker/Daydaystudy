#!/bin/bash


basepath=$(pwd)
targetdir="/home/zhang/liguoqiang/DoipEquip/"
sourcedir="/home/zhang/kaido_new_an/libdoipstack/"


function cleanfile
{
	echo "************cleanfile************************************"
	echo "************cleanfile* ne_doip_comm_def.h ***************"
	rm -rf ${targetdir}/ne_doip_comm_def.h
	echo "************cleanfile* ne_doip_connection.h *************" 
	rm -rf ${targetdir}/ne_doip_connection.h
	echo "************cleanfile* ne_doip_def.h ********************" 
	rm -rf ${targetdir}/ne_doip_def.h 
	echo "************cleanfile* ne_doip_event_loop.h *************"
	rm -rf ${targetdir}/ne_doip_event_loop.h
	echo "************cleanfile* ne_doip_os.h *********************" 
	rm -rf ${targetdir}/ne_doip_os.h 
	echo "************cleanfile* ne_doip_test_equip.h *************"
	rm -rf ${targetdir}/ne_doip_test_equip.h
	echo "************cleanfile* ne_doip_thread.h *****************"
	rm -rf ${targetdir}/ne_doip_thread.h
	echo "************cleanfile* ne_doip_util.h *******************"
	rm -rf ${targetdir}/ne_doip_util.h
	echo "************cleanfile* libnedoipstackclient.so **********"
	rm -rf /home/zhang/liguoqiang/build-DoipEquip-Desktop_Qt_5_3_GCC_64bit-Debug/libnedoipstackclient.so 
}

function cpfile
{
	cleanfile
	
	echo "************cpfile = ne_doip_comm_def.h *************"	
	cp ${sourcedir}/ne_doip_comm_def.h    				 ${targetdir}
	echo "************cpfile = ne_doip_connection.h ***********"	
	cp ${sourcedir}/ne_doip_connection.h  				 ${targetdir}
	echo "************cpfile = ne_doip_def.h*******************"	
	cp ${sourcedir}/ne_doip_def.h        				 ${targetdir}
	echo "************cpfile = ne_doip_event_loop.h ***********"	
	cp ${sourcedir}/ne_doip_event_loop.h  				 ${targetdir}
	echo "************cpfile = ne_doip_os.h *******************"	
	cp ${sourcedir}/ne_doip_os.h           				 ${targetdir}
	echo "************cpfile = ne_doip_test_equip.h ***********"	
	cp ${sourcedir}/ne_doip_test_equip.h   				 ${targetdir}
	echo "************cpfile = ne_doip_thread.h  **************"	
	cp ${sourcedir}/ne_doip_thread.h      				 ${targetdir}
	echo "************cpfile = ne_doip_util.h *****************"	
	cp ${sourcedir}/ne_doip_util.h       			 	 ${targetdir}
	echo "************cpfile = libnedoipstackclient.so ********"	
	cp /home/zhang/kaido_new_an/bin/Debug/libnedoipstackclient.so     /home/zhang/liguoqiang/build-DoipEquip-Desktop_Qt_5_3_GCC_64bit-Debug/
}