
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    static string longestCommonPrefix(vector<string>& strs) {
        if (!strs.size()) {
            return "";
        }
        int length = strs[0].size();
        int len = strs.size();
        for (int i = 0; i < length; i++) {
            char c = strs[0][i];
            for (int j = 1; j < len; j++) {
                if (i == strs[j].size() || strs[j][i] != c) {
                    return strs[0].substr(0, i);
                }
            }
        }
        return strs[0];
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    vector<string> str;
    str.push_back("ssssss");
    str.push_back("ssssss");
    str.push_back("ssssss");
    // vector<string> strs = &str;
    // string stss = Solution::longestCommonPrefix(strs);
    // printf("%s", stss);
    return 0;
}
