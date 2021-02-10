

#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;

// namespace LL{
//     class Solution;
// }

class Solution {
public:
    int removeDuplicates(vector<int>& nums)
    {
        if (!nums.size()) {
            return 0;
        }
        int i = 0;
        for (int j = 0; j < nums.size(); j++) {
            if (nums[i] != nums[j]) {
                i++;
                nums[i] = nums[j];
            }
        }
        
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
