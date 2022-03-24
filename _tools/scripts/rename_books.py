from subprocess import run, PIPE, Popen

# ※Windowsで使う時は適当なbashとかのコンソールで実行すること

prefix = 32

# カレントディレクトリにあるファイル名の一覧を取得
proc = run('ls', shell=True, stdout=PIPE, stderr=PIPE, encoding='utf-8')

for filename in proc.stdout.split('\n'):
    # 空行とこのファイルは無視
    if not filename or filename == 'rename_books.py':
        continue
    # prefixより手前を削る
    run('mv {0} {1}'.format(filename, filename[prefix:]), shell=True)
