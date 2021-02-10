"""
・なんとか自力AC！
・幾何、円と直線の交点
・色々バグらせたりで時間かかったー。
　最初、(x2,y2)を範囲に含めるのかと誤読。含めないような円の最大化ね。。
・あと、(x1,y1) == (x2,y2) にゼロ除算が発生して場合分けね。
・それ以外にもx1とy1書き間違えててWAになったり、やっぱ朝は頭働いてないね。。
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
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

class Geometry:

    def __init__(self, EPS):
        self.EPS = EPS

    def add(self, a, b):
        x1, y1 = a
        x2, y2 = b
        return (x1+x2, y1+y2)

    def sub(self, a, b):
        x1, y1 = a
        x2, y2 = b
        return (x1-x2, y1-y2)

    def mul(self, a, b):
        x1, y1 = a
        if not isinstance(b, tuple):
            return (x1*b, y1*b)
        x2, y2 = b 
        return (x1*x2, y1*y2)

    def div(self, a, b):
        x1, y1 = a
        if not isinstance(b, tuple):
            return (x1/b, y1/b)
        x2, y2 = b
        return (x1/x2, y1/y2)

    def abs(self, a):
        from math import hypot
        x1, y1 = a
        return hypot(x1, y1)

    def norm(self, a):
        x, y = a
        return x**2 + y**2

    def dot(self, a, b):
        x1, y1 = a
        x2, y2 = b
        return x1*x2 + y1*y2

    def cross(self, a, b):
        x1, y1 = a
        x2, y2 = b
        return x1*y2 - y1*x2

    def project(self, seg, p):

        p1, p2 = seg
        base = self.sub(p2, p1)
        r = self.dot(self.sub(p, p1), base) / self.norm(base)
        return self.add(p1, self.mul(base, r))

    def reflect(self, seg, p):

        return self.add(p, self.mul(self.sub(self.project(seg, p), p), 2))

    def ccw(self, p0, p1, p2):

        a = self.sub(p1, p0)
        b = self.sub(p2, p0)
        if self.cross(a, b) > self.EPS: return 1
        if self.cross(a, b) < -self.EPS: return -1
        if self.dot(a, b) < -self.EPS: return 2
        if self.norm(a) < self.norm(b): return -2
        return 0

    def intersect(self, seg1, seg2):

        p1, p2 = seg1
        p3, p4 = seg2
        return (
            self.ccw(p1, p2, p3) * self.ccw(p1, p2, p4) <= 0
            and self.ccw(p3, p4, p1) * self.ccw(p3, p4, p2) <= 0
        )

    def get_distance_PP(self, p1, p2):
        from math import hypot

        x1, y1 = p1
        x2, y2 = p2
        return hypot(x1-x2, y1-y2)

    def get_distance_LP(self, line, p):

        p1, p2 = line
        return abs(self.cross(self.sub(p2, p1), self.sub(p, p1)) / self.abs(self.sub(p2, p1)))

    def get_distance_SP(self, seg, p):

        p1, p2 = seg
        if self.dot(self.sub(p2, p1), self.sub(p, p1)) < 0: return self.abs(self.sub(p, p1))
        if self.dot(self.sub(p1, p2), self.sub(p, p2)) < 0: return self.abs(self.sub(p, p2))
        return self.get_distance_LP(seg, p)

    def get_distance_SS(self, seg1, seg2):

        p1, p2 = seg1
        p3, p4 = seg2
        if self.intersect(seg1, seg2): return 0
        return min(
            self.get_distance_SP(seg1, p3), self.get_distance_SP(seg1, p4),
            self.get_distance_SP(seg2, p1), self.get_distance_SP(seg2, p2),
        )

    def get_cross_pointSS(self, seg1, seg2):

        p1, p2 = seg1
        p3, p4 = seg2
        if not self.intersect(seg1, seg2): return (INF, INF)
        if p1 == p2: return p2
        if p3 == p4: return p3
        base = self.sub(p4, p3)
        dist1 = abs(self.cross(base, self.sub(p1, p3)))
        dist2 = abs(self.cross(base, self.sub(p2, p3)))
        t = dist1 / (dist1+dist2)
        return self.add(p1, self.mul(self.sub(p2, p1), t))

    def intersectCL(self, c, line):

        x, y, r = c
        return self.get_distance_SP(line, (x, y)) <= r

    def get_cross_pointCL(self, c, line):
        from math import sqrt

        if not self.intersectCL(c, line): return -1
        x, y, r = c
        p1, p2 = line
        pr = self.project(line, (x, y))
        e = self.div(self.sub(p2, p1), self.abs(self.sub(p2, p1)))
        base = sqrt(r*r - self.norm(self.sub(pr, (x, y))))
        return [self.add(pr, self.mul(e, base)), self.sub(pr, self.mul(e, base))]

R, x1, y1, x2, y2 = MAP()
gm = Geometry(EPS)

try:
    # 円と直線の交点
    p1, p2 = gm.get_cross_pointCL((x1, y1, R), ((x1, y1), (x2, y2)))
    # 中点の場所
    ax1 = (x2+p1[0])/2
    ay1 = (y2+p1[1])/2
    r1 = gm.get_distance_PP((x2, y2), p1)/2
    ax2 = (x2+p2[0])/2
    ay2 = (y2+p2[1])/2
    r2 = gm.get_distance_PP((x2, y2), p2)/2
    # 半径が大きい方
    if r1 >= r2:
        ans = (ax1, ay1, r1)
    else:
        ans = (ax2, ay2, r2)
    # 元の円より大きい時は元の円にする
    if ans[2] > R:
        ans = (x1, y1, R)
    print(*ans)
except:
    # (x1,y1) == (x2,y2) なら向きは何でもいいので半分の場所
    r = R/2
    ax = x1+r
    ay = y1
    print(ax, ay, r)
