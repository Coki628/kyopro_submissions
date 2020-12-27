"""
・蟻本演習4-4-3
・貰うDP高速化、スライド最小値
・普通にやるとN^2*Kになって間に合わないのを、遷移のNを高速化するやつ。
　数え上げだと累積和で前計算とかできるけど、min,maxならセグ木使ったりになる。
・これはN*Kで既に計算量が10万*300=3000万あって、ここにセグ木のlogが乗ると、普通は通らない。
　で、そこを線形で処理するスライド最小値を使う。
・最初答え合わなくてあれー？ってなったけど、スライド最小値の実装が、真上からの遷移(何もしない遷移)
　も含むからで、今回はこれを含めたくないので、そのためにスライド最小値から戻ってきた時に
　位置を1つ右にずらしてる。(一番左は-INFで無効にする)
・多分pythonのdequeがそんなに速くないのとかが原因ぽいと思うんだけど、pypyでも通らないのでこの後C++で。
"""

import sys

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for k in range(c)] for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(N=None): return list(MAP()) if N is None else [INT() for i in range(N)]
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10**6)
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

class SegTree:
    """
    セグメント木
    1.update: i番目の値をxに更新する
    2.query: 区間[l, r)の値を得る
    """

    def __init__(self, n, func, intv, A=[]):
        """
        :param n: 要素数(0-indexed)
        :param func: 値の操作に使う関数(min, max, add, gcdなど)
        :param intv: 要素の初期値(単位元)
        :param A: 初期化に使うリスト(オプション)
        """
        self.n = n
        self.func = func
        self.intv = intv
        # nより大きい2の冪数
        n2 = 1
        while n2 < n:
            n2 <<= 1
        self.n2 = n2
        self.tree = [self.intv] * (n2 << 1)
        # 初期化の値が決まっている場合
        if A:
            # 1段目(最下段)の初期化
            for i in range(n):
                self.tree[n2+i] = A[i]
            # 2段目以降の初期化
            for i in range(n2-1, -1, -1):
                self.tree[i] = self.func(self.tree[i*2], self.tree[i*2+1])

    def update(self, i, x):
        """
        i番目の値をxに更新
        :param i: index(0-indexed)
        :param x: update value
        """
        i += self.n2
        self.tree[i] = x
        while i > 0:
            i >>= 1
            self.tree[i] = self.func(self.tree[i*2], self.tree[i*2+1])

    def add(self, i, x):
        self.update(i, self.get(i) + x)

    def query(self, a, b):
        """
        [a, b)の値を得る
        :param a: index(0-indexed)
        :param b: index(0-indexed)
        """
        l = a + self.n2
        r = b + self.n2
        s = self.intv
        while l < r:
            if r & 1:
                r -= 1
                s = self.func(s, self.tree[r])
            if l & 1:
                s = self.func(s, self.tree[l])
                l += 1
            l >>= 1
            r >>= 1
        return s

    def get(self, i):
        """ 一点取得 """
        return self.tree[i+self.n2]

    def all(self):
        """ 全区間[0, n)の取得 """
        return self.tree[1]

    def print(self):
        for i in range(self.n):
            if i == self.n-1:
                print(self.get(i))
            else:
                print(self.get(i), end=' ')

# スライド最小値(比較関数、元の数列、遷移回数、遷移幅、遷移の重み)
def slide_min(func, A, k, w=1, v=0):
    from collections import deque

    N = len(A)
    res = A[:]
    for a in range(w):
        que = deque()
        i = 0
        while i*w+a < N:
            val = A[i*w+a] - i*v
            while que and func(que[-1][1], val) == val:
                que.pop()
            que.append((i, val))
            res[i*w+a] = que[0][1] + i*v
            if que[0][0] == i-k:
                que.popleft()
            i += 1
    return res

N, M, K = MAP()
A = LIST()

# dp = list2d(K+1, N, -INF)
# for i in range(N):
#     dp[1][i] = A[i]
# for i in range(2, K+1):
#     for j in range(N):
#         for k in range(max(j-M, 0), j):
#             dp[i][j] = max(dp[i][j], dp[i-1][k] + A[j]*i)
# ans = max(dp[K])
# print(ans)

# seg = SegTree(N, max, -INF, A)
# for i in range(2, K+1):
#     for j in range(N-1, -1, -1):
#         mx = seg.query(max(j-M, 0), j)
#         seg.update(j, mx + A[j]*i)
# ans = seg.all()
# print(ans)

dp = [0] * N
for i in range(N):
    dp[i] = A[i]
for i in range(2, K+1):
    dp = [-INF] + slide_min(max, dp[:-1], M-1, 1)
    for j in range(i-1, N):
        dp[j] += A[j]*i
ans = max(dp)
print(ans)
