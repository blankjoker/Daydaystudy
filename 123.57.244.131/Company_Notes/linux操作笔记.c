

1.抓包的使用：{
	
	sudo tcpdump -i eno1 dst host 192.168.29.70 and port 13400 -w doip_server_log_slow.pcap
	sudo tcpdump -i eno1 dst host 192.168.29.70 and port 13400 -w doip_server_log_fast.pcap
	
	如下例子：抓取网卡eno1的包，并写到文件ifname.pcap
	sudo tcpdump -i eno1 -w ifname.pcap
	
}

2.抓包的查看: {
	
	wireshark doip_server_log66.cap 
	过滤规则：
	ip.src=ip
	ip.dst=ip
	ip.src=ip or ip.dst=ip
	
}

3.linux关闭开启网卡：{
	
	关闭： sudo ifconfig 网卡名字 down                
	启动： sudo ifconfig 网卡名字 up
	如下例子：关掉eno1网卡
	sudo ifconfig eno1 down
	
}

4.打印标准的printf到文件：{
	
	在所有的printf打印之前加上去。
	stdout = freopen("out.txt", "w", stdout)；
	
}

5.ubuntu电脑开启sshd或ssh，使用winscp远程连接：{
	
	sudo service ssh start
	sudo service sshd start
	如果没有开启，则安装
	
}

6.linux瞬速生成一个文件，并可以指定大小：{
	
	dd if=/dev/zero of=send_file.bin bs=10M count=5
	
}

7.查看一个指定进程的cpu占用率：{
	
	ps -ef | grep 进程名字
	top -d 1 -p 进程号
	如看进程号为0303的信息：
	top -d 1 -p 0303
	
}

8.查看windows电脑的信息：{
	
	dxdiag
	
}

9.IPV6中IP地址link和global的配置：{
	
	link：{
		
		fe80::5555:6666:7777:8888  64
	}
	global：{
		
		2400:a480:aaaa:200::159   
		gateway 2400:a480:aaaa:200::1
	}
}

10.ping ipv6的方法：{
	
	ping6 -I 网卡名字  IPV6地址
	如：ping6 -I eno1 fe80::5555:6666:7777:8888
	
}

11.查看电脑是多少位的操作系统：{
	
	uname -a
	uname -m
	
}

12.获取ubuntu终端输出的log并储存在指定文件里面：{
	
	启动：script -a [文件名]
	退出：exit   
	保存的文件在当前运行的目录下。
	如下例子：
	script -a log.txt
}

13.看TCP socket连接数：{
	
	netstat -t
	
}

14.看自己后台运行的程序：{
	
	jobs:查看  程序 & 这种类型.
	bg:执行后台的程序.
	fg：后台调到前台.
	bg / fg 可加编号：
	如: bg 1
}

15.ubuntu下git-gui的安装：{
	
	sudo apt-get install git-gui
	
}

16.logcat的使用：{
	
	logcat | grep doip&
	
	fg
	
	logcat -s doip -v time &
	
	logcat | grep avc &
	
	logcat -s doip &
}

17.repo的使用{
	
	repo forall -c git diff
	
}

18.adb的部分使用方法:{

	查看电脑是否有adb
	1997  which adb
	挂载adb
	1998  adb remount
	关闭adb服务
	1999  sudo adb kill-server
	启动adb服务
	2001  sudo adb devices
	2002  sudo cp /home/zhang/ithing-dipper8/out/host/linux-x86/bin/adb /usr/bin/
	2003  sudo adb devices
	2004  adb remount
	通过adb拉取文件：
	2005  adb push /home/zhang/DoIP_Stack_Stable_5.2/doip_server_config.xml /etc/
	2005  adb pull /etc/ adb push /home/zhang/DoIP_Stack_Stable_5.2/doip_server_config.xml
}

19.系统log查看{
	
	dmesg看系统级别的log
	
}

20.git：{
	
	git打补丁提交方法：
	git commit --amend --no-edit
	
	提交代码：
	git push origin dipper8/master:refs/for/dipper8/master

}
	
21.git删除标签：{
	
	删除远程标签
	然后先删除本地标签
	git tag -d 1.0.0

	然后推送到远程仓库
	git push origin --delete 1.0.0
	
	删除远程分支
	先删除本地分支
	git branch -D branchname
	
	也可以使用：
	git push origin --delete dbg_lichen_star
	这两种方式都可以删除指定的远程分支
	
}

22.linux下修改文件属性：{

	dos2unix -k -n test test.linux

}

23.Vlan的安装与配置：{

	ifconfig eth0:1 192.168.0.3 broadcast 192.168.0.255 netmask 255.255.255.0
	安装vconfig命令：
	apt-get install vlan
	
	给eth0设置1001号VLan

	vconfig add eth0 1001           //添加eth0.1001

	ip address add 192.168.1.101  dev eth0.1001  //设置IP

	ip route add 192.168.1.0/  dev eth0.1001    //设置路由,192.168.1.0网段的从eth0.1001走

	ifconfig eth0.1001 up
	
}

24.makefile加编译选项：{
	
	CFLAGS += -D DEFINE_YUQIANG
	编译的时候定义宏
	CFLAGS += -D ZHANG_TEST
	all:
		gcc ${CFLAGS} make_flag.c -o make_file
		
	gcc -D ZHANG_TEST make_flag.c -o make_file 
	
}

25.使用repo添加分支{
	
	repo start qnx --all
	
}

26.dmesg添加权限的方法：{
	
	dipper项目下的工具：audit2allow
	audit2allow -i 加文件名字
	
}

27.SELinux相关{
	
	logcat -s diagd -v time &

	logcat -s doip -v time &

	logcat -s testdoip -v time &

	//启动SELinux
	setenforce 1

	//关闭SELinux
	setenforce 0
	
	//查看系统相关的log
	dmesg
	
	//用来识别权限命令
	audit2allow -i

}

29.防火墙配置：{
	
	//删除防火墙中白名单的选项
    iptables -t raw -D source_filter -s 255.255.255.255/32 -i vlan51 -j RETURN
	
	//显示防火墙白名单的选项
    iptables -t raw -S
	
	//删除防火墙中白名单的选项
    iptables -t raw -D source_filter -i vlan51 -j RETURN
	
    iptables -t raw -S
	
	//往防火墙中添加白名单选项
    iptables -t raw -I source_filter -s 192.168.50.0/24 -d 255.255.255.255 -i vlan51 -j RETURN

    //查看防火墙的配置
    iptables -t raw -nvL
	
	iptables -F fw_INPUT
	
	iptables -I fw_INPUT -i lo -j RETURN
	
	//关闭防火墙：
	iptables -F

}

30.拉取release分支方法：{
	
	repo init -u ssh://igerrit.storm:29418/Src/iauto-things/manifests -b release分支名
	
}

31.repo介绍：{
	
	repo是一个集中管理git的physon脚本工具。
	主要由两部分组成：
	1、repo脚本集合，主要放在一个git仓库中集中管理。
	2、git项目清单库manifests，存放所有git仓库的路径、名字、数量等。也是用一个git仓库集中管理。
	
}

32.修改文件的最后修改时间：{
	
	touch -m -t 201211112234.50 filename 
	
	将时间设置为2014年6月18日14点16分30秒（MMDDhhmmYYYY.ss）

	date 0618141614.30
	
}

33.查看文件的大小：{
	
	//查看当前目录大小
	du -sh
	
	//查看linux硬盘使用大小
	df -h

}

34.linux下查看程序的依赖库：{
	
	ldd program_name
	
	exe="Vehicle"
	des="/home/zhang/桌面/build-Vehicle-Desktop_Qt_5_3_GCC_64bit-Release/Final_Vehicle"

	deplist=$(ldd $exe | awk '{if (match($3,"/")){ printf("%s "),$3 } }')

	cp $deplist $des
	
	并把相关的库文件复制到指定目录
	
}


35.croot:{
	
	2667  mm -j8 -B
	2668  croot

}

36.windows版本QT发布程序方法：{
	
	1.把release中的程序(exe文件)拷出来放到一个单独的文件夹。
	2.打开电脑开始目录下找到：从开始菜单-->Qt 5.4.0-->5.4-->MinGW 4.9 (32-bit)-->Qt 5.4 for Desktop (MinGW 4.9 32 bit)，可以打开 Qt 命令行
	3.运行该命令：windeployqt  程序名(hello_world.exe)
	
}


37.socket设置read和write超时时间，还有设置阻塞模式：{
	
	这样做在Linux环境下是不会产生效果的，须如下定义：struct timeval timeout = {3, 0}; 
	 //设置发送超时
	setsockopt(socket，SOL_SOCKET,SO_SNDTIMEO，(char *)&timeout,sizeof(struct timeval));
	//设置接收超时
	setsockopt(socket，SOL_SOCKET,SO_RCVTIMEO，(char *)&timeout,sizeof(struct timeval));


	fcntl 函数可以将一个socket 句柄设置成非阻塞模式: 
	flags = fcntl(sockfd, F_GETFL, 0);                       //获取文件的flags值。

	fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);   //设置成非阻塞模式；

	flags  = fcntl(sockfd,F_GETFL,0);

	fcntl(sockfd,F_SETFL,flags&~O_NONBLOCK);    //设置成阻塞模式；

	并在接收和发送数据时:

	将recv, send 函数的最后有一个flag 参数设置成MSG_DONTWAIT

	recv(sockfd, buff, buff_size,MSG_DONTWAIT);     //非阻塞模式的消息发送

	send(scokfd, buff, buff_size, MSG_DONTWAIT);   //非阻塞模式的消息接受
	
}

38.linux下对后台程序的相关操作：{
	
	ctrl^Z：把程序弄到后台挂起，此时会有一个编号。
	bg 编号：把程序放到后台执行。
	jbos：查看后台运行的程序。
	fg：吧程序弄到前台来。
}

39.linux下查找依赖库：{
	
	查找依赖库
	mgrep file
	
}

40.linux下find命令的使用：{
	
	find -name 加名字
	find -type 文件属性(目录还是一般文件) -name “加名字”
	如：find -type f -name "file"
	
}

41.linux下tftp的使用：{
 
	tftp的安装：
	服务器：sudo apt-get install tftpd-hpa
	客户端：sudo apt install tftp
		
	创建 tftp 传输文件夹 
	cd ~ 
	mkdir tftp 
	chmod 777 tftp 
	sudo vim/etc/default/tftpd-hpa
	其中只要修改 TFTP_DIRECTORY 的路径为刚刚上一步骤创建的 tftp 文件夹路径 刚刚我创建的 tftp 文件夹在/disk1/zhuhandong/tftp，那么修改： TFTP_DIRECTORY="/disk1/zhuhandong/tftp"

	sudo service tftpd-hpa restart
	cd ~ 
	sudo tftp localhost 
	tftp > get 123 
	tftp > quit
	
	登录远程服务器：tftp server-ip

	setenv ipaddr 192.168.68.250
	tftp 0x40100000 192.168.68.192:hypervisor-ifs-rcar_m3-graphics.bin
	go 0x40100000
	
	先挂载一下：mount一下挂载的目录
	sudo scp /home/zhang/filepath root@ip:/file
}

42.linux下ln的使用：{
	
	ln -s 源文件  目标文件
	如：ln -s /home/usr/bin/make make-2
	软连接(资源只有一份，改动一边另一边也会改)：ln -s /home/usr/bin/make make-2
	硬链接(资源有两份，两边改动互相影响)：ln /home/usr/bin/make make-2
	
}

43.scp的使用方法：{
	
	sudo scp /home/zhang/filepath root@ip:/file
	
	sudo scp 源文件路径  目标路径
	
	上传本地文件到服务器：
	scp /home/file remove@ip:filepath
	
	拉取远程文件到本地：
	scp remove@ip:filepath /home/file
	
	传输文件夹：(加-r选项)
	scp -r remove@ip:filepath /home/file
}

44.linux下mount的使用：{
	
	mount devices dir
	解析：把devices挂载到dir目录。
	
	fs_spec on fs_file type fs_vfstype (fs_mntopts)
	fs_spec：挂载的块设备或远程文件系统
	fs_file：文件系统的挂载点
	fs_vfstype：文件系统的类型
	fs_mntopts：与文件系统相关的更多选项，不同的文件系统其选项也不太一样
	比如上图中的第一行含义为：挂载的设备为 sysfs，挂载点为 /sys，文件系统的类型为 sysfs。括号中的 rw 表示以可读写的方式挂载文件系统，noexec 表示不能在该文件系统上直接运行程序。
	
	$ sudo mount /dev/sdb1 /mnt
	
}

45.linux查找文件的方法:{
	
	which 　　查看可执行文件的位置。

	whereis 　查看文件的位置。

	locate 　　配合数据库查看文件位置。

	find 　　　实际搜寻硬盘查询文件名称。
	
	如:which adb
	
}

46.sed的使用；{
	
	sed中加双引号才能使用变量$var
	能识别变量： sed -i "N;46a $line_code" makefile
	不能识别变量：sed -i 'N;46a $line_code' makefile
	
	//删除字段DEFINE_YUQIANG的下一行
	sed -i '/DEFINE_YUQIANG/{n;d}' makefile
	
	//插入指定diamante到一行
	sed -i "N;46a $line_code" makefile
	
	//替换指定的字段
	sed -i 's/DEFINE_YUQIANG/makefile/' makefile
	
	// sed匹配某一行开头，替换整行内容
	sed -i "/^CFLAGS = -D NE_DOIP_IPC_PATH/c$line_code" makefile
	
}

47.git中ssh和http免密提交方法：{
	
	安装ssh：sudo apt install ssh 或 sudo  apt install openssh-server
	ssh通信方式免密：
	生成公钥秘钥：ssh-keygen -t rsa -b 4096
	首先 ssh-keygen 会确认密钥的存储位置和文件名（默认是 .ssh/id_rsa）,然后他会要求你输入两次密钥口令，留空即可。所以一般选用默认，全部回车即可。
	接下来我们登陆到GitHub上，右上角小头像->Setting->SSH and GPG keys中，点击new SSH key。
	Title：可以随便填写，但最好起的名字能让自己知道这个公钥是哪个设备的。
	Key：将上面生成的.pub文件中的所有内容复制到这里。
	点击下面的Add SSH key即可。
	然后你就会发现可以免密码访问

	http通信方式免密：
	1.进入git仓库 》 cd .git >> 》》 vim config
	2.修改remote中的url那行如下
	url = https://账号:密码@github.com/地址
	如下例子：
	[remote "origin"]
        url = https://blankjoker:z19961123.@github.com/blankjoker/Company_Notes.git 

}

48.两台linux之间实现免密ssh登录的方法：{

	1.首先确定两台机器都安装了ssh：sudo apt install openssh-server 或sudo apt install ssh
	2.生成ssh公钥密钥：ssh-keygen -t rsa -b 4096
	3.如果是A电脑登陆B电脑，则将A电脑的 id_rsa.pub 复制到 B电脑下，然后执行 cat id_rsa.pub >> .ssh/authorized_keys
	4.设置文件的权限：.ssh文件的权限为700       authorized_keys权限为600

	A/B电脑互相远程登录  反向操作即可。
	
}