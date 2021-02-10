
#include <iostream>
using namespace std;
 
class Base
{
public:
    Base()
    {   
        m_p = this;
    }   
    void func() 
    { 
        m_p->print(); 
    }
 
    virtual void print() 
    { 
        cout << "Base" << endl; 
    }
 
    static Base* m_p;
};
 
Base * Base::m_p = NULL;
 
class Derive : public Base
{
public:
    void print() 
    {
        cout << "Derive" << endl;
    }
};
 
int main()
{
    Base *pBase = new Base();
    Base *pDerive = new Derive();
    pBase->func();
    pDerive->func();
    return 0;
}
