"""
・割と終了間際、攻2守1の編成を作ってみた。まだ未完成。。
"""

import sys
from math import hypot
from random import randrange
from collections import Counter

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

# 巡回路
cx = base_x
cy = base_y + 2000*side
pos0 = []
for i in range(9):
    pos0.append((int(cx), int(cy)))
    # Y軸の上下が逆なので回転方向も逆で考える
    cx, cy = rotate((base_x, base_y), (cx, cy), 350)
tmp = pos0[1:-1]
pos0 += tmp[::-1]
cx = base_x
cy = base_y + 3500*side
pos1 = []
for i in range(9):
    pos1.append((int(cx), int(cy)))
    # Y軸の上下が逆なので回転方向も逆で考える
    cx, cy = rotate((base_x, base_y), (cx, cy), 350)
tmp = pos1[1:-1]
pos1 += tmp[::-1]
cx = opponent_x
cy = opponent_y + 6000*-side
pos2 = []
for i in range(9):
    pos2.append((int(cx), int(cy)))
    # Y軸の上下が逆なので回転方向も逆で考える
    cx, cy = rotate((opponent_x, opponent_y), (cx, cy), 350)
tmp = pos2[1:-1]
pos2 += tmp[::-1]

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
    [8000, 8000, 100000],
    [4000, 100000, 100000],
    [4000, 100000, 100000],
]
# 自分の待機位置
hero_base = [
    [
        (base_x+1000*side, base_y+1000*side),
        (base_x+4000*side, base_y+4000*side),
        (opponent_x+3000*-side, opponent_y+3000*-side),
    ],
    [
        (base_x+2000*side, base_y+2000*side),
        (opponent_x+3000*-side, opponent_y+3000*-side),
        (opponent_x+3000*-side, opponent_y+3000*-side),
    ],
    [
        (base_x+2000*side, base_y+2000*side),
        (opponent_x+3000*-side, opponent_y+3000*-side),
        (opponent_x+3000*-side, opponent_y+3000*-side),
    ],
]

chasing = 0
target = -1
targetprevx = -1
targetprevy = -1
last_controlled = [-10] * 6

# 調整値
add = 4
# シールド張るか
def can_reach(distbase, health, nearcnt):
    # この敵が到達に必要な手数
    needstep = ceil(distbase-300, 400)
    return health > needstep*(1+nearcnt)
# ほぼ確実に到達されてしまう
def must_reach(shield_life, distbase, health):
    if shield_life == 0:
        return False
    # この敵が到達に必要な手数
    needstep = ceil(distbase-300, 400)
    return health > needstep*4

# game loop
while True:
    # 待機場所を動的に
    hero_base[0][0] = pos0[turn%len(pos0)]
    hero_base[1][0] = pos1[turn%len(pos1)]
    hero_base[2][0] = pos1[turn%len(pos1)]
    hero_base[0][1] = pos1[turn%len(pos1)]
    hero_base[1][1] = pos2[turn%len(pos2)]
    hero_base[2][1] = pos2[turn%len(pos2)]
    hero_base[0][2] = pos2[turn%len(pos2)]
    hero_base[1][2] = pos2[turn%len(pos2)]
    hero_base[2][2] = pos2[turn%len(pos2)]

    mana = [0] * 2
    for i in range(2):
        # health: Each player's base health
        # mana: Ignore in the first league; Spend ten mana to cast a spell
        health, mana[i] = [int(j) for j in input().split()]
    entity_count = int(input())  # Amount of heros and monsters you can see

    if phase == 0 and turn >= 100:
        phase = 1
    if phase >= 1:
        mode[0] = 0
        if mana[0] <= 30:
            phase = 1
            mode[1] = 1
            mode[2] = 1
        elif mana[0] >= 100:
            phase = 2
            mode[1] = 2
            mode[2] = 2
    XY = []
    XY2 = []
    D = {}
    heros = []
    oppos = []
    nearcnt = 0
    might_wind = set()
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
            heros.append((x, y, shield_life, _id, is_controlled))
            if is_controlled:
                last_controlled[_id] = turn
            # 序盤で操作してくるやつに当たったら早めに守り強化する
            if phase == 0 and mode[_id+(0 if side == 1 else -3)] == 0 and is_controlled:
                phase = 1
                mode[0] = 0

        # 敵
        if _type == 0:
            dist = hypot(x-base_x, y-base_y)
            XY.append((-(near_base == 1) ,-(threat_for == 1), dist, -health, x, y, _id, shield_life, threat_for))
            XY2.append((health, x, y, _id, shield_life, threat_for))
            D[_id] = (health, x, y, _id, shield_life, threat_for)
        # 相手
        if _type == 2:
            oppos.append((x, y, shield_life, _id))
            distbase = hypot(base_x-x, base_y-y)
            if distbase <= 7000:
                nearcnt += 1
            if phase == 0:
                # 序盤で1人でも近くに来たら守り担当を置く
                if nearcnt == 1:
                    defence_range[0][0] = 3000
                # 序盤で2人で攻めてくるやつに当たったら早めに守り強化する
                if nearcnt >= 2:
                    phase = 1
                    mode[0] = 0

    # 距離を優先度にしてソート
    XY.sort()

    # 各敵の近くにいる相手方の人数
    nearcnt2 = Counter()
    for _, _, distbase, health, x, y, _id, shield_life, threat_for in XY:
        distbase = hypot(base_x-x, base_y-y)
        for oppox, oppoy, _, _ in oppos:
            dist = hypot(oppox-x, oppoy-y)
            if dist <= 2200:
                nearcnt2[_id] += 1
            # WINDやられる可能性がある
            if shield_life == 0 and dist <= 1280 and mana[1] >= 10:
                might_wind.add(_id)

    for i in range(heroes_per_player):

        # Write an action using print
        # To debug: print("Debug messages...", file=sys.stderr, flush=True)
        # In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL <spellParams>;

        def act():
            global chasing
            global target
            global targetprevx
            global targetprevy
            myx, myy, myshield_life, myid, is_controlled = heros[i]
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
                            if distme <= 2200 and threat_for == 2 and can_reach(distbase, health, nearcnt2[_id]):
                                return 'SPELL SHIELD {0} {1}'.format(_id, i)
                        if shield_life == 0 and not (x == targetprevx and y == targetprevy):
                            distme = hypot(x-myx, y-myy)
                            if (distbase >= 5000 or not _id in might_wind) and distme <= 1280 and (distbase-300 <= 2200 or health > 2):
                                return 'SPELL WIND {0} {1} {2}'.format(myx+opponent_x-x, myy+opponent_y-y, i)
                            else:
                                return 'MOVE {0} {1} {2}'.format(x, y, i)
                        chasing = 0
                        target = -1
                    # distmebase2500なら、索敵範囲2200にいなければ既にbase300以内で入ってるか消えてるか
                    elif chasing and distmebase >= 2500:
                        # 追ってる対象じゃなくても近くに飛ばせるやつがいるなら飛ばす
                        for shield_life, distme, health, x, y, _id, threat_for in XY3:
                            if (distbase >= 5000 or not _id in might_wind) and shield_life == 0 and distme <= 1280 and (distbase-300 <= 2200 or health > 2):
                                chasing = 3
                                target = _id
                                targetprevx = x
                                targetprevy = y
                                return 'SPELL WIND {0} {1} {2}'.format(myx+opponent_x-x, myy+opponent_y-y, i)
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
                            # # 行けそうならシールド張ってやる
                            # if distme <= 2200 and threat_for == 2 and can_reach(distbase, health, nearcnt2[_id]):
                            #     return 'SPELL SHIELD {0} {1}'.format(_id, i)
                            if (distbase >= 5000 or not _id in might_wind) and distme <= 1280 and (distbase-300 <= 2200 or health > 2):
                                # 標的確定
                                chasing = 3
                                target = _id
                                targetprevx = x
                                targetprevy = y
                                return 'SPELL WIND {0} {1} {2}'.format(myx+opponent_x-x, myy+opponent_y-y, i)
                            # if distme <= 2200 and threat_for != 2:
                            #     return 'SPELL CONTROL {0} {1} {2}'.format(_id, opponent_x, opponent_y, i)
                            if distme <= 2200:
                                return 'MOVE {0} {1} {2}'.format(x, y, i)
                return 'MOVE {0} {1} {2}'.format(tx, ty, i)

            # 引き剝がしてくるやつへの牽制
            if mode[i] in [0, 3] and last_controlled[myid] == turn-1:
                return 'SPELL SHIELD {0} {1}'.format(myid, i)

            if distbase >= defence_range[phase][i]:
                # 持ち場を離れ過ぎたら戻る
                return 'MOVE {0} {1} {2}'.format(tx, ty, i)

            if mode[i] in [0, 3]:
                for _, _, distbase, health, x, y, _id, shield_life, threat_for in XY:
                    health = -health
                    distme = hypot(x-myx, y-myy)

                    # 敵の自陣からの距離2500以下 or 自陣にそこそこ近くてWINDやられそう
                    if (distbase <= 2500 or distbase <= 5000 and _id in might_wind) and mana[0] >= 10 and threat_for == 1:
                        # WINDが届く範囲
                        if distme <= 1280 and shield_life == 0:
                            return 'SPELL WIND {0} {1} {2}'.format(opponent_x, opponent_y, i)
                    if mode[i] == 0 and not must_reach(shield_life, distbase, health):
                        return 'MOVE {0} {1} {2}'.format(x, y, i)
                    # else:
                    #     # 門番は動かない
                    #     return 'MOVE {0} {1} {2}'.format(*hero_base[phase][i], i)
            
            if mode[i] == 1:
                # マナ稼ぎは常に自分の近くのやつに
                if XY3:
                    shield_life, distme, health, x, y, _id, threat_for = XY3[0]
                    return 'MOVE {0} {1} {2}'.format(x, y, i)

            # やることなかったら持ち場に戻る
            return 'MOVE {0} {1} {2}'.format(*hero_base[phase][i], i)
        print(act())
    turn += 1
