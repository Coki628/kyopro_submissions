"""
・きっちり自力AC！
・この手のcapitalizeとか文字列操作は絶対Pythonが楽だよね。
"""

class Solution:
    def capitalizeTitle(self, title: str) -> str:
        ans = []
        for word in title.split(' '):
            if len(word) <= 2:
                ans.append(word.lower())
            else:
                ans.append(word.capitalize())
        ans = ' '.join(ans)
        return ans
