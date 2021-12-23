@REM cf.bat コンテスト番号
@echo off

cd CodeForces
@REM コンテストの階層を作成
call oj-prepare --config-file C:\Users\srcn4\AppData\Local\online-judge-tools\online-judge-tools\prepare.config.cf.toml https://codeforces.com/contest/%1
@REM A問題へ
cd %1\A
