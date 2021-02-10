
1.更新源：{

	sudo apt-get update
}

2.更新列表：{

	sudo add-apt-repository ppa:git-core/ppa //添加源
	sudo apt-get update
	sudo apt-get install git
}

3.配置用户信息：{

   git config --global user.email "you@example.com" 
   git config --global user.name "Your Name"
}

4.生成秘钥：{

	ssh-keygen -t rsa
}

5.登录igreet添加ssh秘钥：{

	点击网页右上角登录名，在弹出的页面中点击Settings
	点击左侧的SSH Public Keys，进入用户ssh key配置页面 
	在Add SSH Public Key下面空白的编辑区内中拷贝本机的ssh public key（默认是 ~/.ssh/id_rsa.pub）中的内容，点击输入框下的Add按钮。
}


6.在.ssh下创建config文件：{

	输入 user lijialin 并保存
	或者：
	{
		Host iauto
		Hostname review.iauto.net
		IdentityFile ~/.ssh/id_rsa
		User zhangkunliang
		Port 29418

		Host igerrit.storm
		Hostname igerrit.storm
		IdentityFile ~/.ssh/id_rsa
		User zhangkunliang
	}
}

7.检测秘钥是否生成：{
	
	ssh -p 29418 igerrit.storm

	****    Welcome to Gerrit Code Review    ****

	Hi liulin liulin, you have successfully connected over SSH.

	Unfortunately, interactive shells are disabled.
	To clone a hosted Git repository, use:

	git clone ssh://liulin@igerrit:29418/REPOSITORY_NAME.git

	Connection to igerrit closed.
}


//可有可无
8.获取repo：{

   git clone ssh://igerrit.storm:29418/tools/repo.git
   cd repo
   git checkout -b stable origin/stable
   sudo ln repo /usr/bin/repo
}

9.取代吗：{
	
   repo init -u ssh://igerrit.storm:29418/Src/iAutoPlatform/iAuto3/manifest
   repo sync -c --no-tags
   创建一个集体分支：repo start --all 分支名
}
   
10.安装扩展程序：
(1)安装git lfs手顺
git config --global ssh.variant ssh
curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | sudo bash
sudo apt-get install git-lfs
cd <任意git仓库>
git lfs install

