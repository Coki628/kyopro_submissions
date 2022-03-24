"""
・C++ソースコード圧縮ツール
・読み込んだファイルの行頭のインデントを取り除いて、
　改行をスペース1個に置き換えて、1行のコードにして出力する。
"""

import os

def compress(path_r: str, path_w: str):
    output = []
    with open(path_r, encoding='utf-8') as f:
        for line in f.readlines():
            # 空行
            if line[0] == '\n':
                continue
            # コメント行
            if line.strip().startswith('//'):
                continue
            output.append(line.strip())

    for i in range(len(output)):
        # #define等の前後だけ改行させる
        if output[i].startswith('#'):
            output[i] += '\n'
            if i > 0:
                output[i-1] = output[i-1][:-1] + '\n'
        elif i < len(output)-1:
            output[i] += ' '

    with open(path_w, mode='w', encoding='utf-8') as f:
        f.write(''.join(output))

# このファイルが実行された時(importで呼ばれた時はやらない)
if __name__ == '__main__':
    path_r = '{0}/dist/in.cpp'.format(os.getcwd())
    path_w = '{0}/dist/out.cpp'.format(os.getcwd())
    compress(path_r, path_w)
