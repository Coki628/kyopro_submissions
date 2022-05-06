"""
・守りを固めてみたけど、敵にSHIELDやられるとつらい…。
"""

import sys
import math

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
mode = 0
# mode別設定値
# 0: 前半の攻め
# 1: 後半で守り厚め
# 2: 操作されてて危険
attack_range = [100000, 10000, 6000]
hero_base = [
    [((base_x+center_x)//2, (opponent_y+center_y)//2), (center_x, center_y), (center_x, (base_y+center_y)//2)],
    [(base_x+1000*side, base_y+6000*side), (base_x+3000*side, base_y+3000*side), (base_x+6000*side, base_y+1000*side)],
    [(base_x+1000*side, base_y+1000*side), (base_x+1000*side, base_y+1000*side), (base_x+1000*side, base_y+1000*side)],
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
    heros = []
    no_controlled = 1
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
            if is_controlled:
                no_controlled = 0

        # 敵
        if _type == 0:
            dist = abs(x-base_x) + abs(y-base_y)
            # ある程度近くなら倒しに行く
            if dist < attack_range[mode]:
                XY.append((dist, -health, x, y, _id))
    # 距離を優先度にしてソート
    XY.sort()

    if not no_controlled:
        mode = 2

    for i in range(heroes_per_player):

        # Write an action using print
        # To debug: print("Debug messages...", file=sys.stderr, flush=True)

        myx, myy, myshield_life, myid = heros[i]

        # In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL <spellParams>;

        def act():
            if len(XY):
                distbase, health, x, y, _id = XY[i%len(XY)]
                health = -health

                print(distbase, health, mana[0], file=sys.stderr, flush=True)

                distme = abs(x-myx) + abs(y-myy)

                # 敵の距離2000以下
                if distbase <= 2000 and mana[0] >= 10:
                    # WINDが届く範囲
                    if distme <= 1280:
                        return 'SPELL WIND {0} {1} {2}'.format(opponent_x, opponent_y, i)
                    # CONTROLが届く範囲
                    elif distme <= 2200:
                        return 'SPELL CONTROL {0} {1} {2}'.format(_id, opponent_x, opponent_y, i)
                if mode == 2 and myshield_life == 0:
                    return 'SPELL SHIELD {0} {1}'.format(myid, i)
                else:
                    return 'MOVE {0} {1} {2}'.format(x, y, i)
            else:
                # やることなかったら持ち場に戻る
                return 'MOVE {0} {1} {2}'.format(*hero_base[mode][i], i)
        print(act())
    turn += 1
