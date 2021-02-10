#include<iostream>
using namespace std;
class Myclass
{
private:
	int m;
	static int n;
	
public:
	Myclass();
	int test();
	static int getn(Myclass a);

};

Myclass::Myclass()
{
	m = 10;
}

int Myclass::getn(Myclass a)
{
	cout << a.m << endl;
	cout << a.test() << endl;
	return n; 
}

int Myclass::test()
{
	cout << "tstttttttttt" << endl;
	// return 9;
}

int Myclass::n = 100;

int main()
{
	Myclass app1;
	cout << app1.getn(app1) << endl;
	// cout << Myclass::getn(app1) << endl;
	return 0;
}