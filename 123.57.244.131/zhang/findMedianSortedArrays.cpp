

#include <stdio.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int num = nums1.size() + nums2.size();
        if (num < 0 || num > 2000) {
            return 0;
        }
        if (nums1.size() < 0 || nums1.size() > 1000) {
            return 0;
        }
        if (nums2.size() < 0 || nums2.size() > 1000) {
            return 0;
        }
        vector<int> obj;
        int i = 0;
        for (i = 0; i < nums1.size(); i++) {
            obj.push_back(nums1[i]);
        }
        for (int j = 0; j < nums2.size(); j++) {
            obj.push_back(nums2[j]);
        }
        sort(obj.begin(), obj.end());
        if ((obj.size() % 2) == 1) {
            return (double)obj[obj.size() / 2];
        }
        else {
            return (double)(obj[obj.size() / 2]  + obj[(obj.size() / 2) - 1]) / 2;
        }
    }
};

class Solution;
int main(int argc, char const *argv[])
{
    /* code */
    Solution *my = new Solution();
    vector<int> a;
    a.push_back(1);
    a.push_back(2);

    printf("sssssssssssssssssssssssssssssss = 1\n");
    vector<int> b;
    b.push_back(3);
    b.push_back(4);

    double num = my->findMedianSortedArrays(a, b);
    printf("numbers is = %lf\n", num);
    free(my);
    return 0;
}
