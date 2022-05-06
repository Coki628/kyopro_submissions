"""
・2回目提出。そこそこ善戦した。これをベースにやるか。
"""

import sys
from math import hypot
from random import randrange

def ceil(x, y=1): return int(-(-x // y))

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

turn = 0

# phase別設定値
# 0: 開始時＆マナ切れ
# 1: 攻める
phase = 0

# 3人の行動を決めるmode
mode = [
    0, 0, 0,
]

# 本陣から敵を倒しに行く範囲
defence_range = [
    [4000, 8000, 100000],
    [4000, 8000, 100000],
    [4000, 8000, 100000],
]
# 自分の待機位置
hero_base = [
    [
        (base_x+2000*side, base_y+2000*side),
        (base_x+4000*side, base_y+4000*side),
        (center_x, center_y),
    ],
    [
        (base_x+2000*side, base_y+2000*side),
        (base_x+4000*side, base_y+4000*side),
        (opponent_x+3000*-side, opponent_y+3000*-side),
    ],
    [
        (base_x+2000*side, base_y+2000*side),
        (base_x+4000*side, base_y+4000*side),
        (opponent_x+3000*-side, opponent_y+3000*-side),
    ],
]

chasing = 0
target = -1
targetprevx = -1
targetprevy = -1

# game loop
while True:
    if turn >= 100:
        mode[1] = 1

    mana = [0] * 2
    for i in range(2):
        # health: Each player's base health
        # mana: Ignore in the first league; Spend ten mana to cast a spell
        health, mana[i] = [int(j) for j in input().split()]
    entity_count = int(input())  # Amount of heros and monsters you can see

    if mana[0] <= 30:
        phase = 0
    elif turn >= 100 and mana[0] >= 100:
        phase = 1

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
            # 操作されていたら危険
            if is_controlled and phase == 1:
                phase = 2

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
            if phase >= 1 and i == 2:
                # if myshield_life == 0 and mana[0] >= 10:
                #     return 'SPELL SHIELD {0} {1}'.format(myid, i)

                # 標的が決まってる
                if target != -1:
                    if target in D:
                        health, x, y, _id, shield_life, threat_for = D[target]
                        if shield_life == 0:
                            # 敵から相手陣への距離
                            distbase = hypot(x-opponent_x, y-opponent_y)
                            # この敵が到達に必要な手数
                            needstep = ceil(distbase-300, 400)
                            # 行けそうならシールド張ってやる
                            if distme <= 2200 and health > needstep*2:
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
                            # この敵が到達に必要な手数
                            needstep = ceil(distbase-300, 400)
                            # 行けそうならシールド張ってやる
                            if distme <= 2200 and health > needstep*2:
                                return 'SPELL SHIELD {0} {1}'.format(_id, i)
                            if distme <= 1280:
                                # 標的確定
                                chasing = 3
                                target = _id
                                targetprevx = x
                                targetprevy = y
                                return 'SPELL WIND {0} {1} {2}'.format(opponent_x, opponent_y, i)
                            if distme <= 2200:
                                return 'MOVE {0} {1} {2}'.format(x, y, i)

                if tx == myx and ty == myy:
                    # 持ち場から四方ランダム
                    return 'MOVE {0} {1} {2}'.format(tx+2000*(-1)**randrange(0, 2), ty+2000*(-1)**randrange(0, 2), i)
                return 'MOVE {0} {1} {2}'.format(tx, ty, i)

            # 守り
            if distbase >= defence_range[phase][i]:
                # 持ち場を離れ過ぎたら戻る
                return 'MOVE {0} {1} {2}'.format(tx, ty, i)

            if i == 0 or mode[i] == 1:
                if XY:
                    _, _, distbase, health, x, y, _id, shield_life, threat_for = XY[i%len(XY)]
                    health = -health
                    distme = hypot(x-myx, y-myy)

                    if mode[1] == 1:
                        if i <= 1:
                            # 2人目のが近くにいたら対象を入れ替える
                            myx2, myy2, myshield_life2, myid2 = heros[1-i]
                            distme2 = hypot(x-myx2, y-myy2)
                            if distme2 < distme:
                                XY[i%len(XY)], XY[(i+1)%len(XY)] = XY[(i+1)%len(XY)], XY[i%len(XY)]

                    # 敵の自陣からの距離2400以下
                    if distbase <= 2400 and mana[0] >= 10 and threat_for == 1:
                        # WINDが届く範囲
                        if distme <= 1280 and shield_life == 0:
                            return 'SPELL WIND {0} {1} {2}'.format(opponent_x, opponent_y, i)
                        # CONTROLが届く範囲
                        # elif distme <= 2200 and shield_life == 0:
                        #     return 'SPELL CONTROL {0} {1} {2}'.format(_id, myx, myy, i)
                    if phase == 2 and myshield_life == 0:
                        return 'SPELL SHIELD {0} {1}'.format(myid, i)
                    return 'MOVE {0} {1} {2}'.format(x, y, i)
            else:
                # 攻め担当は常に自分の近くのやつに
                if XY3:
                    shield_life, distme, health, x, y, _id, threat_for = XY3[0]
                    return 'MOVE {0} {1} {2}'.format(x, y, i)

            # 圏内に相手方がいたら引き離す
            # if phase == 2 and mana[0] >= 10 and oppos:
            #     oppos2 = []
            #     for x, y, shield_life, _id in oppos:
            #         distme = hypot(x-myx, y-myy)
            #         oppos2.append((distme, x, y, shield_life, _id))
            #     oppos2.sort()
            #     distme, x, y, shield_life, _id = oppos2[0]
            #     if distme <= 2200 and shield_life == 0:
            #         return 'SPELL CONTROL {0} {1} {2}'.format(_id, opponent_x, opponent_y, i)

            # やることなかったら持ち場に戻る
            return 'MOVE {0} {1} {2}'.format(*hero_base[phase][i], i)
        print(act())
    turn += 1
