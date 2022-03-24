# kyopro_submissions
別環境で再構成する時のために、自分用の備忘録として一応色々書いておく。

## 事前準備
- vscode
- GCC
- Python 3系
- pip
- pipenv

## 前提
- 基本的にエディタはvscodeで見ている想定
- このリポジトリと並列な階層に、[kyopro_library](https://github.com/Coki628/kyopro_library)と[ACL](https://github.com/atcoder/ac-library)をclone済である想定

## セットアップ例
```bash
# setup virtual env
pipenv --python 3.6
pipenv shell
# install dependencies
pip install -r requirements.txt
```
- .vscode/settings.json のPythonのパスを適切に設定
- .vscode/tasks.json のPythonのパスを適切に設定
```bash
# create dist files
mkdir _dist
touch _dist/main.cpp
```

## 問題取得
- 直下にあるac.py等の各コンテストサイト用スクリプトはoj-prepareをラップしてる。`python ac.py 問題URL` のように実行すれば、適切に階層を作成して、テストケースを取ってきて、テンプレート付cppファイルを生成して、vscodeのタブでそれを開く。
- バッチからPythonに移行中だけどやってないのもある。次使う時に順次やる予定。

## 実行方法例
- F5でデバッグ実行
- Ctrl+Shift+Bで提出用ファイル生成+oj testが動く。oj-bundleでライブラリ展開済のコードが_dist/main.cppに生成されるので、これをコピペして提出。
