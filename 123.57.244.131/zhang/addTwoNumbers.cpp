#include <vector>
#include <iostream>

using namespace  std;


// namespace  std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


// 遗留问题，int类型能保存的字段有限制。

 struct ListNode {
    int val;
    ListNode *next;
 };

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *l3 = new ListNode;
        l3->val = 0;
        l3->next = NULL;
        int num1 = 0, num2 = 0;
        int n = 1;
        while (l1 != NULL) {
            num1 = num1 + l1->val * (1 * n); 
            n = n * 10;
            l1 = l1->next;
        }
        n = 1;
        while (l2 != NULL) {
            num2 = num2 + l2->val * (1 * n); 
            n = n * 10;
            l2 = l2->next;
        }
        int num3 = num1 + num2;
        int temp = 0;
        ListNode *p = l3;
        temp = num3 % 10;
        num3 = num3 / 10;
        l3->val = temp;
        while(num3 != 0) {
            /* code */
            temp = num3 % 10;
            num3 = num3 / 10;
            ListNode *node = new ListNode;
            node->val = temp;
            p->next = node;
            p = p->next;
        
        }
        return l3;
        

    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}



