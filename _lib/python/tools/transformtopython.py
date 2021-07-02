"""
・C++ -> python 変換ツール
・最近こっちの機会のが増えたので逆も作ることにする。
・細かいところはやらない。大まかなところだけ置換して、python写経作業のコストを下げる。
"""

import os
import re

# 閉じ括弧のindexを返す
def get_pair(l, start, end, line):
    cnt = 0
    r = l
    while r < len(line):
        if line[r] == start:
            cnt += 1
        elif line[r] == end:
            if cnt == 0:
                break
            else:
                cnt -= 1
        r += 1
    return r

path_r = '{0}/in.cpp'.format(os.getcwd())
path_w = '{0}/out.py'.format(os.getcwd())

out = []
indent = '    '
with open(path_r) as f:
    depth = 0
    for line in f.readlines():

        # 空行
        if line[0] == '\n':
            out.append(line)
            continue
        # コメント行
        if line.strip().startswith('//'):
            line = line.replace('//', '#')
            out.append(line)
            continue
        # 閉じ括弧消し
        if line.strip() == '}':
            continue  

        # インデントの確認
        i = 0
        while line[i] == ' ':
            i += 1
        depth = i//len(indent)
        line = line.strip()
        # 末尾セミコロンを削除
        if line[-1] == ';':
            line = line[:-1]

        # 共通
        # インクリメント、デクリメント
        line = line.replace('++', ' += 1')
        line = line.replace('--', ' -= 1')
        # true -> True
        line = line.replace('true', 'True')
        # false -> False
        line = line.replace('false', ' False')
        # list -> vector
        line = line.replace('.pb', '.append')
        # 否定 (!=まで置換してしまうので保留)
        # line = line.replace( ' !', ' not ')
        # 切り捨て除算 (小数除算まで切り捨ててしまうので、そこはとりあえず手動チェック)
        line = line.replace('/', '//')
        # ダブルクォート -> シングルクォート (やらなくてもいい)
        line = line.replace('"', '\'')
        # 主な型宣言は消しておく
        if line.startswith('const '):
            line = line.replace('const ', '')
        # ld,mintあたりはどのみち書き換えが要るのであえて残しておく
        types = ['ll ', 'int ', 'auto ', 'string ', 'char ', 'bool ']
        for _type in types:
            if line.startswith(_type):
                line = line.replace(_type, '')
        # swap(a, b) -> a, b = b, a
        if line.count('swap('):
            l = line.find('swap(')+5
            r = get_pair(l, '(', ')', line)
            a, b = line[l:r].replace(' ', '').split(',')
            line = line[:l-5] + '{0}, {1} = {1}, {0}'.format(a, b) + line[r+1:]
        # A.size() -> len(A)
        if line.count('size('):
            r = line.find('.size(')
            l = max(line.rfind(' ', 0, r), line.rfind('(', 0, r))+1
            arr = line[l:r]
            line = line[:l] + 'len({0})'.format(arr) + line[r+7:]
        # chmin(a, b) -> a = min(a, b)
        if line.count('chmin('):
            l = line.find('chmin(')+6
            r = get_pair(l, '(', ')', line)
            a, b = line[l:r].replace(' ', '').split(',')
            line = line[:l-6] + '{0} = min({0}, {1})'.format(a, b) + line[r+1:]
        # chmax(a, b) -> a = max(a, b)
        if line.count('chmax('):
            l = line.find('chmax(')+6
            r = get_pair(l, '(', ')', line)
            a, b = line[l:r].replace(' ', '').split(',')
            line = line[:l-6] + '{0} = max({0}, {1})'.format(a, b) + line[r+1:]
        # sort,reverseあたりも変換できたらいいな

        # if文
        if line.startswith('if ('):
            l = line.find('(')+1
            r = get_pair(l, '(', ')', line)
            # r = line.find(')')
            cond = line[l:r]
            # {}を使わない1行でやるやつ
            content = ''
            if line[-1] != '{':
                content = line[r+2:]
            line = 'if {0}:'.format(cond)
            if content:
                line += ' '+content
        elif line.startswith('} elif (') or line.count('else if'):
            l = line.find('(')+1
            r = get_pair(l, '(', ')', line)
            # r = line.find(')')
            cond = line[l:r]
            # {}を使わない1行でやるやつ
            content = ''
            if line[-1] != '{':
                content = line[r+2:]
            line = 'elif {0}:'.format(cond)
            if content:
                line += ' '+content
        elif line.startswith('} else '):
            # {}を使わない1行でやるやつ
            content = ''
            if line[-1] != '{':
                content = line[8:]
            line = 'else:'
            if content:
                line += ' '+content

        # repマクロ
        elif line.startswith('rep('):
            l = line.find('(')+1
            r = get_pair(l, '(', ')', line)
            args = line[l:r].replace(' ', '').split(',')
            # {}を使わない1行でやるやつ
            content = ''
            if line[-1] != '{':
                content = line[r+2:]
            # 引数に合わせてfor文に変換
            if len(args) == 2:
                counter, end = args
                line = 'for {0} in range({1}):'.format(counter, end)
            elif len(args) == 3:
                counter, start, end = args
                line = 'for {0} in range({1}, {2}):'.format(counter, start, end)
            elif len(args) == 4:
                counter, start, end, step = args
                line = 'for {0} in range({1}, {2}, {3}):'.format(counter, start, end, step)
            if content:
                line += ' '+content

        # for文
        elif line.startswith('for ('):
            # for (ll i=0; i<N; i++) {
            if line.count(';'):
                # ややこしいのでとりあえず保留
                pass
            # for (auto [a, b] : AB) {
            if line.count('auto') and line.count('['):
                l = line.find('[')+1
                r = get_pair(l, '[', ']', line)
                elems = line[l:r].strip()
                l = line.find(':')+1
                r = get_pair(l, '(', ')', line)
                arr = line[l:r].strip()
                line = 'for {0} in {1}:'.format(elems, arr)
            # for (ll a : A) {
            elif line.count(':'):
                l = line.find('(')+1
                r = get_pair(l, '(', ')', line)
                args = line[l:r]
                l = args.find(' ')+1
                r = args.find(':')
                elem = args[l:r].strip()
                l = args.find(':')+1
                arr = args[l:].strip()
                line = 'for {0} in {1}:'.format(elem, arr)

        # while文
        elif line.startswith('while ('):
            line = line.replace('while (', 'while ').replace(') {', ':')

        # 関数
        # とりあえず保留

        # クラス
        # とりあえず保留

        out.append(indent*depth + line + '\n')

with open(path_w, mode='w') as f:
    f.write(''.join(out))
