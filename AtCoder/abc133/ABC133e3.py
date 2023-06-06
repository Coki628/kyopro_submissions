# -*- coding: utf-8 -*-

"""
参考：https://www.youtube.com/watch?v=8uowVvQ_-Mo
　　　https://img.atcoder.jp/abc133/editorial.pdf
・木DPっぽいけど違う。
・再帰探索で根から決めていく。(葉から決めない)
・木の走査は親に行かないようにだけ気にすれば、訪問フラグいらないんだった。
"""

import sys

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(): return list(map(int, input().split()))
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10 ** 9)
INF = float('inf')
MOD = 10 ** 9 + 7

class FactInvMOD:
    """ 階乗たくさん使う時用のテーブル準備 """

    def __init__(self, MAX, MOD):
        """ MAX：階乗に使う数値の最大以上まで作る """
        
        MAX += 1
        self.MAX = MAX
        self.MOD = MOD

        # 階乗テーブル
        factorial = [1] * MAX
        factorial[0] = factorial[1] = 1
        for i in range(2, MAX):
            factorial[i] = factorial[i-1] * i % MOD
        # 階乗の逆元テーブル
        inverse = [1] * MAX
        # powに第三引数入れると冪乗のmod付計算を高速にやってくれる
        inverse[MAX-1] = pow(factorial[MAX-1], MOD-2, MOD)
        for i in range(MAX-2, 0, -1):
            # 最後から戻っていくこのループならMAX回powするより処理が速い
            inverse[i] = inverse[i+1] * (i+1) % MOD
        self.fact = factorial
        self.inv = inverse
    
    def nCr(self, n, r):
        """ 組み合わせの数 (必要な階乗と逆元のテーブルを事前に作っておく) """
        if n < r: return 0
        # 10C7 = 10C3
        r = min(r, n-r)
        # 分子の計算
        numerator = self.fact[n]
        # 分母の計算
        denominator = self.inv[r] * self.inv[n-r] % self.MOD
        return numerator * denominator % self.MOD

    def nPr(self, n, r):
        """ 順列 """
        if n < r: return 0
        return self.fact[n] * self.inv[n-r] % self.MOD

N,K=MAP()
nodes=[[] for i in range(N)]
for i in range(N-1):
    a,b=MAP()
    nodes[a-1].append(b-1)
    nodes[b-1].append(a-1)

fim=FactInvMOD(max(N, K), MOD)

ans=1
def rec(u, prev):
    global ans
    # 子ノードの数
    cldcnt=len(nodes[u])
    # 根だけは自分と子を両方決める
    if u==0:
        ans*=fim.nPr(K, cldcnt+1)
    # 他は子について決める
    else:
        # 親の分を引く
        cldcnt-=1
        ans*=fim.nPr(K-2, cldcnt)
    ans%=MOD
    for v in nodes[u]:
        if v!=prev:
            rec(v, u)

rec(0, -1)
print(ans)
