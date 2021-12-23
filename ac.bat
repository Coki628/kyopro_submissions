@REM ac.bat コンテスト名
@echo off

cd AtCoder
@REM コンテストの階層を作成
call acc new %1
@REM A問題へ
cd %1\a
