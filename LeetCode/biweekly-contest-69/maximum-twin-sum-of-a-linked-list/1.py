"""
・なんとか自力AC
・Linked List
・りとこはこれがあるって聞いたことあったやつだね。
　勝手が分からなくて、色々調べたり時間かかってしまった…。
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def pairSum(self, head: Optional[ListNode]) -> int:
        li = []
        while head:
            li.append(head.val)
            head = head.next
        N = len(li)
        ans = 0
        for i in range(N//2):
            ans = max(ans, li[i]+li[N-i-1])
        return ans
