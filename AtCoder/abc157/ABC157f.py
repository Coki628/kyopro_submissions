# -*- coding: utf-8 -*-

"""
参考：https://twitter.com/kyopro_friends/status/123411616341349580
・競プロフレンズさんの説明が分かりやすかったのでそこから。
・二分探索、幾何、円と円の交点
・時間でにぶたんすれば焼けるのがOKの範囲を示す円は定まるなー、までは考えたんだけど、
　円の重なりがどうなるかを探す手段を導けなかった。
・結果的には、候補として円の中心と2円間の交点を全部試せばOKだった。
・計算量はN<=60でN^3にlogだから、約20万*数十=数百万くらい。
　pythonTLE,pypyAC0.5秒。
"""

import sys
from math import hypot

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
INF = 10 ** 18
MOD = 10 ** 9 + 7

class Geometry:
    """ 幾何学計算用クラス """

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
        """ 線分segに対する点pの射影 """

        p1, p2 = seg
        base = self.sub(p2, p1)
        r = self.dot(self.sub(p, p1), base) / self.norm(base)
        return self.add(p1, self.mul(base, r))

    def reflect(self, seg, p):
        """ 線分segを対称軸とした点pの線対称の点 """

        return self.add(p, self.mul(self.sub(self.project(seg, p), p), 2))

    def ccw(self, p0, p1, p2):
        """ 線分p0,p1から線分p0,p2への回転方向 """

        a = self.sub(p1, p0)
        b = self.sub(p2, p0)
        # 反時計回り
        if self.cross(a, b) > self.EPS: return 1
        # 時計回り
        if self.cross(a, b) < -self.EPS: return -1
        # 直線上(p2 => p0 => p1)
        if self.dot(a, b) < -self.EPS: return 2
        # 直線上(p0 => p1 => p2)
        if self.norm(a) < self.norm(b): return -2
        # 直線上(p0 => p2 => p1)
        return 0

    def intersect(self, seg1, seg2):
        """ 線分seg1と線分seg2の交差判定 """

        p1, p2 = seg1
        p3, p4 = seg2
        return (
            self.ccw(p1, p2, p3) * self.ccw(p1, p2, p4) <= 0
            and self.ccw(p3, p4, p1) * self.ccw(p3, p4, p2) <= 0
        )

    def get_distance_LP(self, line, p):
        """ 直線lineと点pの距離 """

        p1, p2 = line
        return abs(self.cross(self.sub(p2, p1), self.sub(p, p1)) / self.abs(self.sub(p2, p1)))

    def get_distance_SP(self, seg, p):
        """ 線分segと点pの距離 """

        p1, p2 = seg
        if self.dot(self.sub(p2, p1), self.sub(p, p1)) < 0: return self.abs(self.sub(p, p1))
        if self.dot(self.sub(p1, p2), self.sub(p, p2)) < 0: return self.abs(self.sub(p, p2))
        return self.get_distance_LP(seg, p)

    def get_distance_SS(self, seg1, seg2):
        """ 線分seg1と線分seg2の距離 """

        p1, p2 = seg1
        p3, p4 = seg2
        if self.intersect(seg1, seg2): return 0
        return min(
            self.get_distance_SP(seg1, p3), self.get_distance_SP(seg1, p4),
            self.get_distance_SP(seg2, p1), self.get_distance_SP(seg2, p2),
        )

    def get_cross_pointSS(self, seg1, seg2):
        """ 線分seg1と線分seg2の交点 """

        p1, p2 = seg1
        p3, p4 = seg2
        base = self.sub(p4, p3)
        dist1 = abs(self.cross(base, self.sub(p1, p3)))
        dist2 = abs(self.cross(base, self.sub(p2, p3)))
        t = dist1 / (dist1+dist2)
        return self.add(p1, self.mul(self.sub(p2, p1), t))
    
    def intersectCL(self, c, line):
        """ 円cと直線lineの交差判定 """

        x, y, r = c
        return self.get_distance_SP(line, (x, y)) <= r

    def get_cross_pointCL(self, c, line):
        """ 円cと直線lineの交点 """
        from math import sqrt

        if not self.intersectCL(c, line): return -1
        x, y, r = c
        p1, p2 = line
        pr = self.project(line, (x, y))
        e = self.div(self.sub(p2, p1), self.abs(self.sub(p2, p1)))
        base = sqrt(r*r - self.norm(self.sub(pr, (x, y))))
        return [self.add(pr, self.mul(e, base)), self.sub(pr, self.mul(e, base))]
    
    def arg(self, p):
        from math import atan2
        x, y = p
        return atan2(y, x)
    
    def polar(self, a, r):
        from math import sin, cos
        return (cos(r)*a, sin(r)*a)
    
    def intersectCC(self, c1, c2):
        """ 円c1と円c2の交差判定 """
        from math import hypot

        x1, y1, r1 = c1
        x2, y2, r2 = c2
        return hypot(x1-x2, y1-y2) <= r1 + r2
    
    def get_cross_pointCC(self, c1, c2):
        """ 円c1と円c2の交点 """
        from math import acos

        if not self.intersectCC(c1, c2): return -1
        x1, y1, r1 = c1
        x2, y2, r2 = c2
        try:
            d = self.abs(self.sub((x1, y1), (x2, y2)))
            a = acos((r1*r1+d*d-r2*r2) / (2*r1*d))
            t = self.arg(self.sub((x2, y2), (x1, y1)))
            return [self.add((x1, y1), self.polar(r1, t+a)), self.add((x1, y1), self.polar(r1, t-a))]
        except:
            # 一方が他方を内包しちゃってる場合等はここに飛ぶ(はず)
            return -1

def bisearch_min(mn, mx, func, EPS):
    """ 条件を満たす最小値を見つける二分探索(小数用) """

    ok = mx
    ng = mn
    while ng+EPS < ok:
        mid = (ok+ng) / 2
        if func(mid):
            # 下を探しに行く
            ok = mid
        else:
            # 上を探しに行く
            ng = mid
    return ok

gm = Geometry(10**-8)

# 時間がt経過した時に、焼けた肉がK個以上あるか
def calc(t):

    # ccls[i] := 時間がt経過した時に肉iが焼けるのに間に合う熱源の範囲
    ccls = []
    # XY := 熱源を置く候補となる座標
    XY = []
    for x, y, c in XYC:
        # 全ての円の中心を、候補座標に加える
        XY.append((x, y))
        # 間に合う範囲を決める半径r
        r = t / c
        ccls.append((x, y, r))

    # 全ての2円間の交点を、候補座標に加える
    for i in range(N):
        ccl1 = ccls[i]
        for j in range(i+1, N):
            ccl2 = ccls[j]
            # 円と円の交点
            res =  gm.get_cross_pointCC(ccl1, ccl2)
            if res != -1:
                XY.append(res[0])
                XY.append(res[1])

    # 候補座標全てを熱源として試して、一番いいものがK以上になるか確認
    mx = 0
    for x, y in XY:
        cnt = 0
        for x2, y2, r in ccls:
            # 頂点(x, y)が円の中にあるか
            if hypot(x-x2, y-y2) <= r + gm.EPS:
                cnt += 1
        mx = max(mx, cnt)

    return mx >= K

N, K = MAP()
XYC = []
for i in range(N):
    x, y, c = MAP()
    XYC.append((x, y, c))

# 経過時間tを二分探索
res = bisearch_min(0.0, 10**9, calc, 10**-8)
print(res)
