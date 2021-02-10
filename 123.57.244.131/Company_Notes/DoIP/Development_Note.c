
语法笔记

1.C++中静态成员(静态变量，静态函数)访问非静态成员的方法：{
	
	1.在访问静态方法的时候，传入一个对象，通过对象调用非静态方法。
	2.通过静态对象在静态方法中访问非静态方法。(在静态方法中通过静态对象调用非静态方法)
}

2.在开发中编译的时候；{
	
	注意要加上gcc(g++) -Wall
	不加的话，有些警告不会报出。
}

3.采用TCP协议的客户端和服务器，当一方close(fd)的时候，另一方会收到的异常code：{
	code ：0
	code string ：Success
}

4.C++中采用的事件传输机制：{
	
	1.提供一个Server类，该类具有注册Register监听事件类和取消注册unRegister事件类两个函数。
	class Server{
		Register(Listen &l)
		unRegister(Listen &l)
	}
	2.提供一个监听listener类，里面的函数是相关的事件函数。
	class Listen{
		A();
		B(};
		C();
	}
	3.需要获取事件方，实现listener类，并创建server对象，把listener注册进去。
	class Listen_Event : public Listen{
		A(){xxx}
		B(}{xxx}
		C(){xxx}	
	}
	Listen_Event my_event;
	Server my_server
	void main() 
	{
		my_server.Register(my_server);
	}

}
