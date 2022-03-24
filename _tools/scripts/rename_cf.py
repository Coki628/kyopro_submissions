from subprocess import run, PIPE, Popen

prefix = 'cf'

# カレントディレクトリにあるファイル名の一覧を取得
proc = run('ls', shell=True, stdout=PIPE, stderr=PIPE, encoding='utf-8')

for filename in proc.stdout.split('\n'):
    # 空行とこのファイルは無視
    if not filename or filename == 'rename_cf.py':
        continue
    if not filename.startswith(prefix):
        run('mv {0} {1}{0}'.format(filename, prefix), shell=True)
