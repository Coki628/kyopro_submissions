"""
・python -> C++ 変換ツール
・細かいところはやらない。大まかなところだけ置換して、C++写経作業のコストを下げる。
・って思ってたけど、作ってるとやっぱり色々やりたくなっちゃうよね。
・注意点！読み込むpythonファイルは空行にスペースがないことを確認すること！あるとバグる。。
"""

import os
import re

path_r = '{0}/dist/in.py'.format(os.getcwd())
path_w = '{0}/dist/out.cpp'.format(os.getcwd())

out = []
indent = '    '
with open(path_r, encoding='utf-8') as f:
    depth = 0
    for line in f.readlines():

        # 空行
        if line[0] == '\n':
            out.append(line)
            continue
        # コメント行
        if line.strip().startswith('#') or line.strip().startswith('"""'):
            line = line.replace('#', '//').replace('"""', '//', 1).replace('"""', '')
            out.append(line)
            continue

        # インデントの確認
        i = 0
        while line[i] == ' ':
            i += 1
        nxdepth = i // len(indent)
        # 前の行がコンマで終わっていたら、ブロックではないとみなす
        if not (out and len(out[-1]) >= 2 and out[-1].strip()[-1] == ','):
            while depth > nxdepth:
                depth -= 1
                # 空行、コメント行は次のブロックに付けたいので後ろに回す
                if out and (out[-1] == '\n' or out[-1].strip().startswith('//')):
                    tmp = out.pop()
                    out.append('{0}}}\n'.format(indent*depth))
                    out.append(tmp)
                else:
                    out.append('{0}}}\n'.format(indent*depth))
        depth = nxdepth
        line = line.strip()

        # 共通
        # インクリメント、デクリメント
        line = line.replace(' += 1', '++')
        line = line.replace(' -= 1', '--')
        # list -> vector
        line = line.replace('.append', '.pb')
        # 否定
        line = line.replace(' not ', ' !')
        # 切り捨て除算
        line = line.replace('//', '/')
        # 2文字以上の文字列の括弧をダブルクォートに
        if re.search(r'\'.*\'', line):
            s = re.search(r'\'.*\'', line).group(0).replace('\'', '')
            if len(s) >= 2:
                line = line.replace('\'', '"')
        # 引数のselfを消す
        line = line.replace('(self, ', '(')
        # クラス内のselfを消す
        line = line.replace('self.', '')

        # if文
        if line.startswith('if '):
            line = 'if ({0}) {{'.format(line[3:-1])
        elif line.startswith('elif '):
            # 余分な}を削除
            out.pop()
            line = '}} else if ({0}) {{'.format(line[5:-1])
        elif line.startswith('else:'):
            out.pop()
            line = '} else {'

        # for文
        elif line.startswith('for '):
            # range使ってるやつ
            if line.count('range'):
                # ループカウンター
                counter = line.split()[1]
                l = line.find('range') + 6
                r = line.find('):')
                # 引数部分
                args = line[l:r].replace(' ', '').split(',')
                # 引数の形に合わせてrepマクロに変換
                if len(args) == 1:
                    end = args[0]
                    line = 'rep({0}, {1}) {{'.format(counter, end)
                elif len(args) == 2:
                    start, end = args
                    line = 'rep({0}, {1}, {2}) {{'.format(counter, start, end)
                elif len(args) == 3:
                    start, end, step = args
                    line = 'rep({0}, {1}, {2}, {3}) {{'.format(counter, start, end, step)
            # enumerateしてない普通のfor a in Aみたいなやつ
            elif not line.count('enumerate'):
                sep = line.find(' in ')
                elems = line[4:sep].replace(' ', '').split(',')
                list_name = line[sep+4:-1]
                if len(elems) == 1:
                    line = 'for (auto {0} : {1}) {{'.format(*elems, list_name)
                elif len(elems) == 2:
                    line = 'for (auto [{0}, {1}] : {2}) {{'.format(*elems, list_name)

        # while文
        elif line.startswith('while '):
            line = 'while ({0}) {{'.format(line[6:-1])

        # 関数
        elif line.startswith('def '):
            line = line[:-1] + ' {'
            # コンストラクタ
            if line.startswith('def __init__'):
                line = line.replace('def __init__', classname)

        # クラス
        elif line.startswith('class '):
            line = line[:-1] + ' {'
            line = line.replace('class', 'struct')
            classname = line.split()[1]

        # ブロックを作らない通常の文
        else:
            # 意図的に改行してるとこ以外
            if line[-1] not in [',', '[', '{', '(']:
                line += ';'

        out.append(indent*depth + line + '\n')

    # ファイル終端でのインデント処理
    while depth > 0:
        depth -= 1
        if out and (out[-1] == '\n' or out[-1].strip().startswith('//')):
            tmp = out.pop()
            out.append('{0}}}\n'.format(indent * depth))
            out.append(tmp)
        else:
            out.append('{0}}}\n'.format(indent * depth))

with open(path_w, mode='w', encoding='utf-8') as f:
    f.write(''.join(out))
