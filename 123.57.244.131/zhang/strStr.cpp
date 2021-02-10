
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }
        size_t pos = haystack.find(needle);
        if (pos != string::npos) {
            return (int)pos;
        }
        else {
            return -1;
        }
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    Solution my;
    string str1 = "hello";
    string str2 = "ll";
    cout << "pos is = " << my.strStr(str1, str2) << endl;
    return 0;
}
