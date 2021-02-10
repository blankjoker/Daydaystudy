

#include <stdio.h>

class _myconst
{
private:
    /* data */
    int a;
public:
    _myconst(/* args */);
    ~_myconst();
    int test() const
    {
        int b;
        b = 12;
        // a = 10;
        return a;
    }
};

_myconst::_myconst(/* args */)
{
}

_myconst::~_myconst()
{
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
