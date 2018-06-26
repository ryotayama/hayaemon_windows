@echo off
echo 実行中はPowerShellの画面が表示されます
echo 画面には触らずそのままでお待ちください
cd ./
powershell -ExecutionPolicy Unrestricted ./downloadlibs.ps1
cd ./jpegsr9c/jpeg-9c
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
SET dir=%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A\Include
if exist "%dir%\" goto CONTINUE
SET dir=%ProgramW6432%\Microsoft SDKs\Windows\v7.1\Include
if exist "%dir%\" goto CONTINUE
goto ERROR

:CONTINUE
SET Include=%Include%;%dir%
copy jconfig.vc jconfig.h
nmake /f makefile.vc clean all
cd ../../
powershell -ExecutionPolicy Unrestricted ./makelibs.ps1
cd ./nezplug++/
lib /DEF:npnez.def /MACHINE:x86 /out:npnez.lib
cd ../
powershell -ExecutionPolicy Unrestricted ./copylibs.ps1
cls
echo 処理が完了しました
echo 何かキーを押すと終了します
pause
goto :EOF

:ERROR
echo 必要なSDKが見つかりませんでした
echo Microsoft Windows SDK for Windows 7 and .NET Framework 4 をインストールしてください
echo https://www.microsoft.com/en-us/download/details.aspx?id=8279
pause
