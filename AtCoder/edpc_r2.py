"""
・ゆきこで類題が出たので復習。
・行列累乗、グラフ
・蟻本でこれやった時は、なんでこれでいいのかよく分からなかったけど、今はあの時より分かる。
　頂点iから頂点jに遷移できるか、が隣接行列には全部書いてあるから、そのままK回掛ければいいんだね。
　遷移がN個あるDPみたいな。
・となると、行列累乗のセオリー的には初期値の列があってそれに遷移行列をK回掛けるみたいにやるから、
　初期値の列は今回で言うなら、パスの総数だから出発点はどの頂点でもよくて、全部1の列だな、となる。
・投げてみたけどちゃんとAC。よかった。
・今回は(多分)全部の頂点から出発できるからいいけど、本当は隣接行列から行列逆にしないと、
　行列の遷移の向き的にダメっぽい。一応その処理も入れて再度AC。
"""

import sys

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for j in range(c)] for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(N=None): return list(MAP()) if N is None else [INT() for i in range(N)]
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10**9)
INF = 10**18
MOD = 10**9 + 7

def mat_pow(mat, init, K, MOD):
    """ 行列累乗 """

    def mat_dot(A, B, MOD):
        """ 行列の積 """

        if not isinstance(A[0], list) and not isinstance(A[0], tuple):
            A = [A]
        if not isinstance(B[0], list) and not isinstance(A[0], tuple):
            B = [[b] for b in B]
        n1 = len(A)
        n2 = len(A[0])
        _ = len(B)
        m2 = len(B[0])
        res = list2d(n1, m2, 0)
        for i in range(n1):
            for j in range(m2):
                for k in range(n2):
                    res[i][j] += A[i][k] * B[k][j]
                    res[i][j] %= MOD
        return res

    def _mat_pow(mat, k, MOD):
        """ 行列matをk乗する """

        n = len(mat)
        res = list2d(n, n, 0)
        for i in range(n):
            res[i][i] = 1
        while k > 0:
            if k & 1:
                res = mat_dot(res, mat, MOD)
            mat = mat_dot(mat, mat, MOD)
            k >>= 1
        return res

    res = _mat_pow(mat, K, MOD)
    res = mat_dot(res, init, MOD)
    return [a[0] for a in res]

N, K = MAP()
G = [[]] * N
for i in range(N):
    G[i] = LIST()
G = [list(row) for row in list(zip(*G))]
# init[i] := 移動開始前に頂点iにいる通り数
init = [1] * N

# res[i] := K回移動後に頂点iにいる通り数
res = mat_pow(G, init, K, MOD)
ans = 0
for i in range(N):
    ans += res[i]
    ans %= MOD
print(ans)
