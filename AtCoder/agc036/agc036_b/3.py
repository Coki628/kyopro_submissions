"""
・ダブリングの挙動確認。
　この問題、特殊な遷移かと思ったけど、普通に行先と和を持つダブリングでいけるらしいようなので試した。
　無事、問題なくAC。
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
sys.setrecursionlimit(10 ** 9)
INF = float('inf')
MOD = 10 ** 9 + 7

N, K = MAP()
A = LIST()

# 各値毎の出現位置
B = [[] for i in range(max(A)+1)]
for i, a in enumerate(A+A):
    B[a].append(i)
# 同値が何個先で出現するかを保持する
C = [0] * N
for li in B:
    for i in range(len(li)-1):
        if li[i] >= N:
            break
        C[li[i]] = li[i+1] - li[i]

# nxt[k][i] := iからスタートして、2^kブロック移動後の現在位置
nxt = list2d(61, N, 0)
sm = list2d(61, N, 0)
# 初期化
for i in range(N):
    # iからのスタートは、1(2^0)回目はC[i]+1先に進む
    nxt[0][i] = (i+C[i]+1)%N
    sm[0][i] = C[i]+1
# ダブリングのテーブル構築
for k in range(1, 61):
    for i in range(N):
        nxt[k][i] = nxt[k-1][nxt[k-1][i]]
        sm[k][i] = sm[k-1][i] + sm[k-1][nxt[k-1][i]]
    # N*Kより大きい値は1ブロックしか使う必要がないので、その先はやらない
    if min(nxt[k]) > N*K:
        break

# N*K以内でギリギリまで現在位置を進める
def get_cur():
    i = cur = 0
    while True:
        for k in range(61):
            if cur + sm[k][i] > N * K:
                if k != 0:
                    cur += sm[k-1][i]
                    i = nxt[k-1][i]
                    break
                else:
                    return cur
cur = get_cur()

# 最後のブロックについてシミュレーションする
ans = []
s = set()
for i in range(cur, N*K):
    a = A[i%N]
    # 追加
    if a not in s:
        ans.append(a)
        s.add(a)
    # 削除
    else:
        # aが来るまで遡って削除する
        while True:
            key = ans.pop()
            s.remove(key)
            if key == a:
                break
print(*ans)
