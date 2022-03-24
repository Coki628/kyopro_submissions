from subprocess import run, PIPE, Popen

# カレントディレクトリにあるファイル名の一覧を取得
proc = run('ls', shell=True, stdout=PIPE, stderr=PIPE, encoding='utf-8')

# 上書きでバグらないように1年ずつ処理
year = '2005'

filenames = proc.stdout.split('\n')
filenames = list(filter(lambda s: s.startswith('joi' + year) or s.startswith('joisc' + year), filenames))

for filename in filenames:
    # 空行とこのファイルは無視
    if not filename or filename == 'rename_joi.py':
        continue
    if filename.startswith('joisc'):
        nxtyear = int(filename[5:9]) + 1
        suffix = filename[9:]
        run('mv {0} joisc{1}{2}'.format(filename, nxtyear, suffix), shell=True)
    elif filename.startswith('joi'):
        nxtyear = int(filename[3:7]) + 1
        suffix = filename[7:]
        run('mv {0} joi{1}{2}'.format(filename, nxtyear, suffix), shell=True)
