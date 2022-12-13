"""
・自力AC！
・mapでDP
・最初、無益な貪欲方針で突っ込んで撃沈。とりあえずF通して戻ってきて再考。
・問題設定になんか見覚え。探した。ABC182Fの数え上げを最適化に書き直すと通る。
　このDPやった時難しくて、upsolveでコメントいっぱい書いてたから解読が比較的早くて助かった。
　今でも自力では導けなそう…。
"""

import sys
from collections import defaultdict

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for k in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for k in range(c)] for k in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(N=None): return list(MAP()) if N is None else [INT() for i in range(N)]
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10**9)
INF = 10**19
MOD = 10**9 + 7
EPS = 10**-10

N, X = MAP()
A  = LIST()

# 大きい単位から見る
A.reverse()
# dp[i][j] := i番目まで見て、Xとの差額がjの時の最小枚数
dp = [defaultdict(lambda: INF) for i in range(N)]
# 少なめorぴったりに払う
x = X % A[0]
dp[0][x] = X // A[0]
# 多めに払う
x = X % A[0] - A[0]
if abs(x) < A[0]:
    dp[0][x] = X // A[0] + 1
for i in range(1, N):
    for k, v in dp[i-1].items():
        # modの挙動を考慮して負数は場合分け
        if k >= 0:
            # 少なめorぴったりに払う
            x = k % A[i]
            cnt = k // A[i]
            # この単位で払う額が前の単位より小さいことが条件
            if abs(x-k) < A[i-1]:
                dp[i][x] = min(dp[i][x], v+cnt)
            # 多めに払う
            x = k % A[i] - A[i]
            cnt = k // A[i] + 1
            if abs(x-k) < A[i-1]:
                dp[i][x] = min(dp[i][x], v+cnt)
        else:
            # mod取る前に正の数にする
            k = abs(k)
            x = k % A[i]
            cnt = k // A[i]
            if abs(x-k) < A[i-1]:
                # キーにする時、正負を戻す
                dp[i][-x] = min(dp[i][-x], v+cnt)
            x = k % A[i] - A[i]
            cnt = k // A[i] + 1
            if abs(x-k) < A[i-1]:
                dp[i][-x] = min(dp[i][-x], v+cnt)
# 全部終わって収支が合っている最小枚数
ans = dp[-1][0]
print(ans)
