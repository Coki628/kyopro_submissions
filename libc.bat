@REM lc.bat 問題名
@echo off

@REM 環境に合わせて変更
set project_root=C:\Users\srcn4\repos\kyopro\kyopro_submissions

cd librarychecker
@REM 問題指定(なんかうまく動かない)
@REM call oj-prepare --config-file %project_root%\_lib\cpp\oj-configs\prepare.config.ac.toml https://judge.yosupo.jp/problem/%1
if not exist %1 mkdir %1
copy %project_root%\_tools\oj-configs\tpl.cpp %1\1.cpp
@REM 問題を開く
call code %1\1.cpp
cd ..
