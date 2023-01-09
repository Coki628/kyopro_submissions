"""
参考：https://qiita.com/FumioNonaka/items/c146420c3aeab27fc736
・なんとか自力AC！
・幾何、三角関数
・題意を読み解くと、2点の中心を取ればそこが図形の中心であり、
　そこを軸にして、何角形なのかによって角度を決めて点1から回転させれば、
　目的の座標が分かる。座標と角度から、回した後の座標を求める必要があるので、
　「角度 座標 求め方」で検索した。使えそうなのがすぐ出てよかった…。
・あとは書いてある通りに当てはめればいい。数学O(1)だ。
"""

import sys
from math import cos, sin, radians

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

N = INT()
x1, y1 = MAP()
x2, y2 = MAP()

center_x = (x1+x2)/2
center_y = (y1+y2)/2
ansx = (x1-center_x)*cos(radians(360/N)) - (y1-center_y)*sin(radians(360/N)) + center_x
ansy = (x1-center_x)*sin(radians(360/N)) + (y1-center_y)*cos(radians(360/N)) + center_y
print(ansx, ansy)
