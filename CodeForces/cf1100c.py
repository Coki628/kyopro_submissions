# -*- coding: utf-8 -*-

"""
数学系、三角関数
・最終的にこのCのAC者数がBより多いってあたり、
　世界の参加者全体の数学力の高さにへこむ。
　オレもこのくらい時間内に自分で辿り着けるようになりたいよなー…。
"""

from math import sin, radians

n, r = map(int, input().split())

# まず、外円の中心 - 内円の中心 - 外円同士の接点 を結ぶ角度を出す
dig = 360 / n / 2
theta = sin(radians(dig))

# 外円の半径をRとすると、辺の長さがそれぞれ
# 外円の中心 - 内円の中心 => r + R
# 外円の中心 - 外円同士の接点 => R
# となるので、sinと組み合わせて
# R / (r+R) = sinθ とできる。
# あとはこれを R = の形に展開すると以下の式になる。
ans = theta*r / (1-theta)

# 小数点以下7桁で丸める(一応サンプルに合わせて)
print('{:.7f}'.format(ans))
