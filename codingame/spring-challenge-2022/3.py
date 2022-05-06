"""
・自陣に1～3番目に近くにいる敵をそれぞれ分担してやっつけに行く方針。
　状況見ながら、ちょっとした改善を入れてる。
　解放されたWIND全くまだ使ってないけど、これでも手元だとBossは安定して勝ってそう。
　提出したら、無事Wood1を突破。ブロンズ昇格。
"""

import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

# base_x: The corner of the map representing your base
base_x, base_y = [int(i) for i in input().split()]
heroes_per_player = int(input())  # Always 3

# game loop
while True:
    for i in range(2):
        # health: Each player's base health
        # mana: Ignore in the first league; Spend ten mana to cast a spell
        health, mana = [int(j) for j in input().split()]
    entity_count = int(input())  # Amount of heros and monsters you can see

    XY = []
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

        if _type == 0:
            dist = abs(x-base_x) + abs(y-base_y)
            # ある程度近くなら倒しに行く
            if dist < 6000:
                XY.append((dist, x, y))
    # 距離を優先度にしてソート
    XY.sort()

    for i in range(heroes_per_player):

        # Write an action using print
        # To debug: print("Debug messages...", file=sys.stderr, flush=True)

        # In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL <spellParams>;
        if len(XY):
            print('MOVE {0} {1} {2}'.format(XY[i%len(XY)][1], XY[i%len(XY)][2], i))
        else:
            # やることなかったら自陣に戻る
            print('MOVE {0} {1} {2}'.format(base_x, base_y, i))
