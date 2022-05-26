@REM ac.bat コンテスト名
@echo off

cd AtCoder
@REM コンテストの階層を作成
call acc new %1
@REM A問題へ
call code %1\a\1.cpp
cd ..

@REM ※accコマンドでやる版。一応取っておく。
