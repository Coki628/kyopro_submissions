"""
・さらに色々改修。これでシルバー突破。ゴールド昇格した。
　最後あと一押し欲しい所で、距離をマンハッタン距離で判定してるのがおかしいと気付いた。
　マンハッタンなんて一言も言ってないんだから、これは普通ユークリッドだよね…。
　逆に、そんなでかいバグ入ってて、シルバー20位くらいまで行ったからよくやってたよ。。
"""

from math import hypot
from random import randrange

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

# mode別設定値
# 0: 前半の攻め
# 1: 後半
# 2: 後半(操作してくる)
mode = 0

# 本陣から敵を倒しに行く範囲
defence_range = [100000, 10000, 6000]
# 自分の待機位置
hero_base = [
    [
        (base_x+4000*side, base_y+6000*side),
        (base_x+8000*side, base_y+2000*side),
        (center_x, center_y),
    ],
    [
        (base_x+1000*side, base_y+2000*side),
        (base_x+2000*side, base_y+1000*side),
        (opponent_x+3000*-side, opponent_y+3000*-side),
    ],
    [
        (base_x+1000*side, base_y+2000*side),
        (base_x+2000*side, base_y+1000*side),
        (opponent_x+3000*-side, opponent_y+3000*-side),
    ],
]

# game loop
while True:
    if turn >= 100:
        mode = 1

    mana = [0] * 2
    for i in range(2):
        # health: Each player's base health
        # mana: Ignore in the first league; Spend ten mana to cast a spell
        health, mana[i] = [int(j) for j in input().split()]
    entity_count = int(input())  # Amount of heros and monsters you can see

    XY = []
    XY2 = []
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

        # 自分
        if _type == 1:
            heros.append((x, y, shield_life, _id))
            # 操作されていたら危険
            if is_controlled and mode == 1:
                mode = 2

        # 敵
        if _type == 0:
            dist = hypot(x-base_x, y-base_y)
            XY.append((-(threat_for == 1), dist, -health, x, y, _id, shield_life, threat_for))
            # 攻め用
            XY2.append((health, x, y, _id, shield_life, threat_for))

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
            myx, myy, myshield_life, myid = heros[i]
            # 自分から自陣
            distbase = hypot(myx-base_x, myy-base_y)
            # 自分から敵陣
            distmebase = hypot(opponent_x-myx, opponent_y-myy)
            tx, ty = hero_base[mode][i]
            # 待機場所への距離
            diststay = hypot(tx-myx, ty-myy)

            # 攻め担当
            if mode >= 1 and i == 2:
                if myshield_life == 0:
                    return 'SPELL SHIELD {0} {1}'.format(myid, i)
                if XY2:
                    # 攻め担当との距離でソート
                    XY3 = []
                    windcnt = 0
                    for health, x, y, _id, shield_life, threat_for in XY2:
                        distme = hypot(x-myx, y-myy)
                        if distme <= 1280 and  shield_life == 0:
                            windcnt += 1
                        XY3.append((distme, shield_life, health, x, y, _id, threat_for))
                    XY3.sort()
                    # 敵陣との距離でソート
                    # XY4 = []
                    # windcnt = 0
                    # for health, x, y, _id, shield_life, threat_for in XY2:
                    #     distme = hypot(x-opponent_x, y-opponent_y)
                    #     if distme <= 1280 and  shield_life == 0:
                    #         windcnt += 1
                    #     XY4.append((distme, health, x, y, _id, shield_life, threat_for))
                    # XY4.sort()

                    # 一番近くの敵
                    distme, shield_life, health, x, y, _id, threat_for = XY3[0]
                    # その敵から敵陣
                    distbase = hypot(x-opponent_x, y-opponent_y)
                    # 12ターンで敵陣に着きそうか
                    can_reach = distbase <= 400 * 12
                    if distme <= 2200 and mana[0] >= 50 and shield_life == 0 and threat_for == 2 and can_reach:
                        return 'SPELL SHIELD {0} {1}'.format(_id, i)
                    elif (distmebase <= 6000 or diststay <= 2000) and windcnt >= 1 and distme <= 1280 and mana[0] >= 50:
                        return 'SPELL WIND {0} {1} {2}'.format(opponent_x, opponent_y, i)
                    elif (distmebase <= 6000 or diststay <= 2000) and distme >= 800 and shield_life == 0:
                        # 一番近くの敵に近づく
                        return 'MOVE {0} {1} {2}'.format(x, y, i)

                # 圏内に相手方がいたら引き離す
                if mana[0] >= 10 and oppos and diststay <= 3000:
                    oppos2 = []
                    for x, y, shield_life, _id in oppos:
                        distme = hypot(x-myx, y-myy)
                        oppos2.append((distme, x, y, shield_life, _id))
                    oppos2.sort()
                    distme, x, y, shield_life, _id = oppos2[0]
                    distme = hypot(x-myx, y-myy)
                    if distme <= 2200 and shield_life == 0 and mana[0] >= 50:
                        return 'SPELL CONTROL {0} {1} {2}'.format(_id, base_x, base_y, i)

                if tx == myx and ty == myy:
                    # 持ち場から四方ランダム
                    return 'MOVE {0} {1} {2}'.format(tx+2000*(-1)**randrange(0, 2), ty+2000*(-1)**randrange(0, 2), i)
                return 'MOVE {0} {1} {2}'.format(tx, ty, i)

            # 守り担当
            if diststay >= 10000:
                # 攻め担当以外は持ち場を離れ過ぎたら戻る
                return 'MOVE {0} {1} {2}'.format(tx, ty, i)

            if XY:
                _, distbase, health, x, y, _id, shield_life, threat_for = XY[i%len(XY)]
                health = -health
                distme = hypot(x-myx, y-myy)

                if i <= 1:
                    # 2人目のが近くにいたら対象を入れ替える
                    myx2, myy2, myshield_life2, myid2 = heros[1-i]
                    distme2 = hypot(x-myx2, y-myy2)
                    if distme2 < distme:
                        XY[i%len(XY)], XY[(i+1)%len(XY)] = XY[(i+1)%len(XY)], XY[i%len(XY)]

                # 敵の距離2000以下
                if distbase <= 2000 and mana[0] >= 10 and threat_for == 1:
                    # WINDが届く範囲
                    if distme <= 1280 and shield_life == 0:
                        return 'SPELL WIND {0} {1} {2}'.format(opponent_x, opponent_y, i)
                    # CONTROLが届く範囲
                    elif distme <= 2200 and shield_life == 0:
                        return 'SPELL CONTROL {0} {1} {2}'.format(_id, opponent_x, opponent_y, i)
                if mode == 2 and myshield_life == 0:
                    return 'SPELL SHIELD {0} {1}'.format(myid, i)
                return 'MOVE {0} {1} {2}'.format(x, y, i)

            # 圏内に相手方がいたら引き離す
            if mode == 2 and mana[0] >= 10 and oppos:
                oppos2 = []
                for x, y, shield_life, _id in oppos:
                    distme = hypot(x-myx, y-myy)
                    oppos2.append((distme, x, y, shield_life, _id))
                oppos2.sort()
                distme, x, y, shield_life, _id = oppos2[0]
                if distme <= 2200 and shield_life == 0:
                    return 'SPELL CONTROL {0} {1} {2}'.format(_id, opponent_x, opponent_y, i)

            # やることなかったら持ち場に戻る
            return 'MOVE {0} {1} {2}'.format(*hero_base[mode][i], i)
        print(act())
    turn += 1
