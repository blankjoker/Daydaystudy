



1.针对dipper项目，PC向板子发送单播数据，板子无法收到问题。(原因是端口号不对，板子监听的端口号是13400。但是如果直接改发送信息时候的端口号，会影响power mode的机能，power mode需要根据IP和PORT寻找fd往上发数据。)
解决方案：再创建一个监听UDP数据的fd。

2.现在为了测试UDP的数据，发送的目的端口指定为13400。代码测试结束后需要改回来。

3.tcp建立连接的时候，目标端口为指定的13400，现在实装的代码是有问题的。

4.针对dipper项目，存在双网卡，发送UDP信息的时候，车辆公告，对内对外是否都要发送车辆公告？

5.针对dipper项目，当CGW只存在一个逻辑地址的时候
{
	if (找到逻辑地址 && entity_type是gateway) {
		设置find_flag = NE_DOIP_FALSE;
		走诊断MCU的分支
	}
}

error code：113, message:No route to host {
 server和client连接的时候，拔掉网线，历经10~15分钟左右(client)出现这个错误code。
}

errno32 : Broken pipe{
 server和client连接的时候，server端关闭，client端继续发数据的情况下出现这个错误ode。
}

errno104 : Connection reset by peer{
 server和client连接的时候，拔掉网线，重启server端，client再发数据的时候，出现这个错误code。
}


QNX平台的东西：
x86_64-generic.build
line 249
## doip add bin
[uid=0 gid=0 perms=0755] /usr/bin/diagd=diagd
line 273
## doip add lib
[uid=0 gid=0 perms=0755] /usr/lib/libncore.so=libncore.so
[uid=0 gid=0 perms=0755] /usr/lib/libnedoipstackclient.so=libnedoipstackclient.so
[uid=0 gid=0 perms=0755] /usr/lib/libnedoipstackserver.so=libnedoipstackserver.so

Warning	  2102 at (-1,-1): Could not open C:\Users\zhang\Program Files\Vector CANoe 11.0\Exec32\Ethernet_IL.dll, 找不到指定的模块。  .	DoIP-test.can

repo init -u ssh://igerrit.storm:29418/Src/iauto-things/manifests -b iautothings/master -m v2x.xml

repo init -u ssh://igerrit.storm:29418/Src/iAutoPlatform/iAuto3/manifest -b iauto3/demo/kaido_poc

1.doip stack 目前需要获取如下基本信息：
1).车辆VIN、EID、GID基本编号信息。
2).Activation line是否插入或是否准备好。
3).power mode的ready 或 not ready状态，如果是指edge gateway的状态(是否可以诊断自身)。
4).网卡是否准备好的信息，用于发送车辆公告。


2.以上信息，是否可通过环境变量获取？或通过service之间通信获取？

3.如果是通过环境变量获取，那么是否不需要handler处理了？


28.QNX平台相关操作：{
	
	http://iautowiki.storm:8082/QNX/develop-manual/dev-env
	
	https://wzt.ac.cn/2019/09/10/QEMU-networking/
		
	https://wzt.ac.cn/2019/09/10/QEMU-networking/
	
	logcat | grep -i SELinux

	cd　hardware/bsp/jbn8/x86_64/images

	make usbimage

	qemu-system-x86_64 -usb -usbdevice keyboard -hdb data.qcow2 -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::5559-:22 usb.img
	
	ssh qnxuser@localhost -p 5559
	
	scp -P 5559 /home/zhuangyao/bin/dtc qnxuser@localhost:/home/qnxuser/
	
	//release路徑
	\\uranus.storm\ibigmanny\XCU\Release\master\test_xcu09_9_xcu_rcar_m3-eng_20191105\xcu_rcar_m3-eng_for_developer
}


IMX8：repo init -u ssh://igerrit.storm:29418/Src/iauto-things/manifests -b iautothings/master -m v2x.xml
AG35：repo init -u ssh://igerrit.storm:29418/Src/iauto-things/manifests -b iautothings/master -m tcu.xml
M3：repo init -u ssh://igerrit.storm:29418/Src/iAutoPlatform/iAuto3/manifest -b iauto3/demo/kaido_poc

