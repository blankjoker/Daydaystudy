
// #include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        int i = 0;
        int j = 0;
        int n = 0;
        vector<int> num;
        for (i = 0; i < nums.size(); i++) {
            for (j = 0; j < nums.size(); j++) {
                if ( (i != j) && (nums[i] < nums[j])) {
                    n++;
                }
            }
            num.push_back(n);
            n = 0;
        }
        return num;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
