# .\oj-prep.ps1 コンテスト名

# コンテストの階層を作成
cd "AtCoder"
$Argument = "/c acc new " + $Args[0]
Start-Process -FilePath "cmd" -ArgumentList $Argument -NoNewWindow -Wait

# A問題のパスへ移動
$path = $Args[0] + "\a"
cd $path
