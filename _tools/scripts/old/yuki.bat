@REM yuki.bat 問題番号
@echo off

@REM 環境に合わせて変更
set project_root=C:\Users\srcn4\repos\kyopro

cd yukicoder
@REM 問題指定
call oj-prepare --config-file %project_root%\_lib\cpp\oj-configs\prepare.config.ac.toml https://yukicoder.me/problems/no/%1
@REM 問題を開く
call code %1\1.cpp
cd ..
