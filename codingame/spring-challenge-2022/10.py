"""
・攻め担当に動的な待機位置を入れたり。渾身の提出も、600位台で着地…。
"""

import sys
from math import hypot
from random import randrange

def ceil(x, y=1): return int(-(-x // y))

# 回転行列で座標s,tを回転
def rotate(s, t, dig):
    from math import sin, cos, radians

    x1, y1 = s
    x2, y2 = t
    # sを軸としてtを左回りにdig度回転させた座標(x3,y3)
    x3 = x1 + (x2-x1) * cos(radians(dig)) - (y2-y1) * sin(radians(dig))
    y3 = y1 + (x2-x1) * sin(radians(dig)) + (y2-y1) * cos(radians(dig))
    return (x3, y3)

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

# base_x: The corner of the map representing your base
base_x, base_y = [int(i) for i in input().split()]
heroes_per_player = int(input())  # Always 3

side = 1
if base_x == 0:
    opponent_x = 17630
else:
    side = -1
    opponent_x = 0
if base_y == 0:
    opponent_y = 9000
else:
    side = -1
    opponent_y = 0

center_x = 17630 // 2
center_y = 9000 // 2

# 攻め担当の巡回路
cx = opponent_x
cy = opponent_y + 6000*-side
pos = []
for i in range(7):
    # Y軸の上下が逆なので回転方向も逆で考える
    cx, cy = rotate((opponent_x, opponent_y), (cx, cy), 350)
    pos.append((int(cx), int(cy)))
tmp = pos[1:-1]
pos += tmp[::-1]

turn = 0

# phase別設定値
# 0: 開始時＆マナ切れ(ターン100まで)
# 1: 開始時＆マナ切れ(ターン100以降)
# 2: 攻める
phase = 0

# 3人の行動を決めるmode
# 0: 守り
# 1: マナ稼ぎメイン
# 2: 攻め
# 3: 門番専門
mode = [
    0, 1, 1,
]

# 本陣から敵を倒しに行く範囲
defence_range = [
    [3000, 8000, 100000],
    [4000, 4000, 100000],
    [4000, 4000, 100000],
]
# 自分の待機位置
hero_base = [
    [
        (base_x+1000*side, base_y+1000*side),
        (base_x+4000*side, base_y+4000*side),
        (center_x, center_y),
    ],
    [
        (base_x+1000*side, base_y+3000*side),
        (base_x+3000*side, base_y+1000*side),
        (center_x, center_y),
    ],
    [
        (base_x+1000*side, base_y+3000*side),
        (base_x+3000*side, base_y+1000*side),
        (opponent_x+3000*-side, opponent_y+3000*-side),
    ],
]

chasing = 0
target = -1
targetprevx = -1
targetprevy = -1

# 調整値
add = 4
# シールド張るか
def check1(distbase, health):
    # この敵が到達に必要な手数
    needstep = ceil(distbase-300, 400)
    return health > needstep*2

# game loop
while True:
    # 攻め担当の待機場所を動的に
    hero_base[1][2] = pos[turn%len(pos)]
    hero_base[2][2] = pos[turn%len(pos)]

    mana = [0] * 2
    for i in range(2):
        # health: Each player's base health
        # mana: Ignore in the first league; Spend ten mana to cast a spell
        health, mana[i] = [int(j) for j in input().split()]
    entity_count = int(input())  # Amount of heros and monsters you can see

    if turn >= 100:
        mode[0] = 0
        mode[1] = 0
        if mana[0] <= 30:
            phase = 1
            mode[2] = 1
        elif mana[0] >= 100:
            phase = 2
            mode[2] = 2
    XY = []
    XY2 = []
    D = {}
    heros = []
    oppos = []
    for i in range(entity_count):
        # _id: Unique identifier
        # _type: 0=monster, 1=your hero, 2=opponent hero
        # x: Position of this entity
        # shield_life: Ignore for this league; Count down until shield spell fades
        # is_controlled: Ignore for this league; Equals 1 when this entity is under a control spell
        # health: Remaining health of this monster
        # vx: Trajectory of this monster
        # near_base: 0=monster with no target yet, 1=monster targeting a base
        # threat_for: Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
        _id, _type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for = [int(j) for j in input().split()]

        print(_id, _type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for, file=sys.stderr, flush=True)

        # 自分
        if _type == 1:
            heros.append((x, y, shield_life, _id))
            # 序盤で操作してくるやつに当たったら早めに守り強化する
            if phase == 0 and mode[_id+(0 if side == 1 else -3)] == 0 and is_controlled:
                phase = 1
                mode[0] = 0
                mode[1] = 0

        # 敵
        if _type == 0:
            dist = hypot(x-base_x, y-base_y)
            XY.append((-(near_base == 1) ,-(threat_for == 1), dist, -health, x, y, _id, shield_life, threat_for))
            XY2.append((health, x, y, _id, shield_life, threat_for))
            D[_id] = (health, x, y, _id, shield_life, threat_for)
        # 相手
        if _type == 2:
            oppos.append((x, y, shield_life, _id))

    # 距離を優先度にしてソート
    XY.sort()

    for i in range(heroes_per_player):

        # Write an action using print
        # To debug: print("Debug messages...", file=sys.stderr, flush=True)
        # In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL <spellParams>;

        def act():
            global chasing
            global target
            global targetprevx
            global targetprevy
            myx, myy, myshield_life, myid = heros[i]
            # 自分から自陣
            distbase = hypot(myx-base_x, myy-base_y)
            # 自分から敵陣
            distmebase = hypot(opponent_x-myx, opponent_y-myy)
            tx, ty = hero_base[phase][i]
            # 待機場所への距離
            diststay = hypot(tx-myx, ty-myy)

            # 自分との距離でソート
            XY3 = []
            if XY2:
                windcnt = 0
                for health, x, y, _id, shield_life, threat_for in XY2:
                    distme = hypot(x-myx, y-myy)
                    if distme <= 1280 and  shield_life == 0:
                        windcnt += 1
                    XY3.append((shield_life, distme, health, x, y, _id, threat_for))
                XY3.sort()

            # 攻め
            if mode[i] == 2:
                # 標的が決まってる
                if target != -1:
                    if target in D:
                        health, x, y, _id, shield_life, threat_for = D[target]
                        if shield_life == 0:
                            # 敵から相手陣への距離
                            distbase = hypot(x-opponent_x, y-opponent_y)
                            # 行けそうならシールド張ってやる
                            if distme <= 2200 and threat_for == 2 and check1(distbase, health):
                                return 'SPELL SHIELD {0} {1}'.format(_id, i)
                        if shield_life == 0 and not (x == targetprevx and y == targetprevy):
                            distme = hypot(x-myx, y-myy)
                            if distme <= 1280:
                                return 'SPELL WIND {0} {1} {2}'.format(opponent_x, opponent_y, i)
                            else:
                                return 'MOVE {0} {1} {2}'.format(x, y, i)
                        chasing = 0
                        target = -1
                    # distmebase2500なら、索敵範囲2200にいなければ既にbase300以内で入ってるか消えてるか
                    elif chasing and distmebase >= 2500:
                        # 追ってる対象じゃなくても近くに飛ばせるやつがいるなら飛ばす
                        if XY3:
                            shield_life, distme, health, x, y, _id, threat_for = XY3[0]
                            if shield_life == 0 and distme <= 1280:
                                chasing = 3
                                target = _id
                                targetprevx = x
                                targetprevy = y
                                return 'SPELL WIND {0} {1} {2}'.format(opponent_x, opponent_y, i)
                        chasing -= 1
                        return 'MOVE {0} {1} {2}'.format(opponent_x, opponent_y, i)
                    else:
                        chasing = 0
                        target = -1
                if XY3 and distmebase <= 7000:
                    for shield_life, distme, health, x, y, _id, threat_for in XY3:
                        if shield_life == 0:
                            # 敵から相手陣への距離
                            distbase = hypot(x-opponent_x, y-opponent_y)
                            # 行けそうならシールド張ってやる
                            if distme <= 2200 and threat_for == 2 and check1(distbase, health):
                                return 'SPELL SHIELD {0} {1}'.format(_id, i)
                            if distme <= 1280:
                                # 標的確定
                                chasing = 3
                                target = _id
                                targetprevx = x
                                targetprevy = y
                                return 'SPELL WIND {0} {1} {2}'.format(opponent_x, opponent_y, i)
                            # if distme <= 2200 and threat_for != 2:
                            #     return 'SPELL CONTROL {0} {1} {2}'.format(_id, opponent_x, opponent_y, i)
                            if distme <= 2200:
                                return 'MOVE {0} {1} {2}'.format(x, y, i)
                return 'MOVE {0} {1} {2}'.format(tx, ty, i)

            if distbase >= defence_range[phase][i]:
                # 持ち場を離れ過ぎたら戻る
                return 'MOVE {0} {1} {2}'.format(tx, ty, i)

            if mode[i] in [0, 3]:
                if XY:
                    _, _, distbase, health, x, y, _id, shield_life, threat_for = XY[0]
                    health = -health
                    distme = hypot(x-myx, y-myy)

                    # 敵の自陣からの距離2400以下
                    if distbase <= 2400 and mana[0] >= 10 and threat_for == 1:
                        # WINDが届く範囲
                        if distme <= 1280 and shield_life == 0:
                            return 'SPELL WIND {0} {1} {2}'.format(opponent_x, opponent_y, i)
                    if mode[i] == 0:
                        return 'MOVE {0} {1} {2}'.format(x, y, i)
                    else:
                        # 門番は動かない
                        return 'MOVE {0} {1} {2}'.format(*hero_base[phase][i], i)
            elif mode[i] == 1:
                # 攻め担当は常に自分の近くのやつに
                if XY3:
                    shield_life, distme, health, x, y, _id, threat_for = XY3[0]
                    return 'MOVE {0} {1} {2}'.format(x, y, i)

            # やることなかったら持ち場に戻る
            return 'MOVE {0} {1} {2}'.format(*hero_base[phase][i], i)
        print(act())
    turn += 1
