@REM dojo.bat 回_部屋 問題番号 問題URL 
@echo off

@REM 環境に合わせて変更
set project_root=C:\Users\srcn4\repos\kyopro

cd kyoprodojo
if not exist %1 mkdir %1
cd %1
mkdir %2
cd %2
call oj-prepare --config-file %project_root%\_lib\cpp\oj-configs\prepare.config.dojo.toml %3
call code 1.cpp
cd ..\..\..
