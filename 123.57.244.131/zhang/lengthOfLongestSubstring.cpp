
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
// #include <unordered_set>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<char> seen;
        int str_num_max = 0;
        if (s.empty()) {
            return 0;
        }
        vector<char>::iterator result1;
        cout  << "string len is : " << s.length() << endl;
        for (int i = 0; i < s.length(); i++) {
            seen.push_back(s[i]);
            for (int j = i + 1; j < s.length(); j++) {
                if (s[i] != s[j]) {
                    result1 = find(seen.begin(), seen.end(), s[j]);
                    if (result1 == seen.end()) {
                        seen.push_back(s[j]);
                    }
                    else {
                        break;
                    }
                }
               else {
                    break;
                } 
            }
            if (seen.size() > str_num_max) {
                str_num_max = seen.size();
            }
            seen.clear();
        }
        return str_num_max;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    string str = "qwedgbisdagiaufhaiosdufoadshfNOSIfjbaioshfPOAIFOISOihsoaidfhidfjoiasjfjdfa[jogadi[jgdajg";
    Solution *my = new Solution();
    printf("max string sub is num is = %d\n", my->lengthOfLongestSubstring(str));
    free(my);
    return 0;
}
