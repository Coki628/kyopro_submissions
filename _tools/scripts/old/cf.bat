@REM cf.bat コンテスト番号
@REM cf.bat コンテスト番号 問題
@echo off

@REM 環境に合わせて変更
set project_root=C:\Users\srcn4\repos\kyopro

cd CodeForces
@REM 全問題取得
if "%2"=="" (
    @REM 全問題を取得
    call oj-prepare --config-file %project_root%\_lib\cpp\oj-configs\prepare.config.cf.toml https://codeforces.com/contest/%1
    @REM A問題を開く
    call code %1\A\1.cpp
    cd ..\..
@REM 問題指定
) else (
    @REM なければコンテストの階層を作成
    if not exist %1 mkdir %1
    cd %1
    call oj-prepare --config-file %project_root%\_lib\cpp\oj-configs\prepare.config.cf.toml https://codeforces.com/contest/%1/problem/%2
    @REM 問題を開く
    call code %2\1.cpp
    cd ..\..
)
